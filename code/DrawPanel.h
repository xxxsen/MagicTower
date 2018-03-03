//
// Created by sen on 18-2-18.
//

#ifndef MAGICTOWER_DRAWPANEL_H
#define MAGICTOWER_DRAWPANEL_H

#include <SDL/SDL.h>
#include <memory>
#include <vector>
#include "tools/WordingStore.h"

class Dialog;
typedef std::shared_ptr<Dialog> DialogPtr;

class DrawPanel
{
private:
    DrawPanel();

public:
    static DrawPanel &instance();
    bool init(uint32_t width, uint32_t height);
    void destroy();
    SDL_Surface *raw();

public:
    void update();
    void drawRect(SDL_Surface *src, SDL_Rect *srcLoc, SDL_Rect *dstLoc, bool update = false);
    void backup();
    void restore();

public:
    DialogPtr newWordingDialog(uint32_t x, uint32_t y);
    DialogPtr newWordingDialog(const WordingListPtr &wording);
    DialogPtr newMsgBox(const std::string &msg);
    DialogPtr newCheckDialog(const std::string &msg);
    DialogPtr newSelectDialog(const std::vector<std::string> &wording);

private:
    SDL_Surface *surface_;
    typedef std::shared_ptr<SDL_Surface> PanelFrame;
    typedef std::vector<PanelFrame> FrameStack;
    FrameStack stk_;
};


#endif //MAGICTOWER_DRAWPANEL_H
