//
// Created by sen on 18-2-16.
//

#include <cassert>
#include <iostream>
#include <sstream>
#include <utils/TowerLog.h>
#include "Tower.h"
#include "FloorLoader.h"
#include "tools/MagicFactory.h"
#include "objects/Stair.h"
#include "tools/WordingCreator.h"
#include "tools/ImageCreator.h"
#include "DrawPanel.h"
#include "tools/WordingStore.h"
#include "Dialog.h"


void Tower::process()
{
    hero_->attachTower(this);
    hero_->goToDownStairIndex();
    drawFloor();

    while(true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        //while(SDL_PollEvent(&event))
        if(event.type == SDL_QUIT)
            break;
        onEvent(event);
        if(!wouldLoop())
            break;
    }
    drawFloor();
    if(hero_->isDie())
    {
        DrawPanel::instance().newMsgBox(WordingStore::instance().get(basicSetting_.GAME_OVER_MSGID)->at(0))->show();
    }
    SDL_Quit();
}


void Tower::init(const std::string &file)
{
    DrawPanel::instance().init(480 + 160, 480);
    basicSetting_.init(file);
    TowerLog::instance().init(static_cast<TRLOG_LEVEL>(basicSetting_.DEFAULT_LOG_LEVEL), basicSetting_.DEFAULT_LOG_FILE);
    WordingStore::instance().init(basicSetting_);
    ImageCreator::instance().init(basicSetting_);
    WordingCreator::instance().init(basicSetting_);
    fac_.init(basicSetting_);
    floor_.init(basicSetting_, fac_);
    hero_ = dynamic_cast<Player *>(fac_.create(basicSetting_.DEFAULT_HERO_ID).get());
    assert(font_ != NULL);
}

void Tower::destroy()
{

}

void Tower::drawFloor()
{
    Floor &floor = floor_.getFloor(hero_->getCurrentFloor());
    SDL_Rect rect;
    rect.w = basicSetting_.DEFAULT_ICON_WIDTH;
    rect.y = basicSetting_.DEFAULT_ICON_HEIGHT;
    for(int i = 0; i < floor.raw().size(); ++i)
    {
        for(int j = 0; j < floor.raw().size(); ++j)
        {
            rect.x = i * basicSetting_.DEFAULT_ICON_WIDTH;
            rect.y = j * basicSetting_.DEFAULT_ICON_HEIGHT;

            const Block &block = floor.indexAt(i, j);
            PicItem item;
            if(block.hasBackground())
            {
                ImageCreator::instance().create(block.getBackground()->getCurrentPic(), item);
                DrawPanel::instance().drawRect(item.pic, item.loc, &rect);
            }
            if(block.hasFrontground())
            {
                ImageCreator::instance().create(block.getFrontground()->getCurrentPic(), item);
                DrawPanel::instance().drawRect(item.pic, item.loc, &rect);
            }

        }
    }
    PicItem item;
    ImageCreator::instance().create(hero_->getCurrentPic(), item);
    rect.x = hero_->getCurrentPos().x * basicSetting_.DEFAULT_ICON_WIDTH;
    rect.y = hero_->getCurrentPos().y * basicSetting_.DEFAULT_ICON_HEIGHT;
    DrawPanel::instance().drawRect(item.pic, item.loc, &rect);

    //draw msg
    std::vector<std::string> wording;
    wording.push_back("生命:" + std::to_string(hero_->getHP()));
    wording.push_back("魔法:" + std::to_string(hero_->getMP()));
    wording.push_back("速度:" + std::to_string(hero_->getSP()));
    wording.push_back("攻击:" + std::to_string(hero_->getATK()));
    wording.push_back("防御:" + std::to_string(hero_->getDFS()));
    wording.push_back("金币:" + std::to_string(hero_->getCoin()));
    wording.push_back("经验:" + std::to_string(hero_->getExp()));
    wording.push_back("红钥匙:" + std::to_string(hero_->getRedKey()));
    wording.push_back("蓝钥匙:" + std::to_string(hero_->getBlueKey()));
    wording.push_back("黄钥匙:" + std::to_string(hero_->getYellowKey()));


    SDL_Rect rct;
    rct.x = 15 * 32 + 20;
    rct.y = 10;
    SDL_SurfacePtr ptr = WordingCreator::instance().createWording(wording);
    DrawPanel::instance().drawRect(ptr.get(), NULL, &rct, true);
}

bool Tower::isCanMove(TowerDirection dc, const TowerPoint &src, TowerPoint &dst)
{
    Floor &floor = floor_.getFloor(hero_->getCurrentFloor());
    const TowerPoint &tp = hero_->getCurrentPos();
    dst = src;
    switch(dc)
    {
        case DC_UP:
            if(src.y <= 0)
                return false;
            --dst.y;
            break;
        case DC_DOWN:
            if(src.y >= floor.raw().size() - 1)
                return false;
            ++dst.y;
            break;
        case DC_LEFT:
            if(src.x <= 0)
                return false;
            --dst.x;
            break;
        case DC_RIGHT:
            if(src.x >= floor.raw()[0].size() - 1)
                return false;
            ++dst.x;
            break;
        default:
            assert(false);
            return false;
    }
    return true;
}

Tower::Tower()
    : basicSetting_(Global::instance()), fac_(MagicFactory::instance()), floor_(FloorLoader::instance()), needLoop_(true)
{

}

void Tower::onEvent(const SDL_Event &e)
{
    if(e.type != SDL_KEYDOWN)
        return;
    bool hasDirection = true;
    TowerDirection direction;
    switch(e.key.keysym.sym)
    {
        case SDLK_UP:
        case SDLK_w:
            direction = DC_UP;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            direction = DC_DOWN;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            direction = DC_LEFT;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            direction = DC_RIGHT;
            break;
        default:
            hasDirection = false;
    }
    TowerPoint next;
    if(hasDirection && isCanMove(direction, hero_->getCurrentPos(), next))
    {
        hero_->changeDirection(direction);
        hero_->move(next);
        Floor &floor = floor_.getFloor(hero_->getCurrentFloor());
        const Block &block = floor.indexAt(hero_->getCurrentPos().x, hero_->getCurrentPos().y);
        MagicObjectPtr target = (block.hasFrontground() ? block.getFrontground() : block.getBackground());

        target->doCollision(*hero_);
        hero_->refresh();
        if(hero_->isDie())
        {
            TR_NORMAL("Player die, game over!");
            breakLoop();
        }
        else
        {
            drawFloor();
            TR_TRACE("Move hero from src:(%d, %d) to dst:(%d, %d)", hero_->getCurrentPos().x, hero_->getCurrentPos().y, next.x, next.y);
        }
    }
}

void Tower::breakLoop()
{
    needLoop_ = false;
}

bool Tower::wouldLoop()
{
    return needLoop_;
}

