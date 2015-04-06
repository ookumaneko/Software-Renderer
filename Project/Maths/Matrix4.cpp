#include <math.h>
#include "Matrix4.h"
#include "Vector4.h"
#include "MathHelper.h"

namespace Maths
{

// constant variables
const Matrix4 Matrix4::IDENTITY = Matrix4();
const Matrix4 Matrix4::ZERO = Matrix4( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  );

Matrix4::Matrix4(void)
{
	//create identity matrix as default
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			if ( x == y )
			{
				_m[y][x] = 1;
			}
			else
			{
				_m[y][x] = 0;
			}
		}
	}
}

Matrix4::Matrix4(float m00, float m10, float m20, float m30,
				 float m01, float m11, float m21, float m31,
				 float m02, float m12, float m22, float m32,
				 float m03, float m13, float m23, float m33)
{
	_m[0][0] = m00;
	_m[0][1] = m01;
	_m[0][2] = m02;
	_m[0][3] = m03;
	_m[1][0] = m10;
	_m[1][1] = m11;
	_m[1][2] = m12;
	_m[1][3] = m13;
	_m[2][0] = m20;
	_m[2][1] = m21;
	_m[2][2] = m22;
	_m[2][3] = m23;
	_m[3][0] = m30;
	_m[3][1] = m31;
	_m[3][2] = m32;
	_m[3][3] = m33;
}

Matrix4::Matrix4(const Matrix4 &src)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			_m[y][x] = src._m[y][x];
		}
	}
}

Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::operator =(const Matrix4& left)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			_m[y][x] = left._m[y][x];
		}
	}
	return *this;
}

bool Matrix4::operator ==(const Matrix4& left) const
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			if ( _m[y][x] != left._m[y][x] )
			{
				return false;
			}
		}
	}

	return true;
}

bool Matrix4::Equals(const Matrix4 &left) const
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			if ( _m[y][x] != left._m[y][x] )
			{
				return false;
			}
		}
	}

	return true;
}

void Matrix4::SetRows(const Vector4& r1, const Vector4& r2, const Vector4& r3, const Vector4& r4)
{
	_m[0][0] = r1.X;
	_m[0][1] = r1.Y;
	_m[0][2] = r1.Z;
	_m[0][3] = r1.W;

	_m[1][0] = r2.X;
	_m[1][1] = r2.Y;
	_m[1][2] = r2.Z;
	_m[1][3] = r2.W;

	_m[2][0] = r3.X;
	_m[2][1] = r3.Y;
	_m[2][2] = r3.Z;
	_m[2][3] = r3.W;

	_m[3][0] = r4.X;
	_m[3][1] = r4.Y;
	_m[3][2] = r4.Z;
	_m[3][3] = r4.W;
}

//Add the values in 2 matrcies sent from parameter 
//and output it to the last parameter
void Matrix4::Add(const Matrix4 &left, const Matrix4 &right, Matrix4 &out)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			out._m[y][x] = left._m[y][x] + right._m[y][x];
		}
	}
}

//Subtract the values in 2 matrcies sent from  
//parameter and output it to the last parameter
void Matrix4::Subtract(const Matrix4 &left, const Matrix4 &right, Matrix4 &out)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			out._m[y][x] = left._m[y][x] - right._m[y][x];
		}
	}
}

//Multiply the parameter function with the scalar and store it int out
void Matrix4::Multiply(const Matrix4 &left, float scalar, Matrix4 &out)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			out._m[y][x] = left._m[y][x] * scalar;
		}
	}
}

//Multiply two matrices (parameter 1 and 2) and 
//output the result to the last parameter (&out)
void Matrix4::Multiply(const Matrix4 &left, const Matrix4 &right, Matrix4 &out)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			out._m[y][x] = (left._m[0][x] * right._m[y][0]) + 
						   (left._m[1][x] * right._m[y][1]) + 
						   (left._m[2][x] * right._m[y][2]) + 
						   (left._m[3][x] * right._m[y][3]);
		}
	}
}


void Matrix4::Transform(const Matrix4 &left, const Maths::Vector4 &v, Maths::Vector4 &out)
{
	out.X = left._m[0][0] * v.X + left._m[0][1] * v.Y + left._m[0][2] * v.Z + left._m[0][3] * v.W;
	out.Y = left._m[1][0] * v.X + left._m[1][1] * v.Y + left._m[1][2] * v.Z + left._m[1][3] * v.W;
	out.Z = left._m[2][0] * v.X + left._m[2][1] * v.Y + left._m[2][2] * v.Z + left._m[2][3] * v.W;
	out.W = left._m[3][0] * v.X + left._m[3][1] * v.Y + left._m[3][2] * v.Z + left._m[3][3] * v.W;
}

void Matrix4::OutputToConsole() const
{
	std::cout << std::endl;
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			std::cout << _m[y][x] << "\t";
		}
		std::cout << std::endl;
	}
}


void Matrix4::Transpose(const Matrix4 &left, Matrix4 &out)
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 4; ++x )
		{
			out._m[y][x] = left._m[x][y];
		}
	}
}

//scale the Vector4 with matrix made out of parameter values
void Matrix4::Scale(const Matrix4 &pos, float sx, float sy, float sz, Matrix4 &out)
{
	Matrix4 scale;

	//make scaling matrix
	scale._m[0][0] = sx;
	scale._m[1][1] = sy;
	scale._m[2][2] = sz;
	scale._m[3][3] = 1;

	//multiply position with scale matrix
	Multiply( scale, pos, out );
}

//Rotate by Z-axis
void Matrix4::RotateZ(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot = GetZRotationMatrix( angle );
	Multiply( rot, pos, out ); 
}

//Rotate by X-axis
void Matrix4::RotateX(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot = GetXRotationMatrix( angle );
	Multiply( rot, pos, out );
}

//Rotate by Y-axis
void Matrix4::RotateY(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot = GetYRotationMatrix( angle );
	Multiply( rot, pos, out );
}

//Move 
void Matrix4::Translation(const Matrix4 &pos, float tx, float ty, float tz, Matrix4 &out)
{
	Matrix4 trans;

	//make scaling matrix
	trans._m[0][3] = tx;
	trans._m[1][3] = ty;
	trans._m[2][3] = tz;
	trans._m[3][3] = 1;

	//multiply position with scale matrix
	Multiply( trans, pos, out );
}

Matrix4 Matrix4::GetXRotationMatrix(float angle)
{
	Matrix4 rot;

	rot._m[1][1] = cos( MathHelper::ToRadian( angle ) );
	rot._m[1][2] = ( sin( MathHelper::ToRadian( angle ) ) ) * -1;
	rot._m[2][1] = sin( MathHelper::ToRadian( angle ) );
	rot._m[2][2] = cos( MathHelper::ToRadian( angle ) );

	return rot;
}

Matrix4 Matrix4::GetYRotationMatrix(float angle)
{
	Matrix4 rot;

	rot._m[0][0] = cos( MathHelper::ToRadian( angle ) );
	rot._m[0][2] = sin( MathHelper::ToRadian( angle ) );
	rot._m[2][0] = -1 * sin( MathHelper::ToRadian( angle ) );
	rot._m[2][2] = cos( MathHelper::ToRadian( angle ) );

	return rot;
}

Matrix4 Matrix4::GetZRotationMatrix(float angle)
{
	Matrix4 rot;

	rot._m[0][0] = cos( MathHelper::ToRadian( angle ) );
	rot._m[0][1] = ( sin( MathHelper::ToRadian( angle ) ) ) * -1;
	rot._m[1][0] = sin( MathHelper::ToRadian( angle ) );
	rot._m[1][1] = cos( MathHelper::ToRadian( angle ) );

	return rot;
}

void Matrix4::BuildXYZRotation(float theta_x, float theta_y, float theta_z, Maths::Matrix4 &out)
{
	Matrix4 a;
	Matrix4 b;
	out = IDENTITY;
	RotateX( a, theta_x, b );
	RotateY( b, theta_y, a );
	RotateZ( a, theta_z, b );
	out = b;
}

void Matrix4::BuildXYZTranslation(float tx, float ty, float tz, Maths::Matrix4 &out)
{
	Matrix4 trans;

	//make scaling matrix
	trans._m[0][3] = tx;
	trans._m[1][3] = ty;
	trans._m[2][3] = tz;
	trans._m[3][3] = 1;

	out = trans;
}

void Matrix4::BuildXYZScaling(float sx, float sy, float sz, Matrix4 &out)
{
	Matrix4 scale;

	scale._m[0][0] = sx;
	scale._m[1][1] = sy;
	scale._m[2][2] = sz;
	scale._m[3][3] = 1;

	out = scale;
}


/*-------Inverse Functions------*/
void Matrix4::InverseRotateZ(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot;
	Matrix4::Transpose( GetZRotationMatrix( angle ), rot );
	Multiply( rot, pos, out );
}

void Matrix4::InverseRotateX(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot;
	Transpose( GetXRotationMatrix( angle ), rot );
	Multiply( rot, pos, out );
}

void Matrix4::InverseRotateY(const Matrix4 &pos, float angle, Matrix4 &out)
{
	Matrix4 rot;
	Transpose( GetYRotationMatrix( angle ), rot );
	Multiply( rot, pos, out );
}

void Matrix4::InverseScale(const Matrix4 &pos, float sx, float sy, float sz, Matrix4 &out)
{
	Matrix4 scale;

	//make scaling matrix
	scale._m[0][0] = 1 / sx;
	scale._m[1][1] = 1 / sy;
	scale._m[2][2] = 1 / sz;
	scale._m[3][3] = 1;

	//multiply position with scale matrix
	Multiply( scale, pos, out );
}

void Matrix4::InverseTranslation(const Matrix4 &pos, float tx, float ty, float tz, Matrix4 &out)
{
	Matrix4 trans;

	//make scaling matrix
	trans._m[0][3] = -tx;
	trans._m[1][3] = -ty;
	trans._m[2][3] = -tz;
	trans._m[3][3] = 1;

	//multiply position with scale matrix
	Multiply( trans, pos, out );
}

} // end of namespace Maths