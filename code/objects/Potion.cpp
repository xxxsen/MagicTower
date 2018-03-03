//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Potion.h"

bool Potion::construct(const Json::Value &v)
{
    return MagicObject::construct(v);
}

Potion::Potion()
    : MagicObject(MO_POTION)
{

}

void Potion::doCollision(Player &player)
{
    //TODO:
}

REGIST_OBJECT(Potion);