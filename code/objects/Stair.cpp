//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Stair.h"
#include "Player.h"
#include "FloorLoader.h"

Stair::Stair()
    : MagicObject(MO_STAIR)
{

}

void Stair::setType(StairType st)
{
    st_ = st;
}

StairType Stair::getType() const
{
    return st_;
}

bool Stair::construct(const Json::Value &v)
{
    if(v.isMember("direction"))
    {
        setType(static_cast<StairType>(v["direction"].asInt()));
    }
    else
    {
        assert(false);
    }
    return MagicObject::construct(v);
}

void Stair::doCollision(Player &player)
{
    if(getType() == ST_UP && player.getCurrentFloor() < FloorLoader::instance().floorSize() - 1)
        player.goUpstair();
    else if(getType() == ST_DOWN && player.getCurrentFloor() != 0)
        player.goDownStair();
}

REGIST_OBJECT(Stair);