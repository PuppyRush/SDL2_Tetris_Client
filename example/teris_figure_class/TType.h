#pragma once

#include <tuple>

namespace tetris {

	using t_type = unsigned char;
	using t_age = unsigned short;
	using t_coord = signed char;
	using t_size = unsigned char;

	typedef struct TPoint {
		TPoint()
				: x(0), y(0),z(0) {}

		TPoint(const t_coord x, const t_coord y, const t_coord z=0)
				: x(x), y(y),z(z)
			{}

		t_coord x;
		t_coord y;
		t_coord z;
	} TPoint;

	enum class TColor : t_type
	{
		red = 0,
		blue,
		orange,
		yellow,
		purple,
		green,
		none,
		Begin = red,
		End = green
	};
	
	enum class TFigureClass : t_type
	{
		L=0,
		Z,
		I,
		O,
		T,
		S,
		J,
		Begin = L,
		End = T
	};
	
	enum class TFigureType : t_type
	{
		A,
		B,
		C,
		D,
		None,
		Begin = A,
		End = D
	};
	
	enum class MapType : t_type
	{
	
	};
	
}