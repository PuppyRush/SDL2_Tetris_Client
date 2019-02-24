//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"
#include "../SEG_Event.h"

using namespace std;
using namespace sdleasygui;

EditLabel::EditLabel(EditLabelBuilder& bld)
    :Border(bld), m_labelBasic(bld.m_editBasic)
{
    bld.kind(ControllKind::EditLabel);

    m_textCursorTimerAdder = make_shared<TimerAdder>(700,game_interface::toUType(SEG_Event::EDITLABEL_CHAR_TEXTCURSOR));
}

void EditLabel::onTimer()
{

}

void EditLabel::onUserEvent (const SDL_UserEvent* user)
{
    switch(user->type)
    {
        case EDITLABEL_CHAR_TEXTCURSOR:
            m_textCursor = !m_textCursor;
            refresh();
            break;
    }
    Border::onUserEvent(user);
}

void EditLabel::onAttachFocus()
{
    if(m_textCursorTimer == NULL_TIMER_ID)
    {
        m_textCursorTimer = m_textCursorTimerAdder->addTimer();
        m_textCursor = true;
        setSelected(true);
    }
}

void EditLabel::onDetachFocus()
{
    SDL_RemoveTimer(m_textCursorTimer);
    m_textCursor = false;
    m_textCursorTimer = NULL_TIMER_ID;
    setSelected(false);
}

void EditLabel::onKeyboardEvent (const SDL_KeyboardEvent* key)
{
    if(!isSelected())
        return;

    switch(key->type)
    {
        case SDL_KEYDOWN:
            switch(key->keysym.sym)
            {
                case SDLK_BACKSPACE:
                    if(!m_basic->name.empty())
                        m_basic->name.pop_back();
                    break;
            }
            break;
    }
    Border::onKeyboardEvent(key);
}

void EditLabel::onTextInputEvent (const SDL_TextInputEvent* text)
{
    if(!isSelected())
        return;

    m_basic->name.append(text->text);
    Border::onTextInputEvent(text);
}

void EditLabel::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer().get();
    const auto& fontinfo = getFont();
    TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
    SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, m_basic->name.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    const double text_width = static_cast<double>(textSurface->w);
    const double text_height = static_cast<double>(textSurface->h);

    const auto point = getPoint();
    SDL_Rect renderQuad = { static_cast<int>(point.x +5)
        , static_cast<int>(point.y + ( getHeight() - text_height)/2)
        , static_cast<int>(text_width)
        , static_cast<int>(text_height) };
    SDL_RenderCopy(renderer, text, nullptr, &renderQuad);

    if(m_textCursor)
    {
        SDL_Point points[]
        ={  { static_cast<t_size>(point.x + text_width+10), point.y+5},
            { static_cast<t_size>(point.x + text_width+10), point.y+ static_cast<t_size>(getHeight()) -5},
            { static_cast<t_size>(point.x + text_width+10), point.y+5}};

        TColor lineColor{ColorCode::white};
        SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, 255);
        SDL_RenderDrawLines(renderer,points,SDL_arraysize(points));
    }

    Border::onDraw();
}

void EditLabel::onDrawBackground()
{
    auto renderer = getWindow()->getSDLRenderer().get();

    const auto &back_color = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);

    SDL_Rect rect = SDL_Rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};
    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick()*2)+1;
    rect.w = (rect.w - getBorderThick()*2)+1;

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}


void EditLabel::initialize()
{
    Border::initialize();
}

