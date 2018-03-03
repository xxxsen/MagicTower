//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_MAGICTOWER_H
#define MAGICTOWER_MAGICTOWER_H


#include <cstdint>
#include "Global.h"
#include "tools/MagicFactory.h"
#include "FloorLoader.h"
#include "objects/Player.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <string>
#include <SDL/SDL_ttf.h>

class Tower
{
    enum MTMode { MODE_WALK, MODE_TALK, MODE_FIGHT };
public:
    Tower();

public:
    void init(const std::string &file);
    void destroy();

public:
    void drawFloor();

public:
    void process();
    bool wouldLoop();
    void breakLoop();

public:
    void onEvent(const SDL_Event &e);

protected:
    bool isCanMove(TowerDirection dc, const TowerPoint &src, TowerPoint &dst);

private:
    typedef std::map<std::string, SDL_Surface *> ImageGroup;
    Global &basicSetting_;
    MagicFactory &fac_;
    FloorLoader &floor_;
    ImageGroup mapper_;
    Player *hero_;
    TTF_Font *font_;
    bool needLoop_;
};


#endif //MAGICTOWER_MAGICTOWER_H
