#include <cassert>

#include "../include/TFigureInterface.h"
#include "../include/TFigureBuilder.h"
#include "GameInterface/include/TypeTraits.h"

using namespace game_interface;
using namespace sdleasygui;
using namespace std;
using namespace tetris_module;

TFigureInterface::TFigureInterface()
{}

TFigureInterface::TFigureInterface(const TFigureBuilder* bld)
        : m_width(bld->getWidth()),
          m_height(bld->getHeight()),
          m_figureType(bld->getType()),
          m_absoluteCoord(bld->getPoint()),
          m_color(bld->getColor()),
          m_figureClass(bld->getClass())
{
    if (m_figureType == TFigureType::None) {
        m_figureType = TFigureType::A;
        move(SDLK_LEFT);
    }

    setAll(bld->getUnitType());
    setAll(bld->getColor());
}

TFigureInterface::~TFigureInterface()
{
}

std::shared_ptr<TFigureInterface> TFigureInterface::move(const sdleasygui::t_eventType event)
{
    auto copied = copy();

    switch (event) {
        case SDLK_LEFT:
            _goLeft();
            break;
        case SDLK_RIGHT:
            _goRight();
            break;
        case SDLK_UP:
            _rotateLeft();
            break;
        case SDLK_SPACE:
        case SDLK_DOWN:
            _goDown();
            break;
        default:
            assert(0);
    }

    return copied;
}

TFigureUnit TFigureInterface::getLeftmost() const noexcept
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for (auto it = m_relativeCoord.begin() + 1; it != end; ++it) {
        if (unit.getPoint().x > it->getPoint().x) {
            unit = *it;
        }
    }
    return unit;
}

TFigureUnit TFigureInterface::getRightmost() const noexcept
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for (auto it = m_relativeCoord.begin() + 1; it != end; ++it) {
        if (unit.getPoint().x < it->getPoint().x) {
            unit = *it;
        }
    }
    return unit;
}

TFigureUnit TFigureInterface::getUpmost() const noexcept
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for (auto it = m_relativeCoord.begin() + 1; it != end; ++it) {
        if (unit.getPoint().y < it->getPoint().y) {
            unit = *it;
        }
    }
    return unit;
}

TFigureUnit TFigureInterface::getDownmost() const noexcept
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for (auto it = m_relativeCoord.begin() + 1; it != end; ++it) {
        if (unit.getPoint().y > it->getPoint().y) {
            unit = *it;
        }
    }
    return unit;
}

const std::shared_ptr<TFigureInterface> TFigureInterface::copy() const
{
    auto copied = _copy();
    copied->m_absoluteCoord = this->m_absoluteCoord;
    copied->m_color = this->m_color;
    copied->m_height = this->m_height;
    copied->m_width = this->m_width;
    copied->m_figureType = this->m_figureType;
    copied->m_relativeCoord = this->m_relativeCoord;
    copied->m_figureClass = this->m_figureClass;

    return copied;
}

void TFigureInterface::copy(const TFigureInterface& fig)
{
    this->m_absoluteCoord = fig.m_absoluteCoord;
    this->m_color = fig.m_color;
    this->m_height = fig.m_height;
    this->m_width = fig.m_width;
    this->m_figureType = fig.m_figureType;
    this->m_relativeCoord = fig.m_relativeCoord;
    this->m_figureClass = fig.m_figureClass;
    this->_setFigureType(fig.m_figureType);
}

void TFigureInterface::_goRight()
{
    for (int i = 0; i < m_relativeCoord.size(); i++) {
        auto y = m_relativeCoord[i].getPoint().y;
        auto x = m_relativeCoord[i].getPoint().x;
        m_relativeCoord[i].set({x + 1, y});
    }
    m_absoluteCoord.x += 1;
}

void TFigureInterface::_goLeft()
{
    for (int i = 0; i < m_relativeCoord.size(); i++) {
        auto y = m_relativeCoord[i].getPoint().y;
        auto x = m_relativeCoord[i].getPoint().x;
        m_relativeCoord[i].set({x - 1, y});
    }
    m_absoluteCoord.x -= 1;
}

void TFigureInterface::_goDown()
{
    for (int i = 0; i < m_relativeCoord.size(); i++) {
        auto y = m_relativeCoord[i].getPoint().y;
        auto x = m_relativeCoord[i].getPoint().x;
        m_relativeCoord[i].set({x, y + 1});
    }
    m_absoluteCoord.y += 1;
}

void TFigureInterface::_rotateLeft()
{
    _setFigureType(m_figureType);

    const auto next = (game_interface::toUType(m_figureType) + 1);
    m_figureType = TFigureType{static_cast<std::underlying_type_t<TFigureType >>(next % getTypeCount())};
}

TFigureType TFigureInterface::getRandomlyFigureType() const noexcept
{
    return EnumHelper<TFigureType>::getRandomly(getTypeBegin(), getTypeEnd());
}

void TFigureInterface::_resetRelateivePoint(const TPoint& newPt)
{
    const auto ptDis = TPoint{newPt.x - getPoint().x, newPt.y - getPoint().y};
    for (auto& p : m_relativeCoord) {
        p.set({p.getPoint().x + ptDis.x, p.getPoint().y + ptDis.y});
    }
}

void TFigureInterface::fromJson(const Json::Value& json)
{
    string in = json[getUniqueName().data()].asString();

    this->m_absoluteCoord.x = static_cast<t_coord>(bitset<10>(in.substr(5, 10)).to_ulong());
    this->m_absoluteCoord.y = static_cast<t_coord>(bitset<20>(in.substr(15, 20)).to_ulong());

    this->m_figureClass = static_cast<decltype(m_figureClass)>(bitset<3>(in.substr(0, 3)).to_ulong());
    this->m_figureType = static_cast<decltype(m_figureType)>( bitset<2>(in.substr(3, 2)).to_ulong());
}

Json::Value TFigureInterface::toJson() const
{
    Json::Value json;

    bitset<3> tetriminoBit(toUType(getClass()));
    bitset<2> directionBit(toUType(getType()));
    bitset<10> xBit(getPoint().x);
    bitset<20> yBit(getPoint().y);

    string concator = tetriminoBit.to_string() + directionBit.to_string() + xBit.to_string() + yBit.to_string();
    json[getUniqueName().data()] = bitset<35>(concator).to_string();

    return json;
}
