//
// Created by chaed on 19. 5. 1.
//

#ifndef TETRISMODULE_TFIGURES_H
#define TETRISMODULE_TFIGURES_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TFigureInterface.h"

namespace tetris_module {

/********************************
*		  □ □ □ □	 □ □ ■ □    *
*		  ■ ■ ■ ■	 □ □ ■ □    *
*		  □ □ □ □    □ □ ■ □    *
*		  □ □ □ □    □ □ ■ □    *
*	type  	 A		    B	    *
*	width	 1		    4	    *
*	height   4		    1	    *
*								*
********************************/

class TFigureBuilder;

class TFigureI final : public TFigureInterface
{
public:

    virtual ~TFigureI();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureI> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureI>(new TFigureI(bld));
        figure->initialize();
        return figure;
    }

private:
    TFigureI()
    {}

    TFigureI(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigureInterface> _copy() const override final;

    virtual void _setFigureType(const TFigureType) override final;
};

/***************************************************
*		  □ □ □ □	 □ □ ■ □   □ □ □ ■	 □ ■ ■ □   *
*		  □ ■ ■ ■	 □ □ ■ □   □ ■ ■ ■   □ □ ■ □   *
*		  □ ■ □ □    □ □ ■ ■   □ □ □ □   □ □ ■ □   *
*		  □ □ □ □    □ □ □ □   □ □ □ □   □ □ □ □   *
*	type  	 A		    B		  C			D	   *
*	width	 3		    2		  3			2	   *
*	height   2		    3		  2			3	   *
*												   *
***************************************************/

class TFigureL final : public TFigureInterface
{
public:

    virtual ~TFigureL();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureL> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureL>(new TFigureL(bld));
        figure->initialize();
        return figure;
    }

    TFigureL()
    {}

private:

    TFigureL(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigureInterface> _copy() const override final;

    //implement pure virtual funtions.
    virtual void _setFigureType(const TFigureType) override final;
};

/*********************
*		  □ □ □ □	 *
*		  □ ■ ■ □	 *
*		  □ ■ ■ □    *
*		  □ □ □ □    *
*	type  	 A		 *
*	width	 2		 *
*	height   2		 *
**********************/

class TFigureO final : public TFigureInterface
{
public:

    virtual ~TFigureO();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureO> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureO>(new TFigureO(bld));
        figure->initialize();
        return figure;
    }

private:
    TFigureO()
    {}

    TFigureO(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigureInterface> _copy() const override final;

    virtual void _setFigureType(const TFigureType) override final;
};

/***************************************************
*		  □ □ □ □	 □ □ ■ □   □ □ ■ □	 □ □ ■ □   *
*		  □ ■ ■ ■	 □ □ ■ ■   □ ■ ■ ■   □ ■ ■ □   *
*		  □ □ ■ □    □ □ ■ □   □ □ □ □   □ □ ■ □   *
*		  □ □ □ □    □ □ □ □   □ □ □ □   □ □ □ □   *
*	type  	 A		    B		  C			D	   *
*	width	 3		    2		  3			2	   *
*	height   2		    3		  2			3	   *
*												   *
***************************************************/

class TFigureT final : public TFigureInterface
{
public:

    virtual ~TFigureT();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureT> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureT>(new TFigureT(bld));
        figure->initialize();
        return figure;
    }

    TFigureT()
    {}

private:

    TFigureT(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigureInterface> _copy() const override final;

    //implement pure virtual funtions.
    virtual void _setFigureType(const TFigureType) override final;
};

/********************************
*		  □ □ □ □	 □ □ ■ □    *
*		  □ □ ■ ■	 □ □ ■ ■    *
*		  □ ■ ■ □    □ □ □ ■    *
*		  □ □ □ □    □ □ □ □    *
*	type  	 A		    B	    *
*	width	 3		    2	    *
*	height   2		    3	    *
*								*
********************************/

class TFigureZ final : public TFigureInterface
{
public:

    virtual ~TFigureZ();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureZ> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureZ>(new TFigureZ(bld));
        figure->initialize();
        return figure;
    }

private:
    TFigureZ()
    {}

    TFigureZ(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigureInterface> _copy() const override final;

    virtual void _setFigureType(const TFigureType) override final;
};

}

#endif //SDL2_TETIRS_CLIENT_TFIGURES_H
