#include "TFigureT.h"

using namespace tetris;
using namespace game_interface;

TFigureT::TFigureT(const TFigureBuilder *bld)
    : TFigure(bld)
{

}

TFigureT::~TFigureT() {
}

void TFigureT::initialize() {
    _rotateLeft ();
}

void TFigureT::_setFigureType(const TFigureType)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (m_figureType) {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x+1, m_absoluteCoord.y});
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y-1});
            break;
        case TFigureType::C:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x-1, m_absoluteCoord.y});
            break;
        case TFigureType::D:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y+1});
            break;
        default:
            assert(0);
    }
}

bool TFigureT::_validation() {

}

TFigureType TFigureT::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureT::getTypeEnd() const noexcept
{
    return TFigureType::D;
}

const std::shared_ptr<TFigure> TFigureT::_copy() const {
    return std::shared_ptr<TFigureT>(new TFigureT());
}

