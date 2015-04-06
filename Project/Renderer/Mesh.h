#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "Polygon.h"
#include "Matrix4.h"
#include "Light.h"
#include "Vertex.h"
#include "RendererLibDef.h"
//#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace renderer
{
	class LightDirectional;
	class LightPoint;
	class LightAmbient;
	class Vertex;
	class Camera;
	struct ViewFrustum;

	// transformation option for vertices
	enum TRANSFORM_TYPE
	{
		TRANSFORM_LOCAL,
		TRANSFORM_TRANSFORMED,
		TRANSFORM_PROJECTION,
		TRANSFORM_MODEL,
	};

	// storage for uv coordinate of a vertex
	struct UVCoords
	{
		float U;
		float V;
	};

	//// info on how this mesh reflect lights (for colours)
	//struct Material
	//{
	//	Material(void);

	//	float Ka_red, Ka_green, Ka_blue;
	//	float Kd_red, Kd_green, Kd_blue;
	//	float Specular;
	//};

	class RENDER_DECLSPEC Mesh
	{
		public:

			// friend class decleration
			friend class Rasterizer;
			friend class MD2Loader;

			// constructor and destructor
			Mesh	(void);
			Mesh	(const Mesh &obj);
			virtual ~Mesh	(void);

			// operators
			Mesh& operator=			(const Mesh& obj);	

			// Accessors
			inline int GetNumVerts	(void) const { return m_numVerts; }
			inline int GetNumPolys	(void) const { return m_numPolys; }
			inline int GetNumPolysOnScreen(void) const { return m_onScreenPolys; }
			inline int GetNumVertsOnScreen(void) const { return m_onScreenVerts; }

			inline void SetSpecularity(float specular) { m_specular = specular; }
			void SetAmbientReflection(float red, float green, float blue);
			void SetDiffuseReflection(float red, float green, float blue);

			// mesh operatoins
			void Transform				(const Maths::Matrix4& left, TRANSFORM_TYPE type);
			void Dehomogenise			(void);
			void Sort					(void);
			void CalculateVertsNormals	(void);
			void CalculateBackfaces		(const Maths::Vector4& cameraPos);
			bool CullPolygons			(const ViewFrustum& frustum, const Maths::Vector4& camPos);

			// comparison for polygon sorting 
			static bool GreaterThan		(const renderer::Polygon& poly1, const renderer::Polygon& poly2);
	
			//Lighting functions
			void CalculateFlatLightingDirectional	( const renderer::LightDirectional& light, int numLights, const Maths::Vector4& cameraPos, const Maths::Matrix4& view );
			void CalculateFlatLightingPoint			( const std::vector<LightPoint>& light, int numLight, const Maths::Vector4& camera);
			void CalculateLightingDirectional		( const renderer::LightDirectional& light, int numLights, const Maths::Vector4& camera);
			void CalculateLightingPoint				( const std::vector<LightPoint>& light, int numLight, const Maths::Vector4& camera);
			void CalculateLightingAmbient			( const renderer::LightAmbient& light );

			// reseting mesh data
			void ResetPolyColours	(void);
			void ResetVertsColours	(void);

		protected:
			// member variables
			Gdiplus::Color*		m_palette;
			//Maths::Vector4*		m_verts;
			boost::shared_array<Maths::Vector4> m_verts;
			renderer::Vertex*	m_transformed;
			Polygon*			m_polys;
			UVCoords*			m_TexUVs;
			BYTE*				m_texture;
			float				m_ka_red, m_ka_green, m_ka_blue;
			float				m_kd_red, m_kd_green, m_kd_blue;
			float				m_specular;
			int					m_numVerts;
			int					m_numPolys;
			int					m_onScreenPolys;
			int					m_onScreenVerts;
			int					m_numTexUVs;
			int					m_textureWidth;
			bool				m_hasTexture;
			bool				m_noLight;
	};

} // end of namespace renderer

#endif // end of #ifndef _MESH_H_