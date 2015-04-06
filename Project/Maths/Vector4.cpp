#include "Vector4.h"
#include <math.h>
#include "MathHelper.h"

namespace Maths
{

const Vector4 Vector4::ZERO		= Vector4( 0.0f, 0.0f, 0.0f, 0.0f ); 
const Vector4 Vector4::ONE		= Vector4( 1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::ZEROW	= Vector4( 0.0f, 0.0f, 0.0f, 1.0f ); 

//-----------------------------------------------------------------------------//
//-----------------------Constructors and Destructor---------------------------//
//-----------------------------------------------------------------------------//

Vector4::Vector4(void)
{
	X = 0;
	Y = 0;
	Z = 0;
	W = 1;
}

Vector4::Vector4(float x, float y , float z)
{
	X = x;
	Y = y;
	Z = z;
	W = 1;
}

Vector4::Vector4(float x, float y , float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

Vector4::Vector4(const Vector4& rhs)
{
	this->X = rhs.X;
	this->Y = rhs.Y;
	this->Z = rhs.Z;
	this->W = rhs.W;
}

Vector4::~Vector4(void)
{
	// do nothing
}


//-------------------------------//
//-----------Operators-----------//
//-------------------------------//

Vector4& Vector4::operator=(const Vector4& rhs)
{	
    if ( this == &rhs )
	{
		return *this;
	}

	this->X = rhs.X;
	this->Y = rhs.Y;
	this->Z = rhs.Z;
	this->W = rhs.W;
	return *this;
}

Vector4 Vector4::operator +(const Vector4& rhs) const
{
	return Vector4( X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W ); 
}

Vector4 Vector4::operator -(const Vector4& rhs) const
{
	return Vector4( X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W ); 
}

Vector4 Vector4::operator *(const float scalar) const
{
	return Vector4( X * scalar, Y * scalar, Z * scalar, W * scalar ); 
}

Vector4 Vector4::operator /(const float scalar) const
{
	return Vector4( X / scalar, Y / scalar, Z / scalar, W / scalar );
}

Vector4& Vector4::operator +=( const Vector4& rhs)
{
	X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    W += rhs.W;

    return *this;
}

Vector4& Vector4::operator -=( const Vector4& rhs)
{
	X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    W -= rhs.W;

    return *this;
}

Vector4& Vector4::operator *=( const float scalar)
{
	X *= scalar;
    Y *= scalar;
    Z *= scalar;
    W *= scalar;

    return *this;
}

Vector4& Vector4::operator /=( const float scalar)
{
	X /= scalar;
    Y /= scalar;
    Z /= scalar;
    W /= scalar;

    return *this;
}

bool Vector4::operator ==(const Maths::Vector4 &rhs)
{
	return ( X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W );
}

bool Vector4::operator !=(const Vector4& rhs)
{
	return !( *this == rhs );
}

Vector4 Vector4::operator -() const
{
	return Vector4( -X, -Y, -Z, W );
}

//-----------------------------------------------------------------------------//
//----------------------------Member Functions---------------------------------//
//-----------------------------------------------------------------------------//


void Vector4::SetValues(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

// ARITHMETIC OPERATIONS //------------------------------

Vector4 Vector4::Add(const Vector4 &rhs) const
{
	return Vector4( X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W );
}

Vector4 Vector4::Subtract(const Vector4 &rhs) const
{
	return Vector4( X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W );
}

Vector4 Vector4::Multiply(float scalar) const
{
	return Vector4( X * scalar, Y * scalar, Z * scalar, W * scalar );
}

Vector4 Vector4::Divide(float scalar) const
{
	return Vector4( X / scalar, Y / scalar, Z / scalar, W / scalar );
}

// END ARITHMETIC OPERATIONS //--------------------------


// OTHER OPERATIONSN //----------------------------------

float Vector4::Length() const
{
	return sqrtf(  X * X + Y * Y + Z * Z + W * W  );
}

float Vector4::LengthSquared() const
{
	return ( X * X + Y * Y + Z * Z + W * W );
}

void Vector4::Normalize()
{
	Vector4 temp(X, Y, Z, W);
	float length = temp.Length();
	
	X /= length;
	Y /= length;
	Z /= length;
	W /= length;
}

void Vector4::Dehomogenize()
{
	X /= W;
	Y /= W;
	Z /= W;
	W = 1;
}

void Vector4::DehomogenizeNonZ()
{
	X /= W;
	Y /= W;
	W = 1;
}

bool Vector4::Equals(const Maths::Vector4 &v) const
{
	return ( X == v.X && Y == v.Y && Z == v.Z && W == v.W );
}

float Vector4::DotProduct(const Vector4 &v) const
{
	return ( X * v.X + Y * v.Y + Z * v.Z );
}

Vector4 Vector4::CrossProduct(const Vector4 &v) const
{
	return Vector4( Y * v.Z - Z * v.Y,
					Z * v.X - X * v.Z,
					X * v.Y - Y * v.X,
					1.0f );
}

// END OTHER OPERATIONS //--------------------------------

// print
std::ostream& operator<<(std::ostream& out, const Vector4& vec)
{
	return out << "<" << vec.X << ", " << vec.Y << ", " << vec.Z  << ", " << vec.W <<  ">" << std::endl;
}

//-----------------------------------------------------------------------------//
//----------------------------Static Functions---------------------------------//
//-----------------------------------------------------------------------------//

float Vector4::Distance(const Vector4 &lhs, const Vector4 &rhs)
{
	Vector4 temp = lhs - rhs;
	return temp.Length();
}

float Vector4::DistanceSquared(const Vector4 &lhs, const Vector4 &rhs)
{
	Vector4 temp = lhs - rhs;
	return temp.LengthSquared();
}

//Liner Interpolation Method
Vector4 Vector4::Lerp(const Maths::Vector4 &start, const Maths::Vector4 &end, float amount)
{
	float theta = start.DotProduct( end );
	Vector4 r = end * amount;

	if ( theta >= Maths::MathHelper::ToRadian( 90 ) )
	{
		r += ( start * ( 1 - amount ) );
	}
	else
	{
		r += ( start * ( amount - 1 ) );
	}

	return r;
}

}