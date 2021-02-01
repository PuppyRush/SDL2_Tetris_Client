#ifndef TETRISMODULE_TFIGUREINTERFACE_H
#define TETRISMODULE_TFIGUREINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <bitset>
#include <cassert>
#include <memory>
#include <deque>
#include <numeric>
#include <array>

#include "GameInterface/include/Object.h"
#include "GameInterface/include/Type.h"
#include "GameInterface/include/TypeTraits.h"
#include "GameInterface/include/JsonPackage.h"

#include "TFigureUnit.h"
#include "TProperty.h"

namespace tetris_module{

/***********************************************
*		            □ □ □ □                    *
*		            □ □ ■ □                    *
*		            □ □ □ □                    *
*		            □ □ □ □                    *
*	   	      Relatevie Coordnation		       *
*	(x-2,y-1) (x-1,y-1) (x,y-1)	 (x+1,y-1)     *
*	(x-2,y  ) (x-1,y  ) (x,y  )	 (x+1,y  )     *
*	(x-2,y+1) (x-1,y+1) (x,y+1)	 (x+1,y+1)     *
*	(x-2,y+2) (x-1,y+2) (x,y+2)	 (x+1,y+2)     *
***********************************************/

class TFigureBuilder;

class TFigureInterface : game_interface::JsonPackage
{
public:

    using FigureCoords = std::array<TFigureUnit, 4>;

    virtual ~TFigureInterface();

    inline TFigureType getType() const noexcept
    { return m_figureType; }

    inline TFigureClass getClass() const noexcept
    { return m_figureClass; }

    inline size_t getWidth() const noexcept
    { return m_width; }

    inline size_t getHeight() const noexcept
    { return m_height; }

    inline seg::SEG_Color getColor() const noexcept
    { return m_color; }

    inline seg::SEG_Point getPoint() const noexcept
    { return m_absoluteCoord; }

    inline void setPoint(const seg::SEG_Point& point)
    {
        _resetRelateivePoint(point);
        m_absoluteCoord = point;
    }

    inline FigureCoords& getCoords() noexcept
    { return m_relativeCoord; }

    std::underlying_type_t<TFigureType>
    getTypeCount() const noexcept
    { return (game_interface::toUType(getTypeEnd()) - game_interface::toUType(getTypeBegin())) + 1; }

    std::shared_ptr<TFigureInterface> move(const seg::t_eventType event);

    TFigureUnit getLeftmost() const noexcept;

    TFigureUnit getRightmost() const noexcept;

    TFigureUnit getUpmost() const noexcept;

    TFigureUnit getDownmost() const noexcept;

    void copy(const TFigureInterface& fig);

    const std::shared_ptr<TFigureInterface> copy() const;

    virtual TFigureType getRandomlyFigureType() const noexcept;

    template<class T>
    inline void setAll(const T& type)
    {
        for (auto& unit : m_relativeCoord) {
            unit.set(type);
        }
    }

    template<class T>
    inline void setAll(T&& type)
    {
        for (auto& unit : m_relativeCoord) {
            unit.set(type);
        }
    }

    virtual void initialize() = 0;

    virtual TFigureType getTypeBegin() const noexcept = 0;

    virtual TFigureType getTypeEnd() const noexcept = 0;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    virtual const std::string_view& getUniqueName() const noexcept
    { return game_interface::NAME_FIGURE; }

protected:
    TFigureInterface(const TFigureBuilder* bld);

    TFigureInterface();

    virtual void _rotateLeft();

    seg::t_size m_width;
    seg::t_size m_height;
    seg::SEG_Color m_color;
    TFigureClass m_figureClass;
    TFigureType m_figureType;
    seg::SEG_Point m_absoluteCoord;
    FigureCoords m_relativeCoord;

private:
    virtual void _goRight();

    virtual void _goLeft();

    virtual void _goDown();

    virtual void _rotateRight() final
    { assert(0); } // not implementation yet

    void _resetRelateivePoint(const seg::SEG_Point& exPt);

    virtual const std::shared_ptr<TFigureInterface> _copy() const = 0;

    virtual bool _validation() = 0;

    virtual void _setFigureType(const TFigureType) = 0;
};

}

#endif