//
// Created by chaed on 19. 3. 31.
//

#ifndef PROJECT_LABELBASIC_H
#define PROJECT_LABELBASIC_H

#include <string>

#include "../Border.h"

namespace seg {

typedef struct EditLabelBasic
{
    bool canWritable = true;
    bool canReadable = true;
    bool isOnlyNumber = false;
    bool isOnlyString = false;
    t_size maxlen = 20;
    std::string editstring;
} EditLabelBasic;

class LabelBasucBuilder;

class LabelBasic : public Border
{

public:
    LabelBasic(LabelBasucBuilder& bld);

    virtual ~LabelBasic()
    {}

    bool isEmpty() const noexcept
    {
        return m_labelBasic.editstring.empty();
    }

    std::string& getLabelString() noexcept
    { return m_labelBasic.editstring; }

    inline void clearString() noexcept
    {
        m_labelBasic.editstring.clear();
        onDraw();
    }


protected:

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void initialize() override;

    std::shared_ptr<SDL_Texture> m_texture;
    EditLabelBasic m_labelBasic;

};

class LabelBasucBuilder : public BorderBuilder
{
public:

    LabelBasucBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
        : BorderBuilder(window, point, str)
    {
    }

    LabelBasucBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
        : BorderBuilder(window, point, str)
    {
    }

    virtual ~LabelBasucBuilder() = default;

    virtual Control::control_ptr build() = 0;

    EditLabelBasic m_editBasic;
};

}

#endif //PROJECT_LABELBASIC_H
