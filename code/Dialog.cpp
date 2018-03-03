//
// Created by sen on 18-2-18.
//

#include <iostream>
#include <cassert>
#include <utils/TowerLog.h>
#include "Dialog.h"
#include "tools/WordingCreator.h"
#include "tools/ImageCreator.h"
#include "Consts.h"

SDL_Surface *Dialog::getParent()
{
    return parent_;
}

Dialog::Dialog(SDL_Surface *parent, int x, int y)
    : parent_(parent), x_(x), y_(y), wouldBreak_(false)
{

}

Dialog::~Dialog()
{

}

int Dialog::getX() const
{
    return x_;
}

int Dialog::getY() const
{
    return y_;
}

void Dialog::breakDialog()
{
    wouldBreak_ = true;
}

void Dialog::show()
{
    startLoop();
}

void Dialog::startLoop()
{
    while (true)
    {
        SDL_Event e;
        int ret = SDL_WaitEvent(&e);
        if(ret == 0)
        {
            TR_ERROR("Get game event failed, e:%s", SDL_GetError());
            assert(false);
            break;
        }
        if(e.type == SDL_QUIT)
            break;
        onEvent(e);
        if(wouldBreak_)
            break;
    }
}

void WordingDialog::show()
{
    showFrame(wordingWrap_.next());
    Dialog::show();
}

WordingDialog::WordingDialog(SDL_Surface *parent, int x, int y)
    : Dialog(parent, x, y)
{

}

void WordingDialog::onEvent(SDL_Event &e)
{
    if(e.type != SDL_KEYDOWN)
        return ;
    if(e.key.keysym.sym != SDLK_RETURN)
        return ;
    if(wordingWrap_.hasNext())
    {
        showFrame(wordingWrap_.next());
        return ;
    }
    wordingWrap_.reset();
    breakDialog();
}

void WordingDialog::setWording(const std::string &bg, const WordingListPtr &lst)
{
    bg_ = bg;
    wordingWrap_.attach(lst);
}

void WordingDialog::showFrame(const std::string &str)
{
    PicItem item;
    ImageCreator::instance().createAndCopy(bg_, item);
    SDL_SurfacePtr ptr = WordingCreator::instance().createWording(item.pic, str, 15, 15, true);
    SDL_Rect dst;
    dst.x = getX();
    dst.y = getY();
    dst.w = ptr->w;
    dst.h = ptr->h;
    SDL_BlitSurface(ptr.get(), NULL, getParent(), &dst);
    SDL_Flip(getParent());
}

MsgBox::MsgBox(SDL_Surface *parent, int x, int y, const std::string &bg, const std::string &msg)
    : WordingDialog(parent, x, y)
{
    setWording(bg, WordingListPtr(new WordingList({msg})));
}

void SelectDialog::show()
{
    PicItem panel;
    bool result = ImageCreator::instance().createAndCopy(bg_, panel);
    (void)result;
    assert(result);
    SDL_Rect rect;
    rect.x = getX();
    rect.y = getY();
    rect.w = panel.pic->w;
    rect.h = panel.pic->h;
    SDL_BlitSurface(panel.pic, NULL, getParent(), &rect);

    int beginHight = getY() + 14;
    int baseWidth = getX() + 14;
    for(int i = 0; i < items_.size(); ++i)
    {
        PicItem tmp;
        ImageCreator::instance().createAndCopy(item_, tmp);
        SDL_SurfacePtr ptr = WordingCreator::instance().createWording(tmp.pic, items_.at(i), 10, 10, true);
        ButtonPtr btn(new Button(getParent(), baseWidth, beginHight, ptr, (SDLKey)((int)SDLK_1 + i)));
        btn->draw();
        beginHight += ptr.get()->h;
        btns_.push_back(btn);
    }
    SDL_Flip(getParent());
    SDL_FreeSurface(panel.pic);
    Dialog::show();
}

void SelectDialog::onEvent(SDL_Event &e)
{
    for(int i = 0; i < (int)btns_.size(); ++i)
    {
        if(btns_.at(i)->isClicked(e))
        {
            selected_ = i;
            breakDialog();
            break;
        }
    }
}

SelectDialog::SelectDialog(SDL_Surface *parent, int x, int y, const std::string &bg, const std::string &item, const std::vector<std::string> &items)
        : Dialog(parent, x, y), bg_(bg), item_(item), items_(items), selected_(-1)
{

}

bool SelectDialog::hasSelected() const
{
    return selected_ != -1;
}

int32_t SelectDialog::getSelected() const
{
    return selected_;
}

void CheckDialog::show()
{
    PicItem item;
    ImageCreator::instance().createAndCopy(Global::instance().DEFAULT_DIALOG_IMGID, item);
    SDL_SurfacePtr ptr = WordingCreator::instance().createWording(item.pic, msg_, 15, 10, true);
    SDL_Rect dst;
    dst.x = getX();
    dst.y = getY();
    dst.w = ptr->w;
    dst.h = ptr->h;
    SDL_BlitSurface(ptr.get(), NULL, getParent(), &dst);
    //
    btnOk_.reset(new Button(getParent(), getX() + 400, getY() + 65, Global::instance().DEFAULT_OK_BTN_MSGID, SDLK_y));
    btnOk_->draw();
    //
    btnCl_.reset(new Button(getParent(), getX() + 330, getY() + 65, Global::instance().DEFAULT_CANCEL_BTN_MSGID, SDLK_n));
    btnCl_->draw();
    SDL_Flip(getParent());
    Dialog::show();
}

void CheckDialog::onEvent(SDL_Event &e)
{
    if(btnOk_->isClicked(e))
    {
        result_ = true;
        breakDialog();
    }
    if(btnCl_->isClicked(e))
    {
        result_ = false;
        breakDialog();
    }
}

CheckDialog::CheckDialog(SDL_Surface *parent, int x, int y, const std::string &msg)
        : Dialog(parent, x, y), result_(false), msg_(msg)
{

}

bool CheckDialog::checkResult() const
{
    return result_;
}

Button::Button(SDL_Surface *parent, int x, int y, const std::string &bg, const SDLKey &key)
    : parent_(parent), x_(x), y_(y), hotKey_(key)
{
    PicItem item;
    bool result = ImageCreator::instance().createAndCopy(bg, item);
    (void)result;
    assert(result);
    bg_.reset(item.pic, [](SDL_Surface *p)->void { SDL_FreeSurface(p); });

}

Button::Button(SDL_Surface *parent, int x, int y, const SDL_SurfacePtr &bg, const SDLKey &key)
    : parent_(parent), bg_(bg), x_(x), y_(y), hotKey_(key)
{

}

bool Button::isMouseDown(const SDL_Event &e)
{
    return e.type == SDL_MOUSEBUTTONDOWN;
}

bool Button::isMouseUp(const SDL_Event &e)
{
    return e.type == SDL_MOUSEBUTTONUP;
}

bool Button::isOnRect(const SDL_Event &e)
{
    if(/*isMouseDown(e) || */isMouseUp(e))
    {
        if(e.motion.x >= x_ && e.motion.x <= x_ + bg_->w && e.motion.y >= y_ && e.motion.y <= y_ + bg_->h)
            return true;
        else
        {
            TR_TRACE("User click at:(%d, %d), rect:(x:%d, y:%d, w:%d, h:%d)", e.motion.x, e.motion.y, x_, y_, bg_->w, bg_->h);
        }
    }
    return false;
}

bool Button::isClicked(const SDL_Event &e)
{
    return isHotKeyPressed(e) || isOnRect(e);
}

bool Button::isHotKeyPressed(const SDL_Event &e)
{
    if(/*isKeyDown(e) || */isKeyUp(e))
    {
        if(e.key.keysym.sym == hotKey_)
            return true;
    }
    return false;
}

bool Button::isKeyDown(const SDL_Event &e)
{
    return e.type == SDL_KEYDOWN;
}

bool Button::isKeyUp(const SDL_Event &e)
{
    return e.type == SDL_KEYUP;
}

void Button::draw()
{
    SDL_Rect dst;
    dst.x = x_;
    dst.y = y_;
    dst.w = bg_->w;
    dst.h = bg_->h;
    SDL_BlitSurface(bg_.get(), NULL, parent_, &dst);
}

