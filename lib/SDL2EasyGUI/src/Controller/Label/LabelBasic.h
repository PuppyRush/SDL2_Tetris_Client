//
// Created by chaed on 19. 3. 31.
//

#ifndef PROJECT_LABELBASIC_H
#define PROJECT_LABELBASIC_H

#include <string>

#include "../Border.h"

namespace seg {

class LabelBasic : public Border
{

public:
    LabelBasic(ControlBuilder& bld);

    virtual ~LabelBasic()
    {}

    std::string getString()
    { return m_labelString; }

protected:

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void initialize() override;

    std::shared_ptr<SDL_Texture> m_texture;
    std::string m_labelString;
};

}

#endif //PROJECT_LABELBASIC_H
