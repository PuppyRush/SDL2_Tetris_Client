#pragma once

using t_figureType = unsigned char;
using t_age = unsigned short;
using t_coord = unsigned char;
using t_width = unsigned char;
using t_height = unsigned char;
using t_figureInfo = std::tuple<t_figureType, t_width, t_height>;

typedef struct TPoint
{
	explicit TPoint(const t_coord x, const t_coord y)
		:x(x), y(y)
	{}

	t_coord x;
	t_coord y;
}TPoint;

enum class TColor : unsigned short
{
	red = 0,
	blue,
	orange,
	yellow,
	purple,
	green,
	none
};

