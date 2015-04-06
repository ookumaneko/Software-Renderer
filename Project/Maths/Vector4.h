#ifndef _VECTOR_4_H_
#define _VECTOR_4_H_
#include <iostream> 
#include "MathsLibDef.h"

namespace Maths
{
	class DECLSPEC Vector4
	{
		// object management
		public:
			Vector4	(void);										
			Vector4	(float x, float y, float z);
			Vector4	(float x, float y, float z, float w);		
			Vector4	(const Vector4& rhs);
			~Vector4(void);	

			// operators
			Vector4& operator=	(const Vector4& rhs);
			Vector4  operator+	(const Vector4& rhs) const;
			Vector4  operator-	(const Vector4& rhs) const;
			Vector4  operator*	(const float scalar) const;
			Vector4	 operator/	(const float scalar) const;
			Vector4& operator+=	(const Vector4& rhs);
			Vector4& operator-=	(const Vector4& rhs);
			Vector4& operator*=	(const float scalar);
			Vector4& operator/=	(const float scalar);
			bool	 operator==	(const Vector4& rhs);
			bool	 operator!=	(const Vector4& rhs);

			Vector4	 operator-	(void) const;

			// arithmetic operations
			Vector4 Add			(const Vector4& rhs) const;
			Vector4 Subtract	(const Vector4& rhs) const;
			Vector4 Multiply	(float scalar) const;
			Vector4 Divide		(float scalar) const;

			// other operations
			float		Length			(void) const;
			float		LengthSquared	(void) const;
			void		Normalize		(void);
			void		Dehomogenize	(void);
			void		DehomogenizeNonZ(void);
			bool		Equals			(const Vector4 &v)	 const;
			float		DotProduct		(const Vector4 &rhs) const;
			Vector4		CrossProduct	(const Vector4 &rhs) const;
			void		SetValues		(float x, float y, float z, float w);

			//static methods
			static Vector4	Lerp			(const Vector4 &start, const Vector4 &end, float amount);
			static float	Distance		(const Vector4 &lhs, const Vector4 &rhs);
			static float	DistanceSquared	(const Vector4 &lhs, const Vector4 &rhs);

			// output operator implemented for printing
			friend std::ostream& operator<<(std::ostream&, const Vector4&);

			// member variables
			const static Vector4 ZERO;
			const static Vector4 ZEROW;
			const static Vector4 ONE;
			float X;
			float Y;
			float Z;
			float W;
	};
} // end of namespace Maths


#endif //end of ifndef _VECTOR_4_H_