#ifndef _DNA_OBJECT_H_
#define _DNA_OBJECT_H_
#include "renderobject.h"

namespace demoscene
{
	class DNAObject : public RenderObject
	{
		public:
			DNAObject(void) {};
			DNAObject(const renderer::Mesh& model, const Maths::Vector3& position, const Maths::Vector3& rotation, 
					  float scale, float angle, float yVelocity, float red, float green, float blue);
			DNAObject( const DNAObject& obj);
			~DNAObject(void);

			virtual void Update(float delta);

		protected:
			float m_yVelocity;
			float m_radius;
			float m_angle;
			float m_angleAddition;
	};
} // end of namespace
#endif // end of _DNA_OBJECT_H_