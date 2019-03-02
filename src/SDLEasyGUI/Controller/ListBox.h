//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "Border.h"

namespace sdleasygui {

enum class ListBoxTypes : t_type {
    multiclicked,
    editable,
    clickable,
};

enum class ListBoxScrollType : t_type {
    vertical,
    horizen,
    both
};

class ListBoxBuilder;
class ListBox : public Border {

public:
    explicit ListBox(ListBoxBuilder &bld);

    void appendItem(const std::string& str);

    virtual void initialize() override;
    virtual void onDraw() override;

private:
    std::vector<std::string> m_menus;

};

class ListBoxBuilder : public BorderBuilder {
public:

    ListBoxBuilder(const GraphicInterface::window_ptr window, const TPoint &point, const std::string &str)
        : BorderBuilder(window, point, str) {
    }

    ListBoxBuilder(const GraphicInterface::window_ptr window, TPoint &&point, std::string &&str)
        : BorderBuilder(window, point, str) {
    }

    virtual std::shared_ptr<Controll> build() final {
        return std::make_shared<ListBox>(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
