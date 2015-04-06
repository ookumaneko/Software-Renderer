#ifndef _SIDE_SPIRAL_OBJECT_H_
#define _SIDE_SPIRAL_OBJECT_H_
#include "dnaobject.h"

namespace demoscene
{
	class SideSpiralObject : public DNAObject
	{
		public:
			SideSpiralObject(void){};
			SideSpiralObject(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, 
							 float scale, float angle, float yVelocity, float red, float green, float blue);
			SideSpiralObject(const SideSpiralObject& obj);
			~SideSpiralObject(void);

			void Update(float delta);
	};
} // end of namespace
#endif // end of _SIDE_SPIRAL_OBJECT_H_