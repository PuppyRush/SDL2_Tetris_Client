#include "TFigureI.h"

using namespace tetris;
using namespace game_interface;

TFigureI::TFigureI(const TFigureBuilder* bld)
        : TFigure(bld)
{
}

TFigureI::~TFigureI()
{
}

void TFigureI::initialize()
{
    _rotateLeft();
}

void TFigureI::_setFigureType(const TFigureType type)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (type) {
        case TFigureType::A:
            m_width = 4;
            m_height = 1;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y - 2});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            break;
        case TFigureType::B:
            m_width = 1;
            m_height = 4;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x - 2, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            break;
        default:
            assert(0);
    }
}

bool TFigureI::_validation()
{

}

TFigureType TFigureI::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureI::getTypeEnd() const noexcept
{
    return TFigureType::B;
}

const std::shared_ptr<TFigure> TFigureI::_copy() const
{
    return std::shared_ptr<TFigureI>(new TFigureI());
}