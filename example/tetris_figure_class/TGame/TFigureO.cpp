#include "TFigureO.h"
#include "../Common/TypeTraits.h"

using namespace tetris;

TFigureO::TFigureO (const TFigureBuilder *bld)
    : TFigure (bld)
{
    m_color = {TColorCode::blue};
    _rotateLeft ();
}

TFigureO::~TFigureO ()
{
}

void TFigureO::initialize ()
{
    m_figureTypeCount = toUType (getTypeEnd ()) - toUType (getTypeBegin ());
}

void TFigureO::_rotateLeft ()
{
    m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y));

    switch (m_figureType)
    {
        case TFigureType::A:
            m_relativeCoord[1].setPoint (TPoint (m_point.x-1, m_point.y));
            m_relativeCoord[2].setPoint (TPoint (m_point.x -1, m_point.y + 1));
            m_relativeCoord[3].setPoint (TPoint (m_point.x, m_point.y+1));
            m_figureType = TFigureType::B;
            break;
        default:
            assert(0);
    }
}

void TFigureO::_rotateRight ()
{

}

bool TFigureO::_validation()
{
	return false;
}

const TFigureType TFigureO::getTypeBegin () const
{
    return TFigureType::A;
}

const TFigureType TFigureO::getTypeEnd () const
{
    return TFigureType::A;
}

const std::shared_ptr<TFigure> TFigureO::_copy() const
{
    return std::shared_ptr<TFigureO>(new TFigureO());
}