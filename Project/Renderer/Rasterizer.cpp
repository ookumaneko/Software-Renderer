#include "Rasterizer.h"
#include "Mesh.h"
#include "EdgeSpan.h"
#include "Mesh.h"
#include "Vertex.h"
using namespace renderer;
using namespace Gdiplus;


//-----------------------------------------------------------------------------//
//-----------------------Constructors and Destructor---------------------------//
//-----------------------------------------------------------------------------//

Rasterizer::Rasterizer(void)
{
	//m_width						= 800;
	//m_height					= 600;
	//m_bitmap					= new Gdiplus::Bitmap( m_width, m_height, PixelFormat32bppARGB );
	//m_graphics					= new Gdiplus::Graphics( m_bitmap );
	m_backfaceCulling			= true;
	m_bounds					= Gdiplus::RectF( 0, 0, m_width, 120 );
	m_screenBounds				= Gdiplus::Rect( 0, 0, m_width, m_height );

	//this->m_bitmapData			= new Gdiplus::BitmapData;
	m_bitmapData.Height		= m_height;
	m_bitmapData.Width			= m_width;
	m_bitmapData.PixelFormat	= PixelFormat32bppARGB; 
	m_bitmapData.Stride		= 4 * m_bitmapData.Width;

	for ( int y = 0; y < m_height; ++y )
	{
		for ( int x = 0; x < m_width; ++x )
		{
			m_pixels[y][x] = 0;
		}
	}
}

Rasterizer::Rasterizer(bool backfaceCulling, int width, int height)
{
	m_width						= width;
	m_height					= height;
	m_bitmap					= boost::shared_ptr<Gdiplus::Bitmap>( new Gdiplus::Bitmap( m_width, m_height, PixelFormat32bppARGB ) );
	m_graphics 					= boost::shared_ptr<Gdiplus::Graphics>( new Gdiplus::Graphics( m_bitmap.get() ) );
	m_backfaceCulling			= backfaceCulling;
	m_bounds					= Gdiplus::RectF( 0, 0, m_width, 120 );
	m_screenBounds				= Gdiplus::Rect( 0, 0, m_width, m_height );

	//this->m_bitmapData			= new Gdiplus::BitmapData();
	m_bitmapData.Height			= m_height;
	m_bitmapData.Width			= m_width;
	m_bitmapData.PixelFormat	= PixelFormat32bppARGB; 
	m_bitmapData.Stride			= 4 * m_bitmapData.Width;
}

Rasterizer::~Rasterizer(void)
{
	//delete m_bitmap;
	//m_bitmap.
	//delete m_graphics;
	//delete m_bitmapData;
	//delete m_screenBounds;
	//m_bitmap = NULL;
	//m_graphics = 0;
	//m_bitmapData = 0;
	//m_screenBounds = 0;
}

//-----------------------------------------------------------------------------//
//-------------------------------Member functions------------------------------//
//-----------------------------------------------------------------------------//

void Rasterizer::Clear(const Gdiplus::Color& col)
{	
	m_graphics->Clear( col );
	//m_zbuffer.Clear();
	//for ( int y = 0; y < m_height; y++ )
	//{
	//	for ( int x = 0; x < m_width; x++ )
	//	{
	//		_pixels[y][x] = Gdiplus::Color::Black;
	//	}
	//}
}

void Rasterizer::Begin(const Gdiplus::Color& col)
{
	m_zbuffer.Clear();
	for ( int y = 0; y < m_height; y++ )
	{
		for ( int x = 0; x < m_width; x++ )
		{
			m_pixels[y][x] = col.GetValue();		// clear pixel colour info
			//_zbuffer._buffer[y][x] = -500.0f;	// clear zbuffer
		}
	}
}

void Rasterizer::End()
{
	m_bitmapData.Scan0 = (VOID*)m_pixels;
	m_bitmap->LockBits( &m_screenBounds, ImageLockModeWrite | ImageLockModeUserInputBuf, m_bitmap->GetPixelFormat(), &m_bitmapData );
	m_bitmap->UnlockBits( &m_bitmapData );
}


//-----------------------------------------------------------------------------//
//-------------------------------Public Draw methods---------------------------//
//-----------------------------------------------------------------------------//

void Rasterizer::DrawWireframe(renderer::Mesh *obj)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;

	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					DrawSolidLines( obj, p );
					obj->m_onScreenPolys++;
				}
			}
			else
			{
				DrawSolidLines( obj, p );
				obj->m_onScreenPolys++;
			}
		}
	}
}

void Rasterizer::DrawSolidGDI(renderer::Mesh *obj, const int size)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;
	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					FillPolygonsGDI( obj, p );
					obj->m_onScreenPolys++;
				}
			}
			else
			{
				FillPolygonsGDI( obj, p );
				obj->m_onScreenPolys++;
			}
		}
	}
}

void Rasterizer::DrawSolidFlat(renderer::Mesh *obj)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;
	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					obj->m_onScreenPolys++;
					FillPolygonsFlat( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
									  obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
									  obj->m_transformed[ obj->m_polys[p].Indices[2] ],
									  obj->m_polys[p].Colour );
				}
			}
			else
			{
				obj->m_onScreenPolys++;
				FillPolygonsFlat( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
								  obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
								  obj->m_transformed[ obj->m_polys[p].Indices[2] ],
								  obj->m_polys[p].Colour );
			}
		}
	}
}

void Rasterizer::DrawSolidGouraud(renderer::Mesh *obj)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;
	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					obj->m_onScreenPolys++;
					FillPolygonsGouraud( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
										 obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
										 obj->m_transformed[ obj->m_polys[p].Indices[2] ] );
				}
			}
			else
			{
				obj->m_onScreenPolys++;
				FillPolygonsGouraud( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
									 obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
									 obj->m_transformed[ obj->m_polys[p].Indices[2] ] );
			}
		}
	}
}

void Rasterizer::DrawTexturedFlat(renderer::Mesh *obj)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;
	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			//set temp uv coordinates in vertices
			obj->m_transformed[ obj->m_polys[p].Indices[0] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[0] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[0] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[0] ].V;
			obj->m_transformed[ obj->m_polys[p].Indices[1] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[1] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[1] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[1] ].V;
			obj->m_transformed[ obj->m_polys[p].Indices[2] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[2] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[2] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[2] ].V;

			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					obj->m_onScreenPolys++;
					FillTextureFlat( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
									 obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
									 obj->m_transformed[ obj->m_polys[p].Indices[2] ],
									 obj->m_polys[p].Colour, obj );
				}
			}
			else
			{
				obj->m_onScreenPolys++;
				FillTextureFlat( obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
								 obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
								 obj->m_transformed[ obj->m_polys[p].Indices[2] ],
								 obj->m_polys[p].Colour, obj );
			}
		}
	}
}

void Rasterizer::DrawTextureGouraud(renderer::Mesh *obj)
{
	obj->m_onScreenPolys = 0;
	obj->m_onScreenVerts = 0;
	for ( int p = 0; p < obj->m_numPolys; ++p )
	{
		if ( !CheckCull( obj->m_transformed[ obj->m_polys[p].Indices[0] ], obj->m_transformed[ obj->m_polys[p].Indices[1] ], obj->m_transformed[ obj->m_polys[p].Indices[2] ] ) )
		{
			//set temp uv coordinates in vertices
			obj->m_transformed[ obj->m_polys[p].Indices[0] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[0] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[0] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[0] ].V;
			obj->m_transformed[ obj->m_polys[p].Indices[1] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[1] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[1] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[1] ].V;
			obj->m_transformed[ obj->m_polys[p].Indices[2] ].U = obj->m_TexUVs[ obj->m_polys[p].UvIndices[2] ].U;
			obj->m_transformed[ obj->m_polys[p].Indices[2] ].V = obj->m_TexUVs[ obj->m_polys[p].UvIndices[2] ].V;

			if ( m_backfaceCulling )
			{
				if ( obj->m_polys[p].IsCulled == false )
				{
					obj->m_onScreenPolys++;
					FillTextureGouraud( obj, obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
										obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
										obj->m_transformed[ obj->m_polys[p].Indices[2] ] );
				}
			}
			else
			{
				obj->m_onScreenPolys++;
				FillTextureGouraud( obj, obj->m_transformed[ obj->m_polys[p].Indices[0] ], 
					obj->m_transformed[ obj->m_polys[p].Indices[1] ], 
					obj->m_transformed[ obj->m_polys[p].Indices[2] ] );
			}
		}
	}
}

bool Rasterizer::CheckCull(renderer::Vertex &v1, renderer::Vertex &v2, renderer::Vertex &v3)
{
	if ( (v1.Position.X < 0 || v1.Position.X > m_width - 1 || 
		  v1.Position.Y < 0 || v1.Position.Y > m_height - 1 ) &&
		 (v2.Position.X < 0 || v2.Position.X > m_width - 1 || 
		  v2.Position.Y < 0 || v2.Position.Y > m_height - 1 ) &&
		 (v3.Position.X < 0 || v3.Position.X > m_width - 1 || 
		  v3.Position.Y < 0 || v3.Position.Y > m_height - 1 ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------//
//-------------------------------Private Draw methods--------------------------//
//-----------------------------------------------------------------------------//


// -----------------------GDI+ Flat shading------------------------//

void Rasterizer::FillPolygonsGDI(renderer::Mesh *obj, int p)
{
	PointF list[3];
	SolidBrush brush( obj->m_polys[p].Colour );
	
	for ( int i = 0; i < 3; ++i )
	{
		list[i].X = obj->m_transformed[ obj->m_polys[p].Indices[i] ].Position.X;
		list[i].Y = obj->m_transformed[ obj->m_polys[p].Indices[i] ].Position.Y;
	}

	m_graphics->FillPolygon( &brush, list, 3 );
}

//-----------------------------------------------------------------------------//
//---------------------------Public Text Drawing methods-----------------------//
//-----------------------------------------------------------------------------//

void Rasterizer::DrawTextW(TCHAR mes[], float &x, float &y)
{
   // Initialize arguments.
   Gdiplus::Font myFont( L"Arial", 8 );
   Gdiplus::RectF layoutRect( x, y, 100, 20 );
   Gdiplus::StringFormat format;
   format.SetAlignment( Gdiplus::StringAlignmentCenter );
   Gdiplus::SolidBrush blackBrush( Gdiplus::Color::White );

   // Draw string.
   m_graphics->DrawString(
	   mes,
	   64,
	   &myFont,
	   layoutRect,
	   &format,
	   &blackBrush );

   y += (float)layoutRect.Height + 7.5f;
   if ( y >= m_bounds.Height - 20 )
   {
	   y = 0;
	   x += layoutRect.Width + 10;
   }
}

void Rasterizer::DrawTextPos(TCHAR mes[], float x, float y) 
{
   // Initialize arguments.
   Gdiplus::Font myFont( L"Arial", 8 );
   Gdiplus::RectF layoutRect( x, y, m_width, m_height );
   Gdiplus::StringFormat format;
   format.SetAlignment( Gdiplus::StringAlignmentNear );
   Gdiplus::SolidBrush blackBrush( Gdiplus::Color::White );

   // Draw string.
   m_graphics->DrawString(
	   mes,
	   64,
	   &myFont,
	   layoutRect,
	   &format,
	   &blackBrush );
}

void Rasterizer::DrawTextArea(const Gdiplus::RectF& bound, const Gdiplus::Color& col)
{
	Gdiplus::SolidBrush blackBrush( col );
	m_bounds = bound;
	m_graphics->FillRectangle( &blackBrush, bound );
}


//-----------------------------------------------------------------------------//
//--------------------------Linear Interpolation methods-----------------------//
//-----------------------------------------------------------------------------//

int Rasterizer::Lerp(float start, float end, float amount)
{
	float r = 0.5f;
	return ( ( start * ( 1.0f - amount ) ) + ( end * amount ) + r );
}

float Rasterizer::Lerp(int start, int end, float amount)
{
	return ( (start) * (1 - amount) ) + ( end * amount );
}

Color Rasterizer::Lerp(const Gdiplus::Color &start, const Gdiplus::Color &end, float amount)
{
	float r, g, b;
	r = ( ( start.GetR() * (1.0f - amount) ) + ( end.GetR() * amount ) );
	g = ( ( start.GetG() * (1.0f - amount) ) + ( end.GetG() * amount ) );
	b = ( ( start.GetB() * (1.0f - amount) ) + ( end.GetB() * amount ) );

	if ( r > 255.0f ) r = 255.0f;
	if ( g > 255.0f ) g = 255.0f;
	if ( b > 255.0f ) b = 255.0f;
	if ( r < 0.0f ) r = 0.0f;
	if ( g < 0.0f ) g = 0.0f;
	if ( b < 0.0f ) b = 0.0f;
	
	return Gdiplus::Color::MakeARGB( 255, (BYTE)r, (BYTE)g, (BYTE)b );
}

