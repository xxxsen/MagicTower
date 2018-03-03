//
// Created by sen on 18-2-18.
//

#include <cassert>
#include "DrawPanel.h"
#include "Dialog.h"
#include "Consts.h"

DrawPanel::DrawPanel()
    : surface_(NULL)
{

}

DrawPanel &DrawPanel::instance()
{
    static DrawPanel panel;
    return panel;
}

bool DrawPanel::init(uint32_t width, uint32_t height)
{
    int ret = SDL_Init(SDL_INIT_VIDEO);
    assert(ret != -1);

    surface_ = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    assert(surface_ != NULL);
    return true;
}

SDL_Surface *DrawPanel::raw()
{
    return surface_;
}

void DrawPanel::destroy()
{
    SDL_FreeSurface(surface_);
    SDL_Quit();
}

void DrawPanel::update()
{
    SDL_Flip(surface_);
}

void DrawPanel::drawRect(SDL_Surface *src, SDL_Rect *srcLoc, SDL_Rect *dstLoc, bool update)
{
    SDL_BlitSurface(src, srcLoc, surface_, dstLoc);
    if(update)
        this->update();
}

DialogPtr DrawPanel::newWordingDialog(uint32_t x, uint32_t y)
{
    return DialogPtr(new WordingDialog(surface_, x, y));
}

DialogPtr DrawPanel::newMsgBox(const std::string &msg)
{
    return DialogPtr(new MsgBox(surface_, Global::instance().DEFAULT_DIALOG_LOC_X,
                                Global::instance().DEFAULT_DIALOG_LOC_Y,
                                Global::instance().DEFAULT_DIALOG_IMGID, msg));
}

DialogPtr DrawPanel::newWordingDialog(const WordingListPtr &wording)
{
    DialogPtr dialogPtr(newWordingDialog(Global::instance().DEFAULT_DIALOG_LOC_X,
                                         Global::instance().DEFAULT_DIALOG_LOC_Y));
    dynamic_cast<WordingDialog *>(dialogPtr.get())->setWording(Global::instance().DEFAULT_DIALOG_IMGID, wording);
    return dialogPtr;
}

DialogPtr DrawPanel::newCheckDialog(const std::string &msg)
{
    CheckDialog *dialog = new CheckDialog(surface_, 2, 150, msg);
    return DialogPtr(dialog);
}

DialogPtr DrawPanel::newSelectDialog(const std::vector<std::string> &wording)
{
    SelectDialog *dialog = new SelectDialog(surface_,
                                            Global::instance().DEFAULT_SELECT_DIALOG_LOC_X, Global::instance().DEFAULT_SELECT_DIALOG_LOC_Y,
                                            Global::instance().DEFAULT_SELECT_DIALOG_IMGID, Global::instance().DEFAULT_SELECT_ITEM_IMGID,
                                            wording);
    return DialogPtr(dialog);
}

void DrawPanel::backup()
{
    SDL_Surface *frame = SDL_DisplayFormat(surface_);
    stk_.push_back(PanelFrame(frame, [](SDL_Surface *p)->void { SDL_FreeSurface(p); }));
}

void DrawPanel::restore()
{
    if(!stk_.empty())
    {
        PanelFrame frame = stk_.back();
        stk_.pop_back();
        drawRect(frame.get(), NULL, NULL);
        update();

    }
}
