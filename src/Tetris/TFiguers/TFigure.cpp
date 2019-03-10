#include <cassert>

#include "TFigure.h"
#include "TFigureBuilder.h"
#include "../../GameInterface/TypeTraits.h"

using namespace tetris;
using namespace game_interface;
using namespace sdleasygui;

TFigure::TFigure()
{}

TFigure::TFigure(const TFigureBuilder* bld)
   : m_width(bld->getWidth()),
    m_height(bld->getHeight()),
    m_figureType(bld->getType ()),
    m_absoluteCoord(bld->getPoint ()),
    m_color(bld->getColor()),
    m_figureClass(bld->getClass())
{
    if(m_figureType == TFigureType::None)
    {
        m_figureType = TFigureType::A;
        move(SDLK_LEFT);
    }

    setAll(bld->getUnitType());
    setAll(bld->getColor());
}


TFigure::~TFigure()
{
}


std::shared_ptr<TFigure> TFigure::move(const sdleasygui::t_eventType event)
{
    auto copied = copy();

    switch (event)
    {
        case SDLK_LEFT:
            _goLeft();
            break;
        case SDLK_RIGHT:
            _goRight ();
            break;
        case SDLK_UP:
            _rotateLeft();
            break;
        case SDLK_DOWN:
            _goDown();
            break;
        default:
            assert(0);
    }

    return copied;
}

TFigureUnit TFigure::getLeftmost()
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for(auto it = m_relativeCoord.begin()+1; it != end ; ++it)
    {
        if(unit.getPoint().x > it->getPoint().x)
            unit = *it;
    }
    return unit;
}

TFigureUnit TFigure::getRightmost()
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for(auto it = m_relativeCoord.begin()+1; it != end ; ++it)
    {
        if(unit.getPoint().x < it->getPoint().x)
            unit = *it;
    }
    return unit;
}

TFigureUnit TFigure::getUpmost()
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for(auto it = m_relativeCoord.begin()+1; it != end ; ++it)
    {
        if(unit.getPoint().y < it->getPoint().y)
            unit = *it;
    }
    return unit;
}

TFigureUnit TFigure::getDownmost()
{
    TFigureUnit unit = *m_relativeCoord.begin();
    const auto& end = m_relativeCoord.end();

    for(auto it = m_relativeCoord.begin()+1; it != end ; ++it)
    {
        if(unit.getPoint().y > it->getPoint().y)
            unit = *it;
    }
    return unit;
}

const std::shared_ptr<TFigure> TFigure::copy() const
{
    auto copied = _copy();
    copied->m_absoluteCoord = this->m_absoluteCoord;
    copied->m_color = this->m_color;
    copied->m_height = this->m_height;
    copied->m_width = this->m_width;
    copied->m_figureType = this->m_figureType;
    copied->m_figureTypeCount = this->m_figureTypeCount;
    copied->m_relativeCoord = this->m_relativeCoord;
    copied->m_figureClass = this->m_figureClass;

    return copied;
}

void TFigure::copy(const TFigure& fig)
{
    this->m_absoluteCoord = fig.m_absoluteCoord;
    this->m_color = fig.m_color;
    this->m_height = fig.m_height;
    this->m_width = fig.m_width;
    this->m_figureType = fig.m_figureType;
    this->m_figureTypeCount = fig.m_figureTypeCount;
    this->m_relativeCoord = fig.m_relativeCoord;
    this->m_figureClass = fig.m_figureClass;
}



void TFigure::_goRight ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].set ({x+1,y});
    }
    m_absoluteCoord.x +=1;
}

void TFigure::_goLeft ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].set ({x-1,y});
    }
    m_absoluteCoord.x -=1;
}

void TFigure::_goDown ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].set ({x,y+1});
    }
    m_absoluteCoord.y +=1;
}

const TFigureType TFigure::getRandomlyFigureType() const {
    return EnumHelper<TFigureType>::getRandomly(getTypeBegin(), getTypeEnd());
}

void TFigure::_resetRelateivePoint(const TPoint& newPt)
{
    const auto ptDis = TPoint{newPt.x - getPoint().x, newPt.y - getPoint().y};
    for(auto& p : m_relativeCoord)
    {
        p.set({p.getPoint().x+ptDis.x, p.getPoint().y+ptDis.y});
    }
}
