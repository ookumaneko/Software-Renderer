#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_
#include <iostream> 
#include "MathsLibDef.h"

namespace Maths
{
	class DECLSPEC Vector2
	{
		// object management
		public:
			Vector2	(void);									
			Vector2	(float x, float y);						
			Vector2	(const Vector2& rhs);					
			~Vector2(void);									

			// operators
			Vector2& operator=	(const Vector2& rhs);
			Vector2  operator+	(const Vector2& rhs) const;
			Vector2  operator-	(const Vector2& rhs) const;
			Vector2  operator*	(const float scalar) const;
			Vector2  operator/	(const float scalar) const;
			Vector2& operator+=	(const Vector2& rhs);
			Vector2& operator-=	(const Vector2& rhs);
			Vector2& operator*=	(const float scalar);
			Vector2& operator/=	(const float scalar);
			bool	 operator==	(const Vector2& rhs);	
			bool	 operator!=	(const Vector2& rhs);

			Vector2	 operator-	(void) const;

			// arithmetic operations
			Vector2 Add			(const Vector2 &rhs);
			Vector2 Subtract	(const Vector2 &rhs);
			Vector2 Multiply	(float scalar);
			Vector2 Divide		(float scalar);

			// other operations
			float		Length			(void) const;
			float		LengthSquared	(void) const;
			void		Normalize		(void);
			bool		Equals			(const Vector2 &v) const;

			//static methods
			static Vector2 Lerp				(const Vector2 &start, const Vector2 &end, float amount);
			static float   Distance			(const Vector2 &lhs, const Vector2 &rhs);
			static float   DistanceSquared	(const Vector2 &lhs, const Vector2 &rhs);

			// output operator implemented for printing
			friend std::ostream& operator<<(std::ostream&, const Vector2&);
			
			// constants
			const static Vector2 ZERO;
			const static Vector2 ONE;

			// member variables
			float X;
			float Y;

	};	// end of vector2 class

} // end of Math namespace

#endif // end of #ifndef _VECTOR2_H_
