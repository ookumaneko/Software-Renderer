#include "ZBuffer.h"

namespace renderer
{

ZBuffer::ZBuffer(void)
{
	Clear();
}

ZBuffer::~ZBuffer(void)
{
}

void ZBuffer::Clear()
{
	for ( int y = 0; y < 600; ++y )
	{
		for ( int x = 0; x < 800; ++x )
		{
			m_buffer[y][x] = -50000.0f;	// clear zbuffer
		}
	}
}


}