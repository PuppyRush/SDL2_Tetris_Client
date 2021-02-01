//
// Created by chaed on 19. 3. 5.
//

#ifndef SDL2EASYGUI_INPUTDIALOG_H
#define SDL2EASYGUI_INPUTDIALOG_H

#include "include/DisplayInterface.h"

namespace seg {

class InputDialog : public DisplayInterface
{

public:
    InputDialog(const std::string& message);

    virtual ~InputDialog()
    {}

    virtual const t_id getDisplayId() const noexcept override final
    {
        return resource::INPUT_DIALOG;
    }

    virtual std::underlying_type_t<resource> alert() override;

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    virtual void postCreate(display_ptr display) override
    {}

    virtual void postDestroy(const unique_type unique) override
    {}

    virtual void onClose() override
    {
        DisplayInterface::onClose();
    }

    virtual bool validId(const seg::t_id id) noexcept
    {
        return getWindowID() == id;
    }

    void onClickOk(const void*);

    void onClickYes(const void*);

    void onClickNo(const void*);

private:

    std::string m_message;
};

}

#endif //SDL2EASYGUI_INPUTDIALOG_H
