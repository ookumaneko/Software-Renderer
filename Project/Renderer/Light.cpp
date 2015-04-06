#include "Light.h"

namespace renderer
{

//------------------------------------------//
//-----------Directional Light--------------//
//------------------------------------------//

LightDirectional::LightDirectional(void)
{
	this->Colour	= Gdiplus::Color::Black;
	this->Position	= Maths::Vector4::ZERO;
	this->Intensity = Maths::Vector4( 1.0f, 1.0f, 1.0f, 0.0f );
}

LightDirectional::LightDirectional(const Maths::Vector4& position, const Maths::Vector4& intensity, const Gdiplus::Color& colour)
{
	this->Colour	= colour;
	this->Position	= position;
	this->Intensity = intensity;
}

LightDirectional::LightDirectional(const renderer::LightDirectional &rhs)
{
	this->Colour	= rhs.Colour;
	this->Position	= rhs.Position;
	this->Intensity = rhs.Intensity;
}

LightDirectional::~LightDirectional(void)
{
}


//------------------------------------------//
//----------------Ambient Light-------------//
//------------------------------------------//

LightAmbient::LightAmbient(void)
{
	this->Colour = Gdiplus::Color::Black;
}

LightAmbient::LightAmbient(const Gdiplus::Color& colour)
{
	this->Colour = colour;
}

LightAmbient::LightAmbient(const renderer::LightAmbient &rhs)
{
	this->Colour = rhs.Colour;
}

LightAmbient::~LightAmbient(void)
{
}


//-------------------------------------------//
//---------------Point Light-----------------//
//-------------------------------------------//


LightPoint::LightPoint(void)
{
	this->Position		= Maths::Vector4::ONE;
	this->Coefficients	= Maths::Vector4( 1.0f, 1.0f, 1.0f, 0.0f );
	this->Colour		= Gdiplus::Color::Pink;
} 

LightPoint::LightPoint(const Maths::Vector4& position, float ka_red, float kd_green, float ks_blue, const Gdiplus::Color& colour)
{
	this->Position		= position;
	this->Coefficients	= Maths::Vector4( ka_red, kd_green, ks_blue, 0.0f );
	this->Colour		= colour;
}

LightPoint::LightPoint(const Maths::Vector4& position, const Maths::Vector4& coefficients, const Gdiplus::Color& colour)
{
	this->Position		= position;
	this->Coefficients	= coefficients;
	this->Colour		= colour;
}

LightPoint::LightPoint(const LightPoint &light)
{
	this->Position		= light.Position;
	this->Coefficients	= light.Coefficients;
	this->Colour		= light.Colour;
}

LightPoint::~LightPoint(void)
{
}


} // end of namespace