//
// Created by chaed on 19. 3. 5.
//

#include "MessageDialog.h"
#include "include/SEG_Drawer.h"

using namespace seg;

MessageDialog::MessageDialog(const std::string& message, MessageDialogKind kind)
        : DisplayInterface(), m_message(message), m_kind(kind)
{
    setBackgroundColor(ColorCode::white);
}

std::underlying_type_t<resource> MessageDialog::alert() 
{
    return DisplayInterface::alert();
}

void MessageDialog::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_OK), &MessageDialog::onClickOk, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_YES), &MessageDialog::onClickYes, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_NO), &MessageDialog::onClickNo, this);
}

void MessageDialog::onInitialize()
{
    setWindowTitle(m_message);
    setBackgroundColor(seg::ColorCode::black);
    setWindowHeight(150);
    setWindowWidth(200);

    SEG_Color borderColor{ColorCode::yellow};
    switch (m_kind) {
        case MessageDialogKind::alert:
            borderColor = ColorCode::green;
            break;
        case MessageDialogKind::error:
            borderColor = ColorCode::red;
            break;
        case MessageDialogKind::warining:
            borderColor = ColorCode::yellow;
            break;
    }

    t_size begin_y = getWindowHeight() / 2 - 100;
    {
        StaticLabelBuilder bld(getSEGWindow(), {20, 20}, m_message);
        bld.id(seg::toUType(resource::MESSAGEDIALOG_MSG))->
                fontColor(ColorCode::black)->
                width(240)->
                height(50)->
                backgroundColor(ColorCode::white)->
                borderColor(borderColor)->
                borderThick(3)->
                enabled(true);

        addControl(bld.build());

        auto ctl = getControl<StaticLabel>(resource::MESSAGEDIALOG_MSG);
        auto wh = drawer::getTextSize(ctl->getFont().getTTF_Font(), ctl->getControlText());

        if (wh.first > wh.second) {
            ctl->setWidth(wh.first + 20);
        }
        if (wh.first > getWindowWidth()) {
            setWindowWidth(wh.first + 80);
        }
    }

    {
        ButtonBuilder bld(getSEGWindow(), {getWindowWidth() - 120, 70}, "OK");
        bld.id(seg::toUType(resource::BTN_OK))->
                fontSize(18)->
                fontColor(ColorCode::black)->
                width(60)->
                height(30)->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::black)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }

    DisplayInterface::onInitialize();
}

void MessageDialog::onClickOk(const void*)
{
    DisplayInterface::onOk();
}

void MessageDialog::onClickYes(const void*)
{
    DisplayInterface::onOk();
}

void MessageDialog::onClickNo(const void*)
{
    DisplayInterface::onNo();
}
