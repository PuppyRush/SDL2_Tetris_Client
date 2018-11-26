#include "TFigureL.h"
#include "TypeTraits.h"

using namespace tetris;

TFigureL::TFigureL (const TFigureBuilder *bld)
    : TFigure (bld)
{
    _rotateLeft ();
}

TFigureL::~TFigureL ()
{
}

void TFigureL::initialize ()
{
    m_figureTypeCount = toUType (getTypeEnd ()) - toUType (getTypeBegin ());
}

void TFigureL::_goRight ()
{

}

void TFigureL::_goLeft ()
{
}

void TFigureL::_goDown ()
{
}

void TFigureL::_rotateLeft ()
{
    m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y));
    
    switch (m_figureType)
        {
    case TFigureType::A:m_relativeCoord[0].setPoint (TPoint (m_point.x - 1, m_point.y));
            m_relativeCoord[0].setPoint (TPoint (m_point.x - 1, m_point.y - 1));
            m_relativeCoord[0].setPoint (TPoint (m_point.x + 1, m_point.y));
            m_figureType = TFigureType::B;
            break;
    case TFigureType::B:m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y + 1));
            m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y - 1));
            m_relativeCoord[0].setPoint (TPoint (m_point.x + 1, m_point.y + 1));
            m_figureType = TFigureType::C;
            break;
    case TFigureType::C:m_relativeCoord[0].setPoint (TPoint (m_point.x - 1, m_point.y));
            m_relativeCoord[0].setPoint (TPoint (m_point.x + 1, m_point.y));
            m_relativeCoord[0].setPoint (TPoint (m_point.x + 1, m_point.y - 1));
            m_figureType = TFigureType::D;
            break;
    case TFigureType::D:m_relativeCoord[0].setPoint (TPoint (m_point.x - 1, m_point.y - 1));
            m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y - 1));
            m_relativeCoord[0].setPoint (TPoint (m_point.x, m_point.y + 1));
            m_figureType = TFigureType::A;
            break;
        }
}

void TFigureL::_rotateRight ()
{
}

bool TFigureL::Validation ()
{}

const TFigureType TFigureL::getTypeBegin () const
{
    return TFigureType::A;
}

const TFigureType TFigureL::getTypeEnd () const
{
    return TFigureType::D;
}

const TFigureType TFigureL::getRandomlyFigureType () const
{
    return EnumHelper<TFigureType>::getRandomly (getTypeBegin (), getTypeEnd ());
}


