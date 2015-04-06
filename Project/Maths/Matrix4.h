#ifndef _MATRIX_4_H_
#define _MATRIX_4_H_
#include "MathsLibDef.h"

namespace Maths
{
	// forward declaration
	class Vector4;	

	class DECLSPEC Matrix4
	{
		public:
			Matrix4(void);
			Matrix4(float m00, float m10, float m20, float m30,
					float m01, float m11, float m21, float m31,
					float m02, float m12, float m22, float m32,
					float m03, float m13, float m23, float m33);
			Matrix4(const Matrix4&);
			~Matrix4(void);

			// operators
			Matrix4& operator=	(const Matrix4& left);
			bool	 operator==	(const Matrix4& left) const;
			float&   operator()	(unsigned int row, unsigned int col);
			float    operator()	(unsigned int row, unsigned int col) const;

			// equality
			bool Equals(const Matrix4&) const;

			// setting
			void SetRows(const Vector4& r1, const Vector4& r2, const Vector4& r3, const Vector4& r4);

			// arithmetic
			static void Add		 (const Matrix4 &left, const Matrix4 &right, Matrix4 &out);
			static void Subtract (const Matrix4 &left, const Matrix4 &right, Matrix4 &out);
			static void Multiply (const Matrix4 &left, float scalar, Matrix4 &out);
			static void Multiply (const Matrix4 &left, const Matrix4 &right, Matrix4 &out);
			static void Transform(const Matrix4 &left, const Maths::Vector4 &v, Maths::Vector4 &out);
			static void Transpose(const Matrix4 &left, Matrix4 &out);

			// transformation
			static void Scale			(const Matrix4 &pos, float sx, float sy, float sz, Matrix4 &out);
			static void RotateZ			(const Matrix4 &pos, float angle, Matrix4 &out); 
			static void RotateX			(const Matrix4 &pos, float angle, Matrix4 &out);
			static void RotateY			(const Matrix4 &pos, float angle, Matrix4 &out);
			static void Translation		(const Matrix4 &pos, float tx, float ty, float tz, Matrix4 &out);
		
			// building rotation matrices
			static void BuildXYZRotation	( float theta_x, float theta_y, float theta_z, Matrix4 &out);
			static void BuildXYZTranslation	( float tx, float ty, float tz, Matrix4 &out);
			static void BuildXYZScaling		( float sx, float sy, float sz, Matrix4 &out);
		
			//Inverse Transformation
			static void InverseScale			(const Matrix4 &pos, float sx, float sy, float sz, Matrix4 &out);
			static void InverseRotateZ			(const Matrix4 &pos, float angle, Matrix4 &out); 
			static void InverseRotateX			(const Matrix4 &pos, float angle, Matrix4 &out);
			static void InverseRotateY			(const Matrix4 &pos, float angle, Matrix4 &out);
			static void InverseTranslation		(const Matrix4 &pos, float tx, float ty, float tz, Matrix4 &out);
			
			// console output for debugging
			void OutputToConsole() const;

			// constant variable
			const static Matrix4 IDENTITY;
			const static Matrix4 ZERO;

		private:
			static Matrix4 GetXRotationMatrix(float angle);
			static Matrix4 GetYRotationMatrix(float angle);
			static Matrix4 GetZRotationMatrix(float angle);

			// member variable
			float _m[4][4];

	};

	// inline accessor operators 
	inline float& Matrix4::operator()(unsigned int row, unsigned int col)
	{
		return _m[row][col];	
	}

	inline float Matrix4::operator ()(unsigned int row, unsigned int col) const
	{
		return _m[row][col];
	}

}// end of namespace Maths

	
#endif // end of ifndef _MATRIX_4_H_