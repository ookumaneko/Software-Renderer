#include "Vector3.h"
#include <math.h>
#include "MathHelper.h"

namespace Maths
{

const Vector3 Vector3::ZERO = Vector3();
const Vector3 Vector3::ONE	= Vector3( 1.0f, 1.0f, 1.0f );

//-----------------------------------------------------------------------------//
//-----------------------Constructors and Destructor---------------------------//
//-----------------------------------------------------------------------------//


Vector3::Vector3(void)
{
	X = 0;
	Y = 0;
	Z = 0;
}

Vector3::Vector3(float x, float y , float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vector3::Vector3(const Vector3& rhs)
{
	this->X = rhs.X;
	this->Y = rhs.Y;
	this->Z = rhs.Z;
}

Vector3::~Vector3(void)
{
	// do nothing
}

//-----------------------------------------------------------------------------//
//-----------------------------------Operators---------------------------------//
//-----------------------------------------------------------------------------//

Vector3& Vector3::operator=(const Vector3& rhs)
{	
	if ( this == &rhs )
	{
		return *this;
	}

	this->X = rhs.X;
	this->Y = rhs.Y;
	this->Z = rhs.Z;
	return *this;
}

Vector3 Vector3::operator +(const Vector3& rhs) const
{
	return Vector3( X + rhs.X, Y + rhs.Y, Z + rhs.Z ); 
}

Vector3 Vector3::operator -(const Vector3& rhs) const
{
	return Vector3( X - rhs.X, Y - rhs.Y, Z - rhs.Z ); 
}

Vector3 Vector3::operator *(const float scalar) const
{
	return Vector3( X * scalar, Y * scalar, Z * scalar ); 
}

Vector3 Vector3::operator /(const float scalar) const
{
	return Vector3( X / scalar, Y / scalar, Z / scalar );
}

Vector3& Vector3::operator +=( const Vector3& rhs)
{
	X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;

    return *this;
}

Vector3& Vector3::operator -=( const Vector3& rhs)
{
	X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;

    return *this;
}

Vector3& Vector3::operator *=( const float scalar)
{
	X *= scalar;
    Y *= scalar;
    Z *= scalar;

    return *this;
}

Vector3& Vector3::operator /=( const float scalar)
{
	X /= scalar;
    Y /= scalar;
    Z /= scalar;

    return *this;
}

bool Vector3::operator ==(const Maths::Vector3 &rhs)
{
	return ( X == rhs.X && Y == rhs.Y && Z == rhs.Z );
}

bool Vector3::operator !=(const Vector3& rhs)
{
	return !( *this == rhs );
}

//-----------------------------------------------------------------------------//
//----------------------------Member Functions---------------------------------//
//-----------------------------------------------------------------------------//

void Vector3::SetValues(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

// ARITHMETIC OPERATIONS //------------------------------

Vector3 Vector3::Add(const Vector3& rhs) const
{
	return Vector3( X + rhs.X, Y + rhs.Y, Z + rhs.Z );
}

Vector3 Vector3::Subtract(const Vector3& rhs) const
{
	return Vector3( X - rhs.X, Y - rhs.Y, Z - rhs.Z );
}

Vector3 Vector3::Multiply(float scalar) const
{
	return Vector3( X * scalar, Y * scalar, Z * scalar );
}

Vector3 Vector3::Divide(float scalar) const
{
	return Vector3( X / scalar, Y / scalar, Z / scalar );
}

// END ARITHMETIC OPERATIONS //--------------------------

// OTHER OPERATIONSN //----------------------------------

float Vector3::Length() const
{
	return sqrt( (X * X) + ( Y * Y) + (Z * Z) );
}

float Vector3::LengthSquared() const
{
	return ( X * X ) + ( Y * Y ) + ( Z * Z );
}

void Vector3::Normalize()
{
	float length = Length();	
	X /= length;
	Y /= length;
	Z /= length;
}

bool Vector3::Equals(const Maths::Vector3 &v) const
{
	return ( X == v.X && Y == v.Y && Z == v.Z );
}

float Vector3::DotProduct(const Vector3 &v) const
{
	return ( X * v.X + Y * v.Y + Z * v.Z );
}

Vector3 Vector3::CrossProduct(const Vector3 &v) const
{
	return Vector3( Y * v.Z - Z * v.Y,
				    Z * v.X - X * v.Z,
				    X * v.Y - Y * v.X );
}

// END OTHER OPERATIONS //--------------------------------

// print
std::ostream& operator<<(std::ostream& out, const Vector3& vec)
{
	return out << "<" << vec.X << ", " << vec.Y << ", " << vec.Z  <<  ">" << std::endl;
}

//-----------------------------------------------------------------------------//
//----------------------------Static Functions---------------------------------//
//-----------------------------------------------------------------------------//


float Vector3::Distance(const Vector3 &lhs, const Vector3 &rhs)
{
	Vector3 temp = lhs - rhs;
	return temp.Length();
}

float Vector3::DistanceSquared(const Vector3 &lhs, const Vector3 &rhs)
{
	Vector3 temp = lhs - rhs;
	return temp.LengthSquared();
}

Vector3 Vector3::Lerp(const Maths::Vector3 &start, const Maths::Vector3 &end, float amount)
{
	float theta = start.DotProduct( end );
	Vector3 r = end * amount;

	if ( theta >= Maths::MathHelper::ToRadian( 90.0f ) )
	{
		r += ( start * ( 1 - amount ) );
	}
	else
	{
		r += ( start * ( amount - 1 ) );
	}

	return r;
}

}// end of namespace Math