#include "TFigureI.h"

using namespace tetris;
using namespace game_interface;

TFigureI::TFigureI (const TFigureBuilder *bld)
    : TFigure (bld)
{
    _rotateLeft ();
}

TFigureI::~TFigureI ()
{
}

void TFigureI::initialize ()
{
    m_figureTypeCount = toUType (getTypeEnd ()) - toUType (getTypeBegin ());
}

void TFigureI::_rotateLeft ()
{
    m_relativeCoord[0].set ( {m_absoluteCoord.x, m_absoluteCoord.y});

    switch (m_figureType)
    {
        case TFigureType::A:
            m_width = 4;
            m_height = 1;
            m_relativeCoord[1].set ( {m_absoluteCoord.x, m_absoluteCoord.y-1});
            m_relativeCoord[2].set ( {m_absoluteCoord.x, m_absoluteCoord.y-2});
            m_relativeCoord[3].set ( {m_absoluteCoord.x, m_absoluteCoord.y+1});
            m_figureType = TFigureType::B;
            break;
        case TFigureType::B:
            m_width = 1;
            m_height = 4;
            m_relativeCoord[1].set ( {m_absoluteCoord.x-1, m_absoluteCoord.y});
            m_relativeCoord[2].set ( {m_absoluteCoord.x-2, m_absoluteCoord.y});
            m_relativeCoord[3].set ( {m_absoluteCoord.x+1, m_absoluteCoord.y});
            m_figureType = TFigureType::A;
            break;
        default:
            assert(0);
    }
}

void TFigureI::_rotateRight ()
{

}

bool TFigureI::_validation()
{

}

const TFigureType TFigureI::getTypeBegin () const
{
    return TFigureType::A;
}

const TFigureType TFigureI::getTypeEnd () const
{
    return TFigureType::B;
}

const std::shared_ptr<TFigure> TFigureI::_copy() const
{
    return std::shared_ptr<TFigureI>(new TFigureI());
}