#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Vector4.h"
#include <windows.h>
#include <gdiplus.h>
#include "RendererLibDef.h"

namespace renderer
{
	struct RENDER_DECLSPEC Vertex
	{
		// constructors
		Vertex(void);
		Vertex(const Maths::Vector4 &position);
		Vertex(const Maths::Vector4 &position, const Gdiplus::Color &colour);
		Vertex(const Maths::Vector4 &position, const Maths::Vector4 &normal, const Gdiplus::Color &colour);
		Vertex(const Vertex &vert);
		~Vertex(void);

		// operator
		Vertex& operator=(const Vertex& vert);

		// member variables
		Maths::Vector4	Position;
		Maths::Vector4	Normal;
		Gdiplus::Color	Colour;
		float			U;
		float			V;
		float			SavedZ;
		int				Tally;
		bool			IsCulled;
	};

}// end of namespace

#endif // end of _VERTEX_H_