#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Singleton.h"
#include "Rasterizer.h"
#include <gdiplus.h>
#include <vector>
#include "Light.h"
#include "Camera.h"
#include "RendererLibDef.h"

namespace renderer
{
	enum RENDER_STATE
	{
		RENDER_FLAT_GDI = 0,
		RENDER_FLAT,
		RENDER_GOURAUD,
		RENDER_TEXTURED,
		RENDER_TEXTURE_SOLID,
		RENDER_TEXTURE_GOURAUD,
		RENDER_WIREFRAME,
		RENDER_PHONG,
	};

	enum CULL_MODE
	{
		CULL_NONE = 0,
		CULL_BACKFACE,
	};

	enum LIGHT_MODE
	{
		LIGHT_NONE = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
		LIGHT_AMBIENT,
	};

	class RENDER_DECLSPEC Renderer : public Common::Singleton<Renderer>
	{
		public:

			// contructor and destructor
			Renderer(void);
			~Renderer(void);

			// initialisation
			void Initialize(HWND hWnd, int width, int height);
			void Shutdown(void);

			// render methods
			void Clear		(const Gdiplus::Color& colour);
			void Begin		(void);
			void End		(void);
			void FlipBuffer (void);
			void RenderMesh	(Mesh& mesh);
			
			// text rendering
			void RenderText	(TCHAR mes[], float &x, float &y);
			void RenderTextArea(const Gdiplus::RectF& bound, const Gdiplus::Color& col);

			// Accessor and setups
			inline void SetViewPosition (const Maths::Vector4& viewPosition){ m_view		 = viewPosition; }
			inline void SetViewMatrix	(const Maths::Matrix4& viewMatrix)	{ m_viewMatrix	 = viewMatrix; }
			inline void SetProjection	(const Maths::Matrix4& projection)	{ m_projection	 = projection; }
			inline void SetScreenMatrix	(const Maths::Matrix4& screen)		{ m_screenMatrix = screen; }
			inline void SetWorldMatrix	(const Maths::Matrix4& world)		{ m_worldMatrix	 = world; }

			inline void SetCullMode		(CULL_MODE cullMode)				{ m_cullMode = cullMode; }
			inline void SetRenderState	(RENDER_STATE state)				{ m_renderState = state; }
			inline void SetViewFrustum	(const ViewFrustum& frustum)		{ m_frustum = frustum; }


			inline LIGHT_MODE	GetLightMode	(void) const { return m_lightMode; }
			inline RENDER_STATE GetRenderState	(void) const { return m_renderState; }

			inline int GetNumberOfPolygons			(void) const { return m_numPolys; }
			inline int GetNumberOfVerts				(void) const { return m_numVerts; }
			inline int GetNumberOfPolygonOnScreen	(void) const { return m_numPolyDrawn; }

			// lightings
			inline void SetLightMode		(LIGHT_MODE mode)				{ m_lightMode = mode; }
			inline void AddPointLight		(const LightPoint& light)		{ m_pointLights.push_back( light ); }
			inline void SetDirectionalLight	(const LightDirectional& light)	{ m_directionalLight = light; }
			inline void SetAmbientLight		(const LightAmbient& light)		{ m_ambientLight = light; }
			inline void EnableAmbientLight	(bool  enable)					{ m_ambientEnabled = enable; }

		private:
			
			void BuildScreenMatrix			(void);
			void Lighting					(Mesh& mesh);

			// member variable
			ViewFrustum					m_frustum;
			std::vector<LightPoint>		m_pointLights;
			LightDirectional			m_directionalLight;
			LightAmbient				m_ambientLight;

			Maths::Matrix4				m_viewMatrix;
			Maths::Matrix4				m_projection;
			Maths::Matrix4				m_screenMatrix;
			Maths::Matrix4				m_worldMatrix;
			Maths::Vector4				m_view;
			RENDER_STATE				m_renderState;
			CULL_MODE					m_cullMode;
			LIGHT_MODE					m_lightMode;

			renderer::Rasterizer*		m_rasterizer;
			Gdiplus::Graphics*			m_graphics;

			int							m_screenWidth;
			int							m_screenHeight;
			int							m_numPolys;
			int							m_numVerts;
			int							m_numPolyDrawn;
			bool						m_ambientEnabled;
	};

}// end of namespace renderer

#endif // end of #ifndef _RENDERER_H_