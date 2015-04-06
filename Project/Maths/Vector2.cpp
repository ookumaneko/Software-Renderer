#include "Vector2.h"
#include <math.h>
#include "MathHelper.h"

namespace Maths
{

const Vector2 Vector2::ZERO = Vector2( 0.0f, 0.0f );
const Vector2 Vector2::ONE	= Vector2( 1.0f, 1.0f );

//-----------------------------------------------------------------------------//
//-----------------------Constructors and Destructor---------------------------//
//-----------------------------------------------------------------------------//

Vector2::Vector2(void)
{
	X = 0;
	Y = 0;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::Vector2(const Vector2& rhs)
{
	this->X = rhs.X;
	this->Y = rhs.Y;
}

Vector2::~Vector2(void)
{
	// do nothing
}

//----------------------------------------------------//
//-------------------- Operators ---------------------//
//----------------------------------------------------//

Vector2& Vector2::operator=(const Vector2& rhs)
{	
    if ( this == &rhs )
	{
		return *this;
	}

	this->X = rhs.X;
	this->Y = rhs.Y;
	return *this;
}

Vector2 Vector2::operator +(const Vector2& rhs) const
{
	return Vector2( X + rhs.X, Y + rhs.Y ); 
}

Vector2 Vector2::operator -(const Vector2& rhs) const
{
	return Vector2( X - rhs.X, Y - rhs.Y ); 
}

Vector2 Vector2::operator *(const float scalar) const
{
	return Vector2( X * scalar, Y * scalar ); 
}

Vector2 Vector2::operator /(const float scalar) const
{
	return Vector2( X / scalar, Y / scalar );
}

Vector2& Vector2::operator +=( const Vector2& rhs)
{
	X += rhs.X;
    Y += rhs.Y;

    return *this;
}

Vector2& Vector2::operator -=( const Vector2& rhs)
{
	X -= rhs.X;
    Y -= rhs.Y;

    return *this;
}

Vector2& Vector2::operator *=( const float scalar)
{
	X *= scalar;
    Y *= scalar;

    return *this;
}

Vector2& Vector2::operator /=( const float scalar)
{
	X /= scalar;
    Y /= scalar;

    return *this;
}

bool Vector2::operator ==(const Maths::Vector2 &rhs)
{
	return ( X == rhs.X && Y == rhs.Y );
}

bool Vector2::operator !=(const Vector2& rhs)
{
	return !( *this == rhs );
}

Vector2 Vector2::operator -() const
{
	return Vector2( -X, -Y );
}

//-----------------------------------------------------------------------------//
//----------------------------Member Functions---------------------------------//
//-----------------------------------------------------------------------------//


Vector2 Vector2::Add(const Vector2 &rhs)
{
	return Vector2( X + rhs.X, Y + rhs.Y );
}

Vector2 Vector2::Subtract(const Vector2 &rhs)
{
	return Vector2( X - rhs.X, Y - rhs.Y );
}

Vector2 Vector2::Multiply(float scalar)
{
	return Vector2( X * scalar, Y * scalar );
}

Vector2 Vector2::Divide(float scalar)
{
	return Vector2( X / scalar, Y / scalar );
}

float Vector2::Length() const
{
	return sqrtf( ( X * X ) + ( Y * Y ) );
}

float Vector2::LengthSquared() const
{
	return ( ( X * X ) + ( Y * Y ) );
}

void Vector2::Normalize()
{
	float length = sqrtf( ( X * X ) + ( Y * Y ) ); //temp.Length();
	X /= length;
	Y /= length;
}

inline bool Vector2::Equals(const Maths::Vector2 &v) const
{
	return ( X == v.X && Y == v.Y );
}

// print
std::ostream& operator<<(std::ostream& out, const Vector2& vec)
{
	return out << "<" << vec.X << ", " << vec.Y << ">" << std::endl;
}

//-----------------------------------------------------------------------------//
//----------------------------Static Functions---------------------------------//
//-----------------------------------------------------------------------------//

float Vector2::Distance(const Vector2 &lhs, const Vector2 &rhs)
{
	Vector2 temp = lhs - rhs;
	return temp.Length();
}

float Vector2::DistanceSquared(const Maths::Vector2 &lhs, const Maths::Vector2 &rhs)
{
	return ( lhs.X * rhs.X ) + ( lhs.Y * rhs.Y );
}

Vector2 Vector2::Lerp(const Maths::Vector2 &start, const Maths::Vector2 &end, float amount)
{
	float theta = ( start.X * end.X + start.Y * end.Y );
	Vector2 r = end * amount;

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

}	// end of namespace Math

