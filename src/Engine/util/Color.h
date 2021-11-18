#pragma once

// Size : 16
/*class Color
{
public:
	static const Color BLACK;
	static const Color BLUE;
	static const Color CYAN;
	static const Color GREEN;
	static const Color GREY;
	static const Color NIL;
	static const Color PURPLE;
	static const Color RED;
	static const Color WHITE;
	static const Color YELLOW;
	static const Color SHADE_DOWN;
	static const Color SHADE_NORTH_SOUTH;
	static const Color SHADE_UP;
	static const Color SHADE_WEST_EAST;

public:
	float red;		// 0
	float green;	// 4
	float blue;		// 8
	float alpha;	// 12

public:
	Color(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {};
	static Color *fromHSB(float, float, float);
};*/

struct Color
{
   Color(std::uint8_t r = 255, std::uint8_t g = 255, std::uint8_t b = 255, std::uint8_t a = 255) 
		: r(r), g(g), b(b), a(a)
   {

	}

   Color(std::uint32_t hexValue)
   {
      a = (hexValue & 0xFF000000) >> 24;
      r = (hexValue & 0xFF0000) >> 16;
      g = (hexValue & 0xFF00) >> 8;
      b = hexValue & 0xFF;
   }

   std::uint32_t ToHex()
   {
      return (a << 24) | (r << 16) | (g << 8) | b;
   }


   std::uint8_t a;
   std::uint8_t r;
   std::uint8_t g;
   std::uint8_t b;
};
