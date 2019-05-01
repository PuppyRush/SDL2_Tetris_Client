#include "TFigureL.h"

using namespace tetris;
using namespace game_interface;

TFigureL::TFigureL(const TFigureBuilder* bld)
        : TFigure(bld)
{

}

TFigureL::~TFigureL()
{
}

void TFigureL::initialize()
{
    _rotateLeft();
}

void TFigureL::_setFigureType(const TFigureType type)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (type) {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[3].set({m_absoluteCoord.x + 1, m_absoluteCoord.y + 1});
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y - 1});
            m_relativeCoord[3].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            break;
        case TFigureType::C:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            break;
        case TFigureType::D:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y + 1});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            break;
        default:
            assert(0);
    }
}

bool TFigureL::_validation()
{

}

TFigureType TFigureL::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureL::getTypeEnd() const noexcept
{
    return TFigureType::D;
}

const std::shared_ptr<TFigure> TFigureL::_copy() const
{
    return std::shared_ptr<TFigureL>(new TFigureL());
}