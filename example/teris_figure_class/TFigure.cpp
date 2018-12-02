#include "TFigure.h"
#include "TFigureBuilder.h"
#include "TypeTraits.h"

using namespace tetris;

TFigure::TFigure()
{}

TFigure::TFigure(const TFigureBuilder* bld)
   : m_width(bld->getWidth()),
    m_height(bld->getHeight()),
    m_figureType(bld->getType ()),
    m_point(bld->getPoint ())
{
    if(m_figureType == TFigureType::None)
    {
        m_figureType = TFigureType::A;
        rotateLeft ();
    }
}


TFigure::~TFigure()
{
}

std::shared_ptr<TFigure> TFigure::goRight()
{
    auto copied = copy();
    _goRight ();
    return copied;
}
std::shared_ptr<TFigure> TFigure::goLeft()
{
    auto copied = copy();
    _goLeft ();
    return copied;
}

std::shared_ptr<TFigure> TFigure::goDown()
{
    auto copied = copy();
    _goDown ();
    return copied;
}

std::shared_ptr<TFigure> TFigure::rotateLeft()
{
    auto copied = copy();
    _rotateLeft ();
    return copied;
}

std::shared_ptr<TFigure> TFigure::rotateRight()
{
    auto copied = copy();
    _rotateRight ();
    return copied;
}

const std::shared_ptr<TFigure> TFigure::copy() const
{
    auto copied = _copy();
    copied->m_point = this->m_point;
    copied->m_height = this->m_height;
    copied->m_width = this->m_width;
    copied->m_figureType = this->m_figureType;
    copied->m_figureTypeCount = this->m_figureTypeCount;
    copied->m_relativeCoord = this->m_relativeCoord;
    
    return copied;
}



void TFigure::_goRight ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].setPoint (TPoint(x+1,y));
    }
    m_point.x +=1;
}

void TFigure::_goLeft ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].setPoint (TPoint(x-1,y));
    }
    m_point.x -=1;
}

void TFigure::_goDown ()
{
    for(int i=0 ; i < m_relativeCoord.size() ; i++)
    {
        auto y = m_relativeCoord[i].getPoint ().y;
        auto x = m_relativeCoord[i].getPoint ().x;
        m_relativeCoord[i].setPoint (TPoint(x,y+1));
    }
    m_point.y +=1;
}

const TFigureType TFigure::getRandomlyFigureType() const {
    return EnumHelper<TFigureType>::getRandomly(getTypeBegin(), getTypeEnd());
}
