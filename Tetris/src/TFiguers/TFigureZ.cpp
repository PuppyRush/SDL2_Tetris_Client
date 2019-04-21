#include "TFigureZ.h"

using namespace tetris;
using namespace game_interface;

TFigureZ::TFigureZ (const TFigureBuilder *bld)
    : TFigure (bld)
{

}

TFigureZ::~TFigureZ ()
{
}

void TFigureZ::initialize ()
{
    _rotateLeft ();
}

void TFigureZ::_setFigureType(const TFigureType)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (m_figureType)
    {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set ( {m_absoluteCoord.x, m_absoluteCoord.y-1});
            m_relativeCoord[2].set ( {m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set ( {m_absoluteCoord.x + 1, m_absoluteCoord.y+1});
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set ( {m_absoluteCoord.x+1, m_absoluteCoord.y});
            m_relativeCoord[2].set ( {m_absoluteCoord.x-1, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set ( {m_absoluteCoord.x, m_absoluteCoord.y + 1});
            break;
        default:
            assert(0);
    }
}

bool TFigureZ::_validation()
{

}

TFigureType TFigureZ::getTypeBegin () const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureZ::getTypeEnd () const noexcept
{
    return TFigureType::B;
}

const std::shared_ptr<TFigure> TFigureZ::_copy() const
{
    return std::shared_ptr<TFigureZ>(new TFigureZ());
}

