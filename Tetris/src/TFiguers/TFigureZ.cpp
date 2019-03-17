#include "TFigureZ.h"

using namespace tetris;
using namespace game_interface;

TFigureZ::TFigureZ (const TFigureBuilder *bld)
    : TFigure (bld)
{
    _rotateLeft ();
}

TFigureZ::~TFigureZ ()
{
}

void TFigureZ::initialize ()
{
    m_figureTypeCount = toUType (getTypeEnd ()) - toUType (getTypeBegin ());
}

void TFigureZ::_rotateLeft ()
{
    m_relativeCoord[0].set ( {m_absoluteCoord.x, m_absoluteCoord.y});

    switch (m_figureType)
    {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set ( {m_absoluteCoord.x, m_absoluteCoord.y-1});
            m_relativeCoord[2].set ( {m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set ( {m_absoluteCoord.x + 1, m_absoluteCoord.y+1});
            m_figureType = TFigureType::B;
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set ( {m_absoluteCoord.x+1, m_absoluteCoord.y});
            m_relativeCoord[2].set ( {m_absoluteCoord.x-1, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set ( {m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_figureType = TFigureType::A;
            break;
        default:
            assert(0);
    }
}

void TFigureZ::_rotateRight ()
{

}

bool TFigureZ::_validation()
{

}

const TFigureType TFigureZ::getTypeBegin () const
{
    return TFigureType::A;
}

const TFigureType TFigureZ::getTypeEnd () const
{
    return TFigureType::B;
}

const std::shared_ptr<TFigure> TFigureZ::_copy() const
{
    return std::shared_ptr<TFigureZ>(new TFigureZ());
}