#include "Polygon.h"

namespace renderer
{
	Polygon::Polygon()
	{
		for ( int i = 0; i < 3; ++i )
		{
			Indices[i]		= 0;
			UvIndices[i]	= 0;
		}

		AverageDepth	= 0.0f;
		IsCulled		= false;
		Colour			= Gdiplus::Color::Black;
	}

}