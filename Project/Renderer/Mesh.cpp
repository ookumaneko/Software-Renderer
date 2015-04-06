#include "Mesh.h"
#include <algorithm>
#include <functional>
#include <math.h>
#include "Camera.h"
#include "MathHelper.h"
#include "Renderer.h"

using namespace Maths;
using namespace std;

namespace renderer
{

//Material::Material() : Ka_red( 1.0f ), Ka_green( 1.0f ), Ka_blue( 1.0f )
//					   Kd_red( 1.0f ), Kd_green( 1.0f ), Kd_blue( 1.0f ),
//					   Specular( 1.0f )
//{
//}

Mesh::Mesh(void)
{
	this->m_numPolys		= 0;
	this->m_numVerts		= 0;
	this->m_onScreenPolys	= 0;
	this->m_onScreenVerts	= 0;
	//this->m_verts			= 0;
	this->m_transformed		= 0;
	this->m_polys			= 0;
	this->m_ka_red			= 1.0f;
	this->m_ka_green		= 1.0f;
	this->m_ka_blue			= 1.0f;
	this->m_kd_red			= 1.0f;
	this->m_kd_green		= 1.0f;
	this->m_kd_blue			= 1.0f;
	this->m_specular		= 1.0f;
	this->m_texture			= 0;
	this->m_palette			= 0;
	this->m_numTexUVs		= 0;
	this->m_TexUVs			= 0;
	this->m_textureWidth	= 0;
	this->m_hasTexture		= false;
	this->m_noLight			= true;
}

Mesh::Mesh(const Mesh &obj)
{
	*this = obj;
}

Mesh::~Mesh(void)
{
	delete [] m_polys;
	m_polys = 0;

	//delete [] m_verts;
	//m_verts = 0;

	delete [] m_transformed;
	m_transformed = 0;

	//if ( this->m_hasTexture )
	{
		delete [] m_TexUVs;
		m_TexUVs = 0;

		delete [] m_texture;
		m_texture = 0;

		delete [] m_palette;
		m_palette = 0;
	}
}

Mesh& Mesh::operator =(const Mesh& obj)
{
	m_polys			= new Polygon[ obj.m_numPolys ];
	//m_verts			= new Maths::Vector4[ obj.m_numVerts ];
	m_verts			= boost::shared_array<Vector4>( new Vector4[obj.m_numVerts] );
	m_transformed	= new Vertex[ obj.m_numVerts ];
	
	this->m_numPolys = obj.m_numPolys;
	this->m_numVerts = obj.m_numVerts;
	
	for ( int i = 0; i < m_numPolys; ++i )
	{
		for ( int j = 0; j < 3; ++j )
		{
			this->m_polys[i].Indices[j]		= obj.m_polys[i].Indices[j];
			this->m_polys[i].UvIndices[j]	= obj.m_polys[i].UvIndices[j];
		}
	}

	for ( int i = 0; i < m_numVerts; ++i )
	{
		this->m_verts.get()[i]		= obj.m_verts.get()[i];
		this->m_transformed[i]	= obj.m_transformed[i];
	}

	// only if it holds a texture
	if ( obj.m_hasTexture )
	{
		// texture MUST have same width and height in MD2 models
		int ts			= obj.m_textureWidth * obj.m_textureWidth;
		m_texture		= new BYTE[ ts ];
		m_textureWidth	= obj.m_textureWidth;
		m_palette		= new Gdiplus::Color[256]; // rgb 256 palette 
		m_TexUVs		= new renderer::UVCoords[ obj.m_numTexUVs ];
		m_hasTexture	= true;

		for ( int i = 0; i < obj.m_numTexUVs; ++i )
		{
			m_TexUVs[i].U = obj.m_TexUVs[i].U;
			m_TexUVs[i].V = obj.m_TexUVs[i].V;
		}

		for ( int i = 0; i < 256; ++i )
		{
			m_palette[i] = obj.m_palette[i];
		}

		for ( int i = 0; i < ts; ++i )
		{
			m_texture[i] = obj.m_texture[i];
		}
	}
	else
	{
		m_texture		= 0;
		m_textureWidth	= 0;
		m_palette		= 0;
		m_TexUVs		= 0;
		m_hasTexture	= false;
	}

	this->m_ka_red		= obj.m_ka_red;
	this->m_ka_green	= obj.m_ka_green;
	this->m_ka_blue		= obj.m_ka_blue;
	this->m_kd_red		= obj.m_kd_red;
	this->m_kd_green	= obj.m_kd_green;
	this->m_kd_blue		= obj.m_kd_blue;
	this->m_specular	= obj.m_specular;
	this->m_hasTexture	= obj.m_hasTexture;
	this->m_noLight		= obj.m_noLight;

	return *this;
}

void Mesh::SetAmbientReflection(float red, float green, float blue)
{
	m_ka_red	= red;
	m_ka_green	= green;
	m_ka_blue	= blue;
}

void Mesh::SetDiffuseReflection(float red, float green, float blue)
{
	m_kd_red	= red;
	m_kd_green	= green;
	m_kd_blue	= blue;;
}

void Mesh::Transform(const Maths::Matrix4 &left, renderer::TRANSFORM_TYPE type)
{	
	Maths::Vector4 v;

	switch ( type )
	{
		case TRANSFORM_LOCAL:
			for ( int i = 0; i < m_numVerts; ++i )
			{
				Matrix4::Transform( left, m_verts[i],  v );
				Vertex vert( v );
				m_transformed[i] = vert;
			}
			break;

		case TRANSFORM_TRANSFORMED:
			for ( int i = 0; i < m_numVerts; ++i )
			{
				Matrix4::Transform( left, m_transformed[i].Position,  v );
				m_transformed[i].Position = v;
			}
			break;
		
		case TRANSFORM_PROJECTION:
			for ( int i = 0; i < m_numVerts; ++i )
			{
				m_transformed[i].SavedZ = m_transformed[i].Position.Z;
				Matrix4::Transform( left, m_transformed[i].Position,  v );
				m_transformed[i].Position = v;
			}
			break;

		case TRANSFORM_MODEL:
			break;

		default:
			break;
	}
}

void Mesh::Dehomogenise()
{
	for ( int i = 0; i < m_numVerts; ++i )
	{
		m_transformed[i].Position.Dehomogenize();
	}
}

void Mesh::CalculateBackfaces(const Maths::Vector4& cameraPos)
{
	for ( int i = 0; i < m_numPolys; ++i )
	{
		Maths::Vector4 a = ( m_transformed[ m_polys[i].Indices[0] ].Position ) - ( m_transformed[ m_polys[i].Indices[1] ].Position );
		Maths::Vector4 b = ( m_transformed[ m_polys[i].Indices[2] ].Position ) - ( m_transformed[ m_polys[i].Indices[1] ].Position );
		Maths::Vector4 c = b.CrossProduct(a);
		Maths::Vector4 d;

		m_polys[i].Normal = c;
		c.Normalize();
		m_polys[i].NormalN = c;

		Vector4 p = m_transformed[ m_polys[i].Indices[0] ].Position  - cameraPos;
		if ( p.DotProduct(c) > 0.0f ) 
		{
			m_polys[i].IsCulled = true;
			m_transformed[ m_polys[i].Indices[0] ].IsCulled = true;
			m_transformed[ m_polys[i].Indices[1] ].IsCulled = true;
			m_transformed[ m_polys[i].Indices[2] ].IsCulled = true;
		}
		else
		{
			m_polys[i].IsCulled = false;
			m_transformed[ m_polys[i].Indices[0] ].IsCulled = false;
			m_transformed[ m_polys[i].Indices[1] ].IsCulled = false;
			m_transformed[ m_polys[i].Indices[2] ].IsCulled = false;
		}
	}
}

//-------------------------------//
//--------Sorting----------------//
//------------------------------//

void Mesh::Sort()
{
	float avr = 0;

	//calculate the average Z of each polygons
	for ( int i = 0; i < m_numPolys; ++i )
	{
		for ( int j = 0; j < 3; ++j )
		{
			avr += m_transformed[ m_polys[i].Indices[j] ].Position.Z;
		}
		avr *= 0.3f;
		m_polys[i].AverageDepth = avr;
		avr = 0;
	}

	std::sort( m_polys, m_polys + m_numPolys, Mesh::GreaterThan );
}

bool Mesh::GreaterThan(const renderer::Polygon& poly1, const renderer::Polygon& poly2)
{
	return ( poly1.AverageDepth < poly2.AverageDepth );
}


//-----------------------------------------------//
//--------------------Lightings------------------//
//-----------------------------------------------//

void Mesh::CalculateFlatLightingDirectional(const LightDirectional &light, int numLights, const Vector4& cameraPos, const Matrix4& view)
{
	Maths::Vector4 total, temp;
	Maths::Vector4 reflect;
	Maths::Vector4 v = cameraPos;
	Maths::Vector4 l( light.Position.X, light.Position.Y, light.Position.Z, 1.0f  ); 
	Maths::Vector4 n( 0, 0, 0 );
	Maths::Vector4 t, halfWay;
	BYTE r, g, b;
	float spec = 0;
	float diff = 0;
	float ave = 0;

	m_noLight = false;

	//workout the "halfway" vector for specularity
	ave = v.Length();
	//halfWay = ( v + l ) / ave;
	//halfWay.Normalize();

	//normalize the light position
	l.Normalize();

	for ( int i = 0; i < m_numPolys; ++i )
	{
		if ( !m_polys[i].IsCulled )
		{
			//reset the colout to black
			total.X = 0; //Red
			total.Y = 0; //green
			total.Z = 0; //blue

			for ( int j = 0; j < numLights; ++j )
			{
				//store intensity to corresponding variables
				//modulate intensity with coresponding reflectance co-efficient values
				temp.X = light.Colour.GetR() * light.Intensity.X;
				temp.Y = light.Colour.GetG() * light.Intensity.Y;
				temp.Z = light.Colour.GetB() * light.Intensity.Z;

				//reflect = ( 2 * ( m_polys[i]._normal.DotProduct( light._position ) ) * ( m_polys[i]._normal - light );
				n.SetValues( m_polys[i].Normal.X, m_polys[i].Normal.Y, m_polys[i].Normal.Z, 1.0f );
				n.Normalize();

				//attentuate the rgb values with lambertian attenuation
				diff = max( 0.0f, l.DotProduct( n ) );

				//calculate specular coponent
				Vector4 toEye;
				Matrix4::Transform( view, m_transformed[ m_polys[i].Indices[0] ].Position, toEye );
				toEye.Normalize();

				float r = max( 0, m_transformed[ m_polys[i].Indices[0] ].Normal.DotProduct( l ) );
				Vector4 reflect = m_transformed[ m_polys[i].Indices[0] ].Normal;
				reflect.Multiply( 2 * r );
				reflect.Subtract( l );
			
				//Vector4 toEye = m_transformed[ m_polys[i]._indices[0] ]._position - viewer;
				//Vector4 reflect = ( n - l ) * ( 2 * ( n.DotProduct( l ) ) );
				toEye.Normalize();
				reflect.Normalize();
				float specPower = 1.0f;
				float spec = 0; //max( 0, pow( max( 0.0f, reflect.DotProduct( toEye ) ), specPower ) ) * m_specular;

				if ( diff <= 0.0f )
					spec = 0.0f;

				temp.X =  temp.X * ( (diff + spec) * m_kd_red );
				temp.Y =  temp.Y * ( (diff + spec) * m_kd_green );
				temp.Z =  temp.Z * ( (diff + spec) * m_kd_blue );

				total = total + temp;
			}

			//clamp the values
			if (total.X > 255) total.X = 255;
			if (total.Y > 255) total.Y = 255;
			if (total.Z > 255) total.Z = 255;
			if (total.X < 0) total.X = 0;
			if (total.Y < 0) total.Y = 0;
			if (total.Z < 0) total.Z = 0;

			r = (BYTE)total.X;
			g = (BYTE)total.Y;
			b = (BYTE)total.Z;

			m_polys[i].Colour = Gdiplus::Color::MakeARGB(255, r, g, b);
		}
	}
}

void Mesh::CalculateFlatLightingPoint(const std::vector<LightPoint>& light, int numLights, const Vector4& camera)
{
	Maths::Vector4 l;
	Maths::Vector4 temp, result, n, p;
	BYTE r, g, b;
	float distance = 0;
	float att = 0;
	float a = 0.05f;
	float bb = 0.05f;
	float c = 0.05f;
	float dif, spec;
	m_noLight = false;

	for ( int i = 0; i < m_numPolys; ++i )
	{
		result.X = 0; //Red
		result.Y = 0; //green
		result.Z = 0; //blue

		if ( !m_polys[i].IsCulled )
		{
			for ( int j = 0; j < numLights; ++j )
			{
				//get the position of the light and calculate the 
				//distance between the object and the lifght
				p = light[j].Position;
				l = p - m_transformed[ m_polys[i].Indices[0] ].Position;
				distance = l.Length();

				//calculate the attenuation value
				att = 1 / (a + ( distance * bb ) + ( distance * distance ) * c );
				if ( att < 0)
					att = 0;
				
				temp.X = light[j].Colour.GetR();
				temp.Y = light[j].Colour.GetG();
				temp.Z = light[j].Colour.GetB();
				
				// get the normalized value of the polygon normals
				//n = m_polys[i]._normalN;
				//n.Normalize();

				// calculate the diffuse value
				dif = max( l.DotProduct( m_polys[i].NormalN ), 0.0f ) * att;
				// multiply dif with materials

				// calculate the speculation
				//Vector4 toEye = m_transformed[ m_polys[i]._indices[0] ]._position - camera;
				//Vector4 reflect = ( n - l ) * ( 2 * ( n.DotProduct( l ) ) );
				//toEye.Normalize();
				//reflect.Normalize();
				//float specPower = 1.0f;
				//float spec = pow( max( reflect.DotProduct( toEye ), 0.0f ), specPower ) * att;

				Vector4 toEye = m_transformed[ m_polys[i].Indices[0] ].Position - camera;
				Vector4 half = camera + p / 2;
				toEye.Normalize();
				half.Normalize();
				float specPower = 1.0f;
				float spec = pow( max( n.DotProduct( half ), 0.0f ), specPower ) * att;

				temp.X =  temp.X * ( (dif + spec) * m_kd_red );
				temp.Y =  temp.Y * ( (dif + spec) * m_kd_green );
				temp.Z =  temp.Z * ( (dif + spec) * m_kd_blue );

				result += temp;
			}

			//set colour
			if ( result.X > 255.0f ) result.X = 255;
			if ( result.Y > 255.0f ) result.Y = 255;
			if ( result.Z > 255.0f ) result.Z = 255;
			if ( result.X < 0.0f ) result.X = 0;
			if ( result.Y < 0.0f ) result.Y = 0;
			if ( result.Z < 0.0f ) result.Z = 0;
			r = (BYTE)result.X;
			g = (BYTE)result.Y;
			b = (BYTE)result.Z;

			m_polys[i].Colour = Gdiplus::Color::MakeARGB( 255, r, g, b );
		}
	}
}



void Mesh::CalculateLightingDirectional(const LightDirectional& light, int numLights, const Vector4& camera)
{
	Maths::Vector4 total;
	Maths::Vector4 temp;
	Maths::Vector4 l( light.Position.X, light.Position.Y, light.Position.Z, 1.0f );
	Maths::Vector4 n( 0, 0, 0, 0 );
	BYTE r, g, b;
	float diff, spec = 0;

	m_noLight = false;
	l.Normalize();

	for ( int i = 0; i < m_numVerts; ++i )
	{
		if ( !m_transformed[i].IsCulled )
		{
			//reset the colout to black
			total.X = 0; //Red
			total.Y = 0; //green
			total.Z = 0; //blue

			for ( int j = 0; j < numLights; ++j )
			{
				Maths::Vector4 d;
				
				//modulate intensity with coresponding reflectance co-efficient values
				temp.X = light.Colour.GetR() * light.Intensity.X;
				temp.Y = light.Colour.GetG() * light.Intensity.Y;
				temp.Z = light.Colour.GetB() * light.Intensity.Z;

				n = m_transformed[i].Normal; 
				n.Normalize();

				//attentuate the rgb values with lambertian attenuation
				diff = max(0.0, l.DotProduct( n ));
				
				Vector4 toEye = m_transformed[i].Position - camera;
				Vector4 reflect = ( n - l ) * ( 2 * ( n.DotProduct( l ) ) );
				toEye.Normalize();
				reflect.Normalize();
				float specPower = 1.0f;
				spec = pow( max( reflect.DotProduct( toEye ), 0.0f ), specPower )  * 0.01f;

				if ( diff <= 0.0f )
					spec = 0.0f;

				temp.X =  temp.X * ( (diff + spec) * m_kd_red );
				temp.Y =  temp.Y * ( (diff + spec) * m_kd_green );
				temp.Z =  temp.Z * ( (diff + spec) * m_kd_blue );

				//temp.X =  temp.X * ( diff * m_kd_red + spec ) );
				//temp.Y =  temp.Y * ( diff * m_kd_green + spec ) );
				//temp.Z =  temp.Z * ( diff * m_kd_blue + spec ) );
				total = total + temp;
			}

			if ( total.X > 255.0f ) total.X = 255.0f;
			if ( total.Y > 255.0f ) total.Y = 255.0f;
			if ( total.Z > 255.0f ) total.Z = 255.0f;
			if ( total.X < 0.0f ) total.X = 0.0f;
			if ( total.Y < 0.0f ) total.Y = 0.0f;
			if ( total.Z < 0.0f ) total.Z = 0.0f;

			r = (BYTE)total.X;
			g = (BYTE)total.Y;
			b = (BYTE)total.Z;

			m_transformed[i].Colour = Gdiplus::Color::MakeARGB( 255, r, g, b );
		}
	}
}

void Mesh::CalculateLightingPoint( const std::vector<LightPoint>& light, int numLight, const Maths::Vector4& camera)
{
	Maths::Vector4 l;
	Maths::Vector4 temp, result, n, p;
	Maths::Vector4 cof( 1.0f, 1.0f, 10.0f );
	BYTE r, g, b;
	float distance = 0;
	float att = 0;
	float a = 0.05f;
	float bb = 0.05f;
	float c = 0.05f;
	float dif, spec;

	m_noLight = false;

	for ( int i = 0; i < m_numVerts; ++i )
	{
		if ( !m_transformed[i].IsCulled )
		{
			result.X = 0; //Red
			result.Y = 0; //green
			result.Z = 0; //blue

			for ( int j = 0; j < numLight; ++j )
			{
				p = light[j].Position;
				l = p - m_transformed[i].Position;
				distance = l.Length();

				//calculate the attenuation value
				att = 1 / (a + ( distance * bb ) + ( distance * distance ) * c );
				if ( att < 0 )
					att = 0;

				temp.X = light[j].Colour.GetR();
				temp.Y = light[j].Colour.GetG();
				temp.Z = light[j].Colour.GetB();
				
				n = m_transformed[i].Normal;
				n.Normalize();

				dif = max( 0.0, l.DotProduct( n ) ) * att;

				// calculate the speculation
				//Vector4 toEye = m_transformed[i].Position - camera;
				//Vector4 half = camera + p / 2;
				//toEye.Normalize();
				//half.Normalize();
				//float specPower = 1.0f;
				//float spec = pow( max( n.DotProduct( half ), 0.0f ), specPower ) * att;
				Vector4 toEye = m_transformed[i].Position - camera;
				Vector4 reflect = ( n - l ) * ( 2 * ( n.DotProduct( l ) ) );
				toEye.Normalize();
				reflect.Normalize();
				float specPower = 1.0f;
				float spec = pow( max( reflect.DotProduct( toEye ), 0.0f ), specPower ) * att;

				temp.X =  temp.X * ( (dif + spec) * m_kd_red );
				temp.Y =  temp.Y * ( (dif + spec) * m_kd_green );
				temp.Z =  temp.Z * ( (dif + spec) * m_kd_blue );

				//temp.X =  temp.X * ( dif * m_kd_red ) );
				//temp.Y =  temp.Y * ( dif * m_kd_green ) );
				//temp.Z =  temp.Z * ( dif * m_kd_blue ) );

				result += temp;
			}

			//set colour
			if ( result.X > 255.0f ) result.X = 255.0f;
			if ( result.Y > 255.0f ) result.Y = 255.0f;
			if ( result.Z > 255.0f ) result.Z = 255.0f;
			if ( result.X < 0.0f ) result.X = 0.0f;
			if ( result.Y < 0.0f ) result.Y = 0.0f;
			if ( result.Z < 0.0f ) result.Z = 0.0f;
			r = (BYTE)result.X;
			g = (BYTE)result.Y;
			b = (BYTE)result.Z;
			m_transformed[i].Colour = Gdiplus::Color::MakeARGB( 255, r, g, b );
		}
	}
}

void Mesh::CalculateLightingAmbient( const renderer::LightAmbient& light )
{
	m_noLight = false;

	for ( int i = 0; i < m_numPolys; ++i )
	{
		if ( !m_polys[i].IsCulled )
		{
			float r = ( light.Colour.GetR() * this->m_ka_red )	 + m_polys[i].Colour.GetR();
			float g = ( light.Colour.GetG() * this->m_ka_green ) + m_polys[i].Colour.GetG();
			float b = ( light.Colour.GetB() * this->m_ka_blue )  + m_polys[i].Colour.GetB();
			if ( r > 255.0f ) r = 255.0f;
			if ( g > 255.0f ) g = 255.0f;
			if ( b > 255.0f ) b = 255.0f;
			if ( r < 0.0f ) r = 0.0f;
			if ( g < 0.0f ) g = 0.0f;
			if ( b < 0.0f ) b = 0.0f;

			m_polys[i].Colour = Gdiplus::Color::MakeARGB( 255, (BYTE)r, (BYTE)g, (BYTE)b );
		}
	}
}

void Mesh::ResetPolyColours()
{
	m_onScreenPolys = 0;
	m_noLight = true;
	for ( int i = 0; i < m_numPolys; ++i )
	{
		m_polys[i].Colour = Gdiplus::Color::Black;
	}
}

void Mesh::ResetVertsColours()
{
	m_onScreenVerts = 0;
	m_noLight = true;
	for ( int i = 0; i < m_numVerts; ++i )
	{
		m_transformed[i].Colour = Gdiplus::Color::Black;
	}
}

void Mesh::CalculateVertsNormals()
{
	//reset normals on each vertices
	for ( int i = 0; i < m_numVerts; ++i )
	{
		m_transformed[i].Normal.SetValues( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	for ( int i = 0; i < m_numPolys; ++i )
	{
		if ( !m_polys[i].IsCulled )
		{
			//calculate normal of the polygon
			Maths::Vector4 a = ( m_transformed[ m_polys[i].Indices[0] ].Position ) - ( m_transformed[ m_polys[i].Indices[1] ].Position );
			Maths::Vector4 b = ( m_transformed[ m_polys[i].Indices[0] ].Position ) - ( m_transformed[ m_polys[i].Indices[2] ].Position );
			Maths::Vector4 c = a.CrossProduct(b);

			//Add the surface normal to each vertices
			m_transformed[ m_polys[i].Indices[0] ].Normal += c;
			m_transformed[ m_polys[i].Indices[1] ].Normal += c;
			m_transformed[ m_polys[i].Indices[2] ].Normal += c;

			//increment the tally (number of time normal has been added)
			m_transformed[ m_polys[i].Indices[0] ].Tally++;
			m_transformed[ m_polys[i].Indices[1] ].Tally++;
			m_transformed[ m_polys[i].Indices[2] ].Tally++;
		}
	}

	for ( int i = 0; i < m_numVerts; ++i )
	{
		m_transformed[i].Normal /= m_transformed[i].Tally;
		m_transformed[i].Normal.Normalize();
	}
}

bool Mesh::CullPolygons(const ViewFrustum& frustum, const Maths::Vector4& camPos)
{
	int cullCount = 0;
	for ( int i = 0; i < m_numPolys; ++i )
	{
		if ( m_polys[i].IsCulled )
		{
			cullCount++;
			continue;
		}

		int count = 0;
		for ( int vv = 0; vv < 3; ++vv )
		{
			//Vector4 point = m_transformed[ m_polys[i].Indices[vv] ].Position - camPos;
			Vector4 point = m_transformed[ m_polys[i].Indices[vv] ].Position - m_verts[ m_polys[i].Indices[vv] ];
			float result = point.DotProduct( frustum.Left.Normal );
			if ( result > 0.0f )
			{
				count++;
				m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
				continue;
			}

			result = point.DotProduct( frustum.Right.Normal );
			if ( result > 0.0f )
			{
				count++;
				m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
				continue;
			}

			result = point.DotProduct( frustum.Top.Normal );
			if ( result > 0.0f )
			{
				count++;
				m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
				continue;
			}

			result = point.DotProduct( frustum.Bottom.Normal );
			if ( result > 0.0f )
			{
				count++;
				m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
				continue;
			}

			//result = point.DotProduct( frustum.Near.Normal );
			//if ( result > 0.0f )
			//{
			//	count++;
			//	m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
			//	continue;
			//}

			//result = point.DotProduct( frustum.Far.Normal );
			//if ( result > 0.0f )
			//{
			//	count++;
			//	m_transformed[ m_polys[i].Indices[vv] ].IsCulled = true;
			//	continue;
			//}
		}

		if ( count == 3 )
		{
			cullCount++;
			m_polys[i].IsCulled = true;
		}
	}

	return ( cullCount == m_numPolys );
}

} // end of namespace