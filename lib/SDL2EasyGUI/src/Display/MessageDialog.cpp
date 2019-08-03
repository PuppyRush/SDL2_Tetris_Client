//
// Created by chaed on 19. 3. 5.
//

#include "MessageDialog.h"
#include <include/SEG_Drawer.h>

using namespace seg;

MessageDialog::MessageDialog(const std::string& message, MessageDialogKind kind)
        : DisplayInterface(toUType(MESSAGEDIALOG_MSG)), m_message(message), m_kind(kind)
{
    setWindowTitle(message);
    setWindowHeight(150);
    setWindowWidth(200);

    setBackgroundColor(ColorCode::white);
}

void MessageDialog::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_OK), &MessageDialog::onClickOk, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_YES), &MessageDialog::onClickYes, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::BTN_NO), &MessageDialog::onClickNo, this);
}

void MessageDialog::onInitialize()
{
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
        StaticLabelBuilder bld(getWindow(), {20, 20}, m_message);
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
        auto renderer = ctl->getSDLRenderer();
        TextDrawer textDrawer{renderer, ctl->getFont(), SEG_Point{0,0}, ctl->getString()};

        if (textDrawer.getTextWidth() > ctl->getHeight()) {
            ctl->setWidth(textDrawer.getTextWidth() + 20);
        }
        if (textDrawer.getTextWidth() > getWindowWidth()) {
            setWindowWidth(textDrawer.getTextWidth() + 80);
        }
    }

    {
        ButtonBuilder bld(getWindow(), {getWindowWidth() - 120, 70}, "OK");
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

    DisplayInterface::onOK();
}

void MessageDialog::onClickYes(const void*)
{

    DisplayInterface::onOK();
}

void MessageDialog::onClickNo(const void*)
{

    DisplayInterface::onNO();
}
