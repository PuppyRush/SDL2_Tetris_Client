#include "TFigureO.h"

using namespace tetris;
using namespace game_interface;

TFigureO::TFigureO (const TFigureBuilder *bld)
    : TFigure (bld)
{
    _rotateLeft ();
    m_width = 2;
    m_height = 2;
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
    m_relativeCoord[0].set ( {m_absoluteCoord.x, m_absoluteCoord.y});

    switch (m_figureType)
    {
        case TFigureType::A:
            m_relativeCoord[1].set ( {m_absoluteCoord.x-1, m_absoluteCoord.y});
            m_relativeCoord[2].set ( {m_absoluteCoord.x -1, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set ( {m_absoluteCoord.x, m_absoluteCoord.y+1});
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