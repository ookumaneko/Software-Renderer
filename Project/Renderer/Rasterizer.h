#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include <windows.h>
#include <gdiplus.h>
#include "ZBuffer.h"
#include "RendererLibDef.h"
#include <boost/shared_ptr.hpp>

namespace renderer
{
	// forward declerations
	class Span;
	class Edge;
	class Vertex;
	class Mesh;

	class RENDER_DECLSPEC Rasterizer
	{
		public:
			
			// ---- constructor and destructor ---//
			Rasterizer(void);
			Rasterizer(bool backfaceCulling, int width, int height);
			~Rasterizer(void);

			// ------Accessors---------//
			inline const Gdiplus::Bitmap* GetBitmap(void) const { return m_bitmap.get(); }
			inline Gdiplus::Bitmap*	   GetBitmap(void)			{ return m_bitmap.get(); }			
			
			inline void EnableBackfaceCulling(bool enable)		{ m_backfaceCulling = enable; }

			//---------routine methods--------//
			void Clear	(const Gdiplus::Color& col);
			void Begin	(const Gdiplus::Color& col);
			void End	(void);


			//-----Public Draw Calls--------//
			void DrawWireframe		( Mesh *obj );
			void DrawSolidGDI		( Mesh *obj, const int size);
			void DrawSolidFlat		( Mesh *obj );
			void DrawSolidGouraud	( Mesh *obj );
			void DrawTexturedFlat	( Mesh *obj );
			void DrawTextureGouraud ( Mesh *obj );

			//---------Text Drawing Methods----//
			void DrawText			( TCHAR mes[], float &x, float &y );
			void DrawTextPos		( TCHAR mes[], float x, float y );
			void DrawTextArea		( const Gdiplus::RectF& bound, const Gdiplus::Color& col );
		
		private:
			
			//---------Culling----------//
			bool CheckCull			( Vertex &v1, Vertex &v2, Vertex &v3);

			//---------Wireframe--------//
			void DrawSolidLines		( Mesh *obj, int p);
			void DrawLine			( float x1, float y1, float z1, float x2, float y2, float z2 );

			//---------GDI+ Flat--------//
			void FillPolygonsGDI	( Mesh *obj, int p);

			//--------Flat Shading------//
			void FillPolygonsFlat	( const Vertex& v1, const Vertex& v2, const Vertex& v3, const Gdiplus::Color &col);
			void DrawSpansFlat		( const Edge &e1, const Edge &e2, const Gdiplus::Color& col);
			void DrawSpan			( const Span& span, int y, const Gdiplus::Color& col );

			//--------Gouraud Shading---//
			void FillPolygonsGouraud (const Vertex& v1, const Vertex& v2, const Vertex& v3);
			void DrawSpansGouraud	( const Edge &e1, const Edge &e2 );
			void DrawSpan			( const Span& span, int y );			
			
			//--------Textured Flat-----//
			void DrawSpansTextured	( const Edge &e1, const Edge &e2, const Gdiplus::Color& col, const Mesh* obj);
			void FillTextureFlat	( const Vertex& v1, const Vertex& v2, const Vertex& v3, const Gdiplus::Color &col, const Mesh* obj);
			void DrawSpan			( const Span& span, int y, const Gdiplus::Color& col, const Mesh* obj );

			//------Textured Gouraud-----//
			void FillTextureGouraud ( const Mesh* obj, const Vertex& v1, const Vertex& v2, const Vertex& v3 );
			void DrawSpansTexGouraud( const Edge &e1, const Edge &e2, const Mesh* obj );
			void DrawSpan			( const Span& span, int y, const Mesh* obj );

			//---------Phong Shading-----//
			void FillPhong			( const Mesh* obj, const Vertex& v1, const Vertex& v2, const Vertex& v3 );
			void DrawSpansPhong		( const Edge &e1, const Edge &e2, const Mesh* obj );
			void DrawPhong			( const Span& span, int y, const Mesh* obj );

			//-----Liner Interpolation----//
			int				Lerp	( float start, float end, float amount );
			float			Lerp	( int start, int end, float amount );
			Gdiplus::Color  Lerp	( const Gdiplus::Color &start, const Gdiplus::Color &end, float amount);

		private:

			//------Member Data----------//
			UINT					m_pixels[600][800];
			ZBuffer					m_zbuffer;
			boost::shared_ptr<Gdiplus::Bitmap>		m_bitmap;
			boost::shared_ptr<Gdiplus::Graphics>		m_graphics;
			Gdiplus::RectF			m_bounds;
			Gdiplus::Rect			m_screenBounds;
			Gdiplus::BitmapData		m_bitmapData;

			int						m_width;
			int						m_height;

			bool					m_backfaceCulling;
	};

} // end of namespace
#endif // end of _RASTERIZER_H_