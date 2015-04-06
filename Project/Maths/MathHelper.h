#ifndef _MATH_HELPER_H_
#define _MATH_HELPER_H_
#include "MathsLibDef.h"

namespace Maths
{
	class DECLSPEC MathHelper
	{
		private:
			MathHelper(void) {};

		public:
			~MathHelper(void) {};

		public:

			// constatnt variables
			const static float Pi;
			const static float PiOver2;
			const static float PiOver4;
			const static float TwoPi;

			// inline methods
			static inline float ToRadian(float degree)
			{
				return (float)( degree * ( Pi / 180.0f ) );
			}
	};
}

#endif