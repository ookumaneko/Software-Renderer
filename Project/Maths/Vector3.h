#ifndef _VECTOR_3_H_
#define _VECTOR_3_H_
#include <iostream> 
#include "MathsLibDef.h"

namespace Maths
{
	class DECLSPEC Vector3
	{
		// object management
		public:
			Vector3	(void);	
			Vector3	(float x, float y, float z);
			Vector3	(const Vector3& rhs);
			~Vector3(void);

			// operators
			Vector3& operator=	(const Vector3& rhs);
			Vector3	 operator+	(const Vector3& rhs) const;
			Vector3	 operator-	(const Vector3& rhs) const;
			Vector3  operator*	(const float scalar) const;
			Vector3  operator/	(const float scalar) const;
			Vector3& operator+=	(const Vector3& rhs);
			Vector3& operator-=	(const Vector3& rhs);
			Vector3& operator*=	(const float scalar);
			Vector3& operator/=	(const float scalar);
			bool	 operator==	(const Vector3& rhs);	
			bool	 operator!=	(const Vector3& rhs);

			Vector3  operator - (void) const;

			// arithmetic operations
			Vector3 Add		 (const Vector3& rhs) const;
			Vector3 Subtract (const Vector3& rhs) const;
			Vector3 Multiply (float scalar) const;
			Vector3 Divide	 (float scalar) const;

			// other operations
			void		Normalize		(void);
			bool		Equals			(const Vector3 &v) const;
			float		Length			(void) const;
			float		LengthSquared	(void) const;
			float		DotProduct		(const Vector3 &rhs) const;
			Vector3		CrossProduct	(const Vector3 &rhs) const;

			//static functions
			static Vector3	Lerp			(const Vector3 &start, const Vector3 &end, float amount);
			static float	Distance		(const Vector3 &lhs, const Vector3 &rhs);
			static float	DistanceSquared	(const Vector3 &lhs, const Vector3 &rhs);

			// output operator implemented for printing
			friend std::ostream& operator<<	(std::ostream&, const Vector3&);

			void SetValues(float x, float y, float z);

			// member variables
			const static Vector3 ZERO;
			const static Vector3 ONE;
			float X;
			float Y;
			float Z;
	};
}	// end of namespace Maths

#endif // enf of ifndef _VECTOR_3_H_


