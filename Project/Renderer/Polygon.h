#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <windows.h>
#include <gdiplus.h>
#include "RendererLibDef.h"
#include "Vector4.h"

namespace renderer
{
	struct RENDER_DECLSPEC Polygon
	{
		Polygon(void);

		// member variables
		Maths::Vector4	Normal;
		Maths::Vector4	NormalN;	
		Gdiplus::Color	Colour;
		float			AverageDepth;
		int				Indices[3];
		int				UvIndices[3];
		bool			IsCulled;
	};

} // end of namespace

#endif // end of _POLYGON_H_