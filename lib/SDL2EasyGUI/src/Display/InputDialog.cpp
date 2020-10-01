//
// Created by chaed on 19. 3. 5.
//

#include "InputDialog.h"
#include <include/SEG_Drawer.h>

using namespace seg;

InputDialog::InputDialog(const std::string& message)
    : m_message(message)
{
    setBackgroundColor(ColorCode::white);
}

std::underlying_type_t<resource> InputDialog::alert()
{
    return DisplayInterface::alert();
}

void InputDialog::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_OK), &InputDialog::onClickOk, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_YES), &InputDialog::onClickYes, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_NO), &InputDialog::onClickNo, this);
}

void InputDialog::onInitialize()
{
    setWindowTitle(m_message);
    setBackgroundColor(seg::ColorCode::black);
    setWindowHeight(150);
    setWindowWidth(200);

    SEG_Color borderColor{ ColorCode::yellow };

    DisplayInterface::onInitialize();
}

void InputDialog::onClickOk(const void*)
{
    DisplayInterface::onOk();
}

void InputDialog::onClickYes(const void*)
{
    DisplayInterface::onOk();
}

void InputDialog::onClickNo(const void*)
{
    DisplayInterface::onNo();
}
