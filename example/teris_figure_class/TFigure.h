#pragma once


#include <cassert>
#include <memory>
#include <deque>
#include <numeric>

#include "TType.h"
#include "TFigureUnit.h"


/************************************************
*	бщ(x,y)  	Relatevie Coordnation		    *
*	бр бр	бр	(x  ,y) (x  ,y+1) (x  ,y+2)			*
*	бр бр	бр	(x+1,y) (x+1,y+1) (x+1,y+2)			*
*	бр бр	бр	(x+2,y) (x+2,y+1) (x+2,y+2)			*
*												*
************************************************/

typedef struct TFigureInfo
{
	TPoint coord;
	t_width width;
	t_height height;
	TColor color;
};


class FigureBuilder
{
public:

	FigureBuilder(const TPoint& coord)
		:m_coord(coord),
		m_width(std::numeric_limits<t_width>::max()),
		m_height(std::numeric_limits<t_height>::max()),
		m_color(TColor::none)
	{
		
	}

	FigureBuilder* width(const t_width _width)
	{
		this->width = _width;
		return this;
	}

	FigureBuilder* height(const t_width _height)
	{
		this->m_height = _height;
		return this;
	}

	FigureBuilder* color(const TColor _color)
	{
		this->m_color = _color;
		return this;
	}

	const TFigureInfo build()
	{
		//runtime check of necessary value
		assert(m_width != std::numeric_limits<t_width>::max());
		assert(m_height != std::numeric_limits<t_height>::max());
		assert(m_color != TColor::none);

		TFigureInfo fi;
		fi.height = m_height;
		fi.width = m_width;
		fi.coord = m_coord;
		fi.color = m_color;
		return fi;
	}

private:
	t_width m_width;
	t_height m_height;
	TPoint m_coord;
	TColor m_color;
};


class TFigure
{
public:
	virtual ~TFigure();

	virtual void goRight() = 0;
	virtual void goLeft() = 0;
	virtual void goDown() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
	
	const t_figureType getType();
	const size_t getWidth();
	const size_t getHeight();
	
	const TFigureUnit** getCoord() const noexcept
	{	return m_relativeCoord;	}


private:
	TFigure(const FigureBuilder&);
	virtual bool Validation() = 0;

	TFigureInfo m_figureInfo;
	TFigureUnit** m_relativeCoord; //coord is coordinations.
};

