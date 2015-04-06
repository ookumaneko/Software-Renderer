#ifndef _Z_BUFFER_H_
#define _Z_BUFFER_H_
#include "RendererLibDef.h"

namespace renderer
{
	class RENDER_DECLSPEC ZBuffer
	{
		public:
			// constructors
			ZBuffer(void);
			~ZBuffer(void);

			// managements	
			void  Clear	(void);

			// Accessor
			inline void  Set	(int x, int y, float value) { m_buffer[y][x] = value; }
			inline const float& Get	(int x, int y) const	{ return m_buffer[y][x]; }

		protected:
			// member variables
			float m_buffer[600][800];
	};

} // enf of namepsace
#endif // end of _Z_BUFFER_H_