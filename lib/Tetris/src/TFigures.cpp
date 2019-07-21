//
// Created by chaed on 19. 5. 1.
//

#include "../include/TFigures.h"

using namespace tetris_module;
using namespace game_interface;

TFigureI::TFigureI(const TFigureBuilder* bld)
        : TFigureInterface(bld)
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
    return true;
}

TFigureType TFigureI::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureI::getTypeEnd() const noexcept
{
    return TFigureType::B;
}

const std::shared_ptr<TFigureInterface> TFigureI::_copy() const
{
    return std::shared_ptr<TFigureI>(new TFigureI());
}

//***************************************************************************//

TFigureL::TFigureL(const TFigureBuilder* bld)
        : TFigureInterface(bld)
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
    return true;
}

TFigureType TFigureL::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureL::getTypeEnd() const noexcept
{
    return TFigureType::D;
}

const std::shared_ptr<TFigureInterface> TFigureL::_copy() const
{
    return std::shared_ptr<TFigureL>(new TFigureL());
}

//***************************************************************************//

TFigureO::TFigureO(const TFigureBuilder* bld)
        : TFigureInterface(bld)
{
    m_width = 2;
    m_height = 2;
}

TFigureO::~TFigureO()
{
}

void TFigureO::initialize()
{
    _rotateLeft();
}

void TFigureO::_setFigureType(const TFigureType)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (m_figureType) {
        case TFigureType::A:
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x - 1, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_figureType = TFigureType::B;
            break;
        default:
            assert(0);
    }
}

bool TFigureO::_validation()
{
    return true;
}

TFigureType TFigureO::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureO::getTypeEnd() const noexcept
{
    return TFigureType::A;
}

const std::shared_ptr<TFigureInterface> TFigureO::_copy() const
{
    return std::shared_ptr<TFigureO>(new TFigureO());
}


//***************************************************************************//

TFigureT::TFigureT(const TFigureBuilder* bld)
        : TFigureInterface(bld)
{

}

TFigureT::~TFigureT()
{
}

void TFigureT::initialize()
{
    _rotateLeft();
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
            m_relativeCoord[3].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            break;
        case TFigureType::C:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            break;
        case TFigureType::D:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x - 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            break;
        default:
            assert(0);
    }
}

bool TFigureT::_validation()
{
    return true;
}

TFigureType TFigureT::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureT::getTypeEnd() const noexcept
{
    return TFigureType::D;
}

const std::shared_ptr<TFigureInterface> TFigureT::_copy() const
{
    return std::shared_ptr<TFigureT>(new TFigureT());
}


//***************************************************************************//

TFigureZ::TFigureZ(const TFigureBuilder* bld)
        : TFigureInterface(bld)
{

}

TFigureZ::~TFigureZ()
{
}

void TFigureZ::initialize()
{
    _rotateLeft();
}

void TFigureZ::_setFigureType(const TFigureType)
{
    m_relativeCoord[0].set({m_absoluteCoord.x, m_absoluteCoord.y});
    switch (m_figureType) {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_absoluteCoord.x, m_absoluteCoord.y - 1});
            m_relativeCoord[2].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[3].set({m_absoluteCoord.x + 1, m_absoluteCoord.y + 1});
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_absoluteCoord.x + 1, m_absoluteCoord.y});
            m_relativeCoord[2].set({m_absoluteCoord.x - 1, m_absoluteCoord.y + 1});
            m_relativeCoord[3].set({m_absoluteCoord.x, m_absoluteCoord.y + 1});
            break;
        default:
            assert(0);
    }
}

bool TFigureZ::_validation()
{
    return true;
}

TFigureType TFigureZ::getTypeBegin() const noexcept
{
    return TFigureType::A;
}

TFigureType TFigureZ::getTypeEnd() const noexcept
{
    return TFigureType::B;
}

const std::shared_ptr<TFigureInterface> TFigureZ::_copy() const
{
    return std::shared_ptr<TFigureZ>(new TFigureZ());
}

