//
// Created by sen on 18-2-17.
//

#include <DrawPanel.h>
#include <utils/XPrintf.h>
#include "Buildings.h"
#include "Player.h"
#include "Dialog.h"

void Wall::doCollision(Player &player)
{
    Building::doCollision(player);
}

REGIST_OBJECT(Wall);

void Road::doCollision(Player &player)
{
    //
}

REGIST_OBJECT(Road);

bool Door::construct(const Json::Value &v)
{
    if(v.isMember("cost"))
    {
        cost_ = v["cost"].asInt();
    }
    return Building::construct(v);
}

void Door::doCollision(Player &player)
{
    Building::doCollision(player);
}

Door::Door()
    : cost_(0)
{

}

int32_t Door::getCost() const
{
    return cost_;
}

void Door::setCost(uint32_t cost)
{
    cost_ = cost;
}

REGIST_OBJECT(Door);

void RedDoor::doCollision(Player &player)
{
    if(player.getRedKey() < getCost())
    {
        player.goBack();
        return ;
    }
    player.setRedKey(player.getRedKey() - getCost());
    player.killBlock();
}

RedDoor::RedDoor()
{

}

REGIST_OBJECT(RedDoor);

void BlueDoor::doCollision(Player &player)
{
    if(player.getBlueKey() < getCost())
    {
        player.goBack();
        return ;
    }
    player.setBlueKey(player.getBlueKey() - getCost());
    player.killBlock();
}

REGIST_OBJECT(BlueDoor);

void YellowDoor::doCollision(Player &player)
{
    if(player.getYellowKey() < getCost())
    {
        player.goBack();
        return ;
    }
    player.setYellowKey(player.getYellowKey() - getCost());
    player.killBlock();
}

REGIST_OBJECT(YellowDoor);

void Lava::doCollision(Player &player)
{
    player.setHP(player.getHP() - getCost());
    DrawPanel::instance().newMsgBox(sen::utils::xsprintf(WordingStore::instance().get(15)->at(0).c_str(), getCost()))->show();
    AffectBlock::doCollision(player);
}

REGIST_OBJECT(Lava);

bool AffectBlock::construct(const Json::Value &v)
{
    if(v.isMember("cost"))
        setCost(v["cost"].asInt());
    else
        setCost(0);
    if(v.isMember("auto_delete"))
        setAutoDelete(v["auto_delete"].asInt());
    else
        setAutoDelete(0);
    return MagicObject::construct(v);
}

void AffectBlock::doCollision(Player &player)
{
    if(getAutoDelete())
        player.killBlock();
}

void AffectBlock::setCost(int32_t cost)
{
    cost_ = cost;
}

int32_t AffectBlock::getCost() const
{
    return cost_;
}

AffectBlock::AffectBlock()
    : cost_(0), autoDelete_(0)
{

}

void AffectBlock::setAutoDelete(int32_t v)
{
    autoDelete_ = v;
}

int32_t AffectBlock::getAutoDelete() const
{
    return autoDelete_;
}
