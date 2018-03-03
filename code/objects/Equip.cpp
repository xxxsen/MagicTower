//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Equip.h"

Equip::Equip()
    : MagicObject(MO_EQUIP)
{

}

void Equip::doCollision(Player &player)
{
    //TODO:
    assert(false);
}

bool Equip::construct(const Json::Value &v)
{
    return MagicObject::construct(v);
}

REGIST_OBJECT(Equip);

void Sword::doCollision(Player &player)
{
    Equip::doCollision(player);
}

bool Sword::construct(const Json::Value &v)
{

}

REGIST_OBJECT(Sword);
