#pragma once
#include <gdiplus.h>

namespace GameDef
{
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
	static bool DEBUG_MODE = true;
	static bool BACKFACE_CULLLING = true;
	static Gdiplus::Color BACKGROUND_COLOUR = Gdiplus::Color::Black;
}