#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <windows.h>
#include "Vector4.h"
#include <gdiplus.h>
#include "RendererLibDef.h"

namespace renderer
{
	struct RENDER_DECLSPEC LightDirectional
	{
		public:
			LightDirectional(void);
			LightDirectional(const Maths::Vector4& position, const Maths::Vector4& intensity, const Gdiplus::Color& colour);
			LightDirectional(const LightDirectional &rhs);
			~LightDirectional(void);
		
			Maths::Vector4 Position;
			Maths::Vector4 Intensity;
			Gdiplus::Color Colour;
	};

	struct RENDER_DECLSPEC LightAmbient
	{
		public:
			LightAmbient(void);
			LightAmbient(const Gdiplus::Color& colour);
			LightAmbient(const LightAmbient &rhs);
			~LightAmbient(void);
		
			Gdiplus::Color Colour;
	};

	struct RENDER_DECLSPEC LightPoint
	{
		public:
			LightPoint(void);
			LightPoint(const Maths::Vector4& position, float ka_red, float kd_green, float ks_blue, const Gdiplus::Color& colour);
			LightPoint(const Maths::Vector4& position, const Maths::Vector4& coefficients, const Gdiplus::Color& colour);
			LightPoint(const LightPoint& light);
			~LightPoint(void);

			Maths::Vector4 Position;
			Maths::Vector4 Coefficients;
			Gdiplus::Color Colour;
	};

} // end of namespace renderer

#endif // end of _LIGHT_H_