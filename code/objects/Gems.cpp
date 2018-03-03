//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Gems.h"
#include "Player.h"

Gem::Gem()
    : MagicObject(MO_GEM), v_(0)
{

}

void Gem::setValue(int32_t v)
{
    v_ = v;
}

int32_t Gem::getValue() const
{
    return v_;
}

bool Gem::construct(const Json::Value &v)
{
    if(v.isMember("value"))
    {
        setValue(v["value"].asInt());
    }
    return MagicObject::construct(v);
}

void Gem::doCollision(Player &player)
{
    player.killBlock();
}

void AtkGem::doCollision(Player &player)
{
    player.setATK(player.getATK() + getValue());
    Gem::doCollision(player);
}

REGIST_OBJECT(AtkGem);

void DefGem::doCollision(Player &player)
{
    player.setDFS(player.getDFS() + getValue());
    Gem::doCollision(player);
}

REGIST_OBJECT(DefGem);

void SPGem::doCollision(Player &player)
{
    player.setSP(player.getSP() + getValue());
    Gem::doCollision(player);
}

REGIST_OBJECT(SPGem);

void HPGem::doCollision(Player &player)
{
    player.setHP(player.getHP() + getValue());
    Gem::doCollision(player);
}

REGIST_OBJECT(HPGem);

void MPGem::doCollision(Player &player)
{
    player.setMP(player.getMP() + getValue());
    Gem::doCollision(player);
}

REGIST_OBJECT(MPGem);