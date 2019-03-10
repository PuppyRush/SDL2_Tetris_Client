#include "TFigureT.h"

using namespace tetris;
using namespace game_interface;

TFigureT::TFigureT(const TFigureBuilder *bld)
    : TFigure(bld)
{
    _rotateLeft();
}

TFigureT::~TFigureT() {
}

void TFigureT::initialize() {
    m_figureTypeCount = toUType(getTypeEnd()) - toUType(getTypeBegin());
}

void TFigureT::_rotateLeft() {

    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});

    switch (m_figureType) {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x+1, m_absoluteCoord.y});
            m_figureType = TFigureType::B;
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y-1});
            m_figureType = TFigureType::C;
            break;
        case TFigureType::C:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x-1, m_absoluteCoord.y});
            m_figureType = TFigureType::D;
            break;
        case TFigureType::D:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y+1});
            m_figureType = TFigureType::A;
            break;
        default:
            assert(0);
    }
}

void TFigureT::_rotateRight() {

}

bool TFigureT::_validation() {

}

const TFigureType TFigureT::getTypeBegin() const {
    return TFigureType::A;
}

const TFigureType TFigureT::getTypeEnd() const {
    return TFigureType::D;
}

const std::shared_ptr<TFigure> TFigureT::_copy() const {
    return std::shared_ptr<TFigureT>(new TFigureT());
}