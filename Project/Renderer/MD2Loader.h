#pragma once
#include <windows.h>
#include <gdiplus.h>
#include "RendererLibDef.h"

/*
This file was provided by Adam Thronette 
*/

// forward  declaration
namespace renderer 
{
class Mesh; 

class RENDER_DECLSPEC MD2Loader
{
public:
	MD2Loader(void);
public:
	~MD2Loader(void);
private:
	struct Md2Header_t
	{
      int indent;             // The magic number used to identify the file.
      int version;            // The file version number (must be 8).
      int skinWidth;          // The width in pixels of our image.
      int skinHeight;         // The height in pixels of our image.
      int frameSize;          // The size in bytes the frames are.
      int numSkins;           // The number of skins associated with the model.
      int numVertices;		  // The number of vertices.
      int numTexCoords;		  // The number of texture coordinates.
      int numTriangles;		  // The number of faces (polygons).
      int numGlCommands;      // The number of gl commands.
      int numFrames;          // The number of animated frames.
      int offsetSkins;		  // The offset in the file for the skin data.
      int offsetTexCoords;	  // The offset in the file for the texture data.
      int offsetTriangles;	  // The offset in the file for the face data.
      int offsetFrames;		  // The offset in the file for the frames data.
      int offsetGlCommands;	  // The offset in the file for the gl commands data.
      int offsetEnd;          // The end of the file offset.
	};
public:
	static bool LoadModel(const char* pFilename, renderer::Mesh& obj, const char* textureFilename = 0);
	static bool LoadPCX(const char* pFilename, BYTE* pTexture, Gdiplus::Color* pPalette, const Md2Header_t* pMd2Header);
};

}