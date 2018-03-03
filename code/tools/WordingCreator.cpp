//
// Created by sen on 18-2-17.
//

#include <cassert>
#include <fstream>
#include <codecvt>
#include "WordingCreator.h"
#include "utils/Utility.h"
#include <locale>
#include <iostream>
#include <utils/TowerLog.h>

WordingCreator::WordingCreator()
    : font_(NULL), wordSize_(24)
{
    int ret = TTF_Init();
    (void) ret;
    assert(ret != -1);
}

WordingCreator::~WordingCreator()
{
    if(font_)
    {
        TTF_CloseFont(font_);
        font_ = NULL;
    }
    TTF_Quit();
}

bool WordingCreator::init(const Global &bs)
{
    Json::Value v;
    bool result = Utility::loadJson(bs.fontPath, v);
    if(!result)
    {
        TR_ERROR("Init wording creator, but load json failed, json path:%s", bs.fontPath);
        assert(false);
        return false;
    }
    if(v.isMember("font_size"))
        wordSize_ = v["font_size"].asUInt();
    std::string loc;
    if(v.isMember("font_location"))
        loc = bs.basicRoot + "/" + v["font_location"].asString();
    else
    {
        TR_ERROR("Load font info, but not found font location info!");
        assert(false);
        return false;
    }
    font_ = TTF_OpenFont(loc.c_str(), wordSize_);
    if(font_ == NULL)
    {
        TR_ERROR("Load font, but got null pointer, font loc:%s", loc.c_str());
        assert(false);
        return false;
    }
    TR_NORMAL("Wording creator init success!");
    return true;
}

SDL_SurfacePtr WordingCreator::createWording(const std::string &wording, SDL_Color color)
{
    SDL_Surface *surf = TTF_RenderText_Blended(font_, wording.c_str(), color);
    return SDL_SurfacePtr(surf, [](SDL_Surface *p)-> void { SDL_FreeSurface(p); });
}

SDL_SurfacePtr WordingCreator::createWording(const std::vector<std::string> &wording, SDL_Color color)
{
    if(wording.size() == 1)
        return createWording(wording[0], color);

    std::vector<SDL_Surface *> ct;
    int maxWidth = 0;
    int maxHeight = 0;
    for(auto &word : wording)
    {
        SDL_Surface *sf = TTF_RenderUTF8_Blended(font_, word.c_str(), color);
        maxHeight += sf->h;
        if(maxWidth < sf->w)
            maxWidth = sf->w;
        ct.push_back(sf);
    }
    SDL_Surface *screen = SDL_CreateRGBSurface(SDL_SWSURFACE, maxWidth, maxHeight, 8, 0, 0, 0, 0);
    SDL_Palette *palette = screen->format->palette;
    palette->colors[0].r = static_cast<Uint8>(255 - color.r);
    palette->colors[0].g = static_cast<Uint8>(255 - color.g);
    palette->colors[0].b = static_cast<Uint8>(255 - color.b);
    palette->colors[1].r = color.r;
    palette->colors[1].g = color.g;
    palette->colors[1].b = color.b;
    SDL_SetColorKey(screen, SDL_TRUE, 0);
    for(uint32_t i = 0; i < ct.size(); ++i)
    {
        SDL_Rect dst;
        dst.w = static_cast<Uint16>(ct.at(i)->w);
        dst.h = static_cast<Uint16>(ct.at(i)->h);
        dst.x = 0;
        dst.y = static_cast<Sint16>(i * ct.at(i)->h);
        SDL_BlitSurface(ct.at(i), NULL, screen, &dst);
        SDL_FreeSurface(ct.at(i));
    }
    return SDL_SurfacePtr(screen, [](SDL_Surface *p)-> void { SDL_FreeSurface(p); });

}

SDL_SurfacePtr WordingCreator::createWording(SDL_Surface *screen, const std::vector<std::string> &wording, int x, int y, bool autoRelease, SDL_Color color)
{
    std::vector<SDL_Surface *> ct;
    int maxWidth = 0;
    int maxHeight = 0;
    for(auto &word : wording)
    {
        SDL_Surface *sf = TTF_RenderUTF8_Blended(font_, word.c_str(), color);
        maxHeight += sf->h;
        if(maxWidth < sf->w)
            maxWidth = sf->w;
        ct.push_back(sf);
    }
    for(uint32_t i = 0; i < (int)ct.size(); ++i)
    {
        SDL_Rect dst;
        dst.w = static_cast<Uint16>(ct.at(i)->w);
        dst.h = static_cast<Uint16>(ct.at(i)->h);
        dst.x = static_cast<Sint16>(x);
        dst.y = static_cast<Sint16>(y + i * ct.at(i)->h);
        SDL_BlitSurface(ct.at(i), NULL, screen, &dst);
        SDL_FreeSurface(ct.at(i));
    }
    return SDL_SurfacePtr(screen, [autoRelease](SDL_Surface *p)-> void { if(autoRelease) SDL_FreeSurface(p); });
}

WordingCreator &WordingCreator::instance()
{
    static WordingCreator cr;
    return cr;
}

SDL_Color WordingCreator::defaultColor_ = {0xff, 0xff, 0xff, 0};

SDL_SurfacePtr WordingCreator::createWording(SDL_Surface *bg, const std::string &wording, int x, int y, bool autoRelease, SDL_Color color)
{
    std::vector<std::string> lst;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(wording);
    std::wstring tmp;
    uint32_t counter = 0;
    uint32_t cntPerLine = (bg->w - x * 2) / (wordSize_) * 2;
    for(uint32_t i = 0; i < wide.size(); ++i)
    {
        if(wide.at(i) < 128)
            ++counter;
        else
            counter += 2;
        tmp.push_back(wide.at(i));
        if(counter >= cntPerLine || i + 1 == wide.size())
        {
            lst.push_back(converter.to_bytes(tmp));
            tmp.clear();
            counter = 0;
            TR_TRACE("Wording split to line:%s", lst.back().c_str());
        }
    }
    return createWording(bg, lst, x, y, autoRelease, color);
}
