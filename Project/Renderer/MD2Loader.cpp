/*
This file was provided by Adam Thronette 
and modified by me
*/


#include "MD2Loader.h"

// file reading
#include <iostream>
#include <fstream>

#include "Mesh.h"
//#include "Vector4.h"

typedef unsigned char BYTE; // added in case not doing in a win32 app

// magic number "IDP2" or 844121161
const int MD2_IDENT = (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I');

// model version
const int MD2_VERSION = 8;

// triangle
struct Md2Triangle_t
{
	short vertexIndex[3];   // vertex indices of the triangle
	short uvIndex[3];       // tex. coord. indices 
};

// vertex
struct Md2Vertex_t
{
    BYTE v[3];                // compressed vertex (x, y, z) coordinates
    BYTE lightnormalindex;    // index to a normal vector for the lighting

};

// frame
struct Md2Frame_t
{
    float       scale[3];       // scale values
    float       translate[3];   // translation vector
    char        name[16];       // frame name
    Md2Vertex_t verts[1];       // first vertex of this frame
};

//texture coordinate
struct Md2TexCoord_t
{
	short		texCoord[2];	//texture coords
};

struct PcxHeader_t
{
	BYTE  ID;
	BYTE  Version;
	BYTE  Encoding;
	BYTE  BitsPerPixel;
	short XMin;
	short YMin;
	short XMax;
	short YMax;
	short HRes;
	short VRes;
	BYTE  ClrMap[16*3];
	BYTE  Reserved;
	BYTE  NumPlanes;
	short BytesPerLine;
	short Pal;
	BYTE  Filler[58];
};

namespace renderer
{

MD2Loader::MD2Loader(void)
{
}

MD2Loader::~MD2Loader(void)
{
}

// ----------------------------------------------
// LoadModel() - load model from file.
// ----------------------------------------------
bool MD2Loader::LoadModel( const char* filename, renderer::Mesh& obj, const char* textureFilename)
{
    std::ifstream   file;           // file stream

	// try to open filename
    file.open( filename, std::ios::in | std::ios::binary );

    if( file.fail() )
        return false;

    // read md2 header file
    Md2Header_t header;         
	file.read( reinterpret_cast<char*>(&header), sizeof( Md2Header_t ) );

    /////////////////////////////////////////////
    //      verify that this is a MD2 file

    // check for the ident and the version number
    if( (header.indent != MD2_IDENT) && (header.version != MD2_VERSION) )
    {
        // this is not a MD2 model
        file.close();
        return false;
    }

    /////////////////////////////////////////////

    // allocate memory dynamically (on heap)
	Md2Triangle_t*	pTriangles		= new Md2Triangle_t[ header.numTriangles ];
	BYTE*			pFrameBuffer	= new BYTE[ header.frameSize ];// only interested in one frame (first)
	Md2Frame_t*		pFrame			= reinterpret_cast<Md2Frame_t*>(pFrameBuffer);
	Md2TexCoord_t*	pTexCoords		= new Md2TexCoord_t[ header.numTexCoords ];

    /////////////////////////////////////////////
    //          reading file data

	// read polygon data...
	file.seekg( header.offsetTriangles, std::ios::beg );
	file.read( reinterpret_cast<char*>(pTriangles), sizeof(Md2Triangle_t) * header.numTriangles );	// read just first frame

    // read frame data...
    file.seekg( header.offsetFrames, std::ios::beg );
    file.read( reinterpret_cast<char*>(pFrame), header.frameSize );	// read just first frame

	// read texture coord data
	file.seekg( header.offsetTexCoords, std::ios::beg );
	file.read( reinterpret_cast<char*>(pTexCoords), sizeof(Md2TexCoord_t) * header.numTexCoords );

	// close the file 
    file.close();
    /////////////////////////////////////////////

	bool bHasTexture = false;

	//attempt to load texture
	if ( textureFilename != 0 ) 
	{   
		BYTE*   pTexture = new BYTE[header.skinWidth * header.skinHeight]; 
		Gdiplus::Color* pPalette = new Gdiplus::Color[256]; // rgb 256 palette 
		
		/*Note.  The texture co-ordinates that we load from the MD2 file are not normalised, but actually 
		in texture space already (scaled in range 0-255) since the texture size is fixed for MD2s at 
		256x256 textures. */

		bHasTexture = LoadPCX( textureFilename, pTexture, pPalette, &header ); 
		if ( !bHasTexture ) 
		{ 
			delete(pTexture); 
			delete(pPalette); 
			obj.m_hasTexture = false;
		} 
		else 
		{ 
			obj.m_hasTexture = true;
			obj.m_texture = pTexture; 
			obj.m_palette = pPalette; 
			obj.m_textureWidth = header.skinWidth; 
		} 
	} 

	// polygon array initialization
	obj.m_polys = new renderer::Polygon[header.numTriangles];
	for ( int i = 0; i < header.numTriangles; ++i )
	{
		renderer::Polygon p;
		
		p.Indices[0] = pTriangles[i].vertexIndex[0];
		p.Indices[1] = pTriangles[i].vertexIndex[1];
		p.Indices[2] = pTriangles[i].vertexIndex[2];

		p.UvIndices[0] = pTriangles[i].uvIndex[0];
		p.UvIndices[1] = pTriangles[i].uvIndex[1];
		p.UvIndices[2] = pTriangles[i].uvIndex[2];

		p.IsCulled = false;
		p.AverageDepth = 0.0f;
		p.Normal = Maths::Vector4();
		p.Colour = Gdiplus::Color::Black;
		obj.m_polys[i] = p;
	}
	obj.m_numPolys = header.numTriangles;

	// vertex array initialization
	obj.m_verts = boost::shared_array<Maths::Vector4>( new Maths::Vector4[ header.numVertices ] ); //new Maths::Vector4[ header.numVertices ];
	obj.m_transformed = new renderer::Vertex[ header.numVertices ];
    for( int i = 0; i < header.numVertices; ++i )
	{
		// NOTE: we have to swap Y and Z over because Z is up in Quake2 and we have Y as up-axis
		Maths::Vector4 v;
		v.X = (pFrame->verts[i].v[0] * pFrame->scale[0]) + pFrame->translate[0];
		v.Z = (pFrame->verts[i].v[1] * pFrame->scale[1]) + pFrame->translate[1];
		v.Y = (pFrame->verts[i].v[2] * pFrame->scale[2]) + pFrame->translate[2];
		v.W = 1.0f; // DON'T FORGET THIS otherwise looks 'exploded'
		obj.m_verts[i] = v;
	}
	obj.m_numVerts = header.numVertices;

	// Texture coordinates initialization
	if ( bHasTexture )
	{
		obj.m_TexUVs = new renderer::UVCoords[ header.numTexCoords ];
		for (int i = 0; i < header.numTexCoords; i++)
		{
			obj.m_TexUVs[i].U = pTexCoords[i].texCoord[0];
			obj.m_TexUVs[i].V = pTexCoords[i].texCoord[1];
		}
		obj.m_numTexUVs = header.numTexCoords;
	}
	else
	{
		obj.m_numTexUVs = 0;
	}

	// free buffer's heap memory
    delete [] pTriangles; // NOTE: this is 'array' delete must be sure to use this
	pTriangles = 0;

	delete [] pFrameBuffer;
	pFrameBuffer = 0;
	pFrame = 0;

	delete [] pTexCoords;
	pTexCoords = 0;
	return true;
}

// ----------------------------------------------
// LoadPCX() - load pcx texture from file.
//
// assume the caller has allocated enough memory for texture - pMd2Header->skinWidth * pMd2Header->skinHeight
// ----------------------------------------------
bool MD2Loader::LoadPCX(const char* pFilename, BYTE* pTexture, Gdiplus::Color* pPalette, const Md2Header_t* pMd2Header)
{
	std::ifstream   file;   // file stream

	// try to open filename
    file.open( pFilename, std::ios::in | std::ios::binary );

    if( file.fail() )
        return false;

    // read md2 header file
    PcxHeader_t header;         
	file.read( reinterpret_cast<char*>(&header), sizeof( PcxHeader_t ) );

    /////////////////////////////////////////////
    //      verify that this is a valid PCX file

	// only handle those with 256 colour palette
	if( (header.Version != 5) || (header.BitsPerPixel != 8) || 
		(header.Encoding != 1) || (header.NumPlanes != 1) ||
		(pMd2Header && (header.BytesPerLine != pMd2Header->skinWidth) ) )
    {
        // this is not valid supported PCX
        file.close();
        return false;
    }

    /////////////////////////////////////////////
	//		check dimensions

	int XSize = header.XMax - header.XMin + 1;
	int YSize = header.YMax - header.YMin + 1;
	int Size = XSize * YSize;

	// check matches our MD2 expected texture
	// note. valid size is <= because uses RLE (so potentially smaller)
	if ( pMd2Header && ( Size > (pMd2Header->skinHeight * pMd2Header->skinWidth) ) )
	{
		// doesn't match expected MD2 skin size
		file.close();
		return false;
	}
	
	/////////////////////////////////////////////
    //          reading file data

	BYTE processByte, colourByte;
	int count = 0;
	while(count < Size)
	{
		file.read( reinterpret_cast<char*>(&processByte), 1 );

		// Run length encoding - test if byte is an RLE byte
		if ((processByte & 192) == 192)
		{
			// extract number of times repeated byte
			processByte &= 63;
			file.read( reinterpret_cast<char*>(&colourByte), 1 );
			for (int index = 0; index < processByte; ++index)
			{
				// repeatedly write colour 
				pTexture[count] = colourByte;
				++count;
			}
		}
		else
		{
			// process byte is the colour
			pTexture[count] = processByte;
			++count;
		}
	}

	bool returnValue = false;

	// read palette data...
	file.seekg( -769, std::ios::end);	// from this offset from end of file
	file.read( reinterpret_cast<char*>(&processByte), 1 );
	if (processByte == 12)
	{
		BYTE rawPalette[768];
		file.read( reinterpret_cast<char*>(&rawPalette), 768 );

		// build palette
		for (int palIndex = 0; palIndex < 256; ++palIndex)
		{			
			pPalette[palIndex].SetFromCOLORREF( RGB(rawPalette[ palIndex * 3],
													rawPalette[(palIndex * 3) + 1],
													rawPalette[(palIndex * 3) + 2] ));
		}

		returnValue = true;
	}

	// all done
	file.close();
	return returnValue;
}

}