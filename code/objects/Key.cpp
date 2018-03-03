//
// Created by sen on 18-2-17.
//

#include "Key.h"
#include "Player.h"

Key::Key()
    : MagicObject(MO_KEY)
{

}

bool Key::construct(const Json::Value &v)
{
    if(v.isMember("cnt"))
        sz_ = v["cnt"].asInt();
    if(v.isMember("color"))
        type_  = static_cast<KeyType>(v["color"].asInt());

    return MagicObject::construct(v);
}

int32_t Key::getSize()
{
    return sz_;
}

void Key::setSize(uint32_t sz)
{
    sz_ = sz;
}

KeyType Key::getKeyType() const
{
    return type_;
}

void Key::setKeyType(KeyType type)
{
    type_ = type;
}

void Key::doCollision(Player &player)
{
    switch(type_)
    {
        case KEY_BLUE:
            player.setBlueKey(player.getBlueKey() + sz_);
            break;
        case KEY_YELLOW:
            player.setYellowKey(player.getYellowKey() + sz_);
            break;
        case KEY_RED:
            player.setRedKey(player.getRedKey() + sz_);
            break;
    }
    if(player.getRedKey() < 0)
        player.setRedKey(0);
    if(player.getYellowKey() < 0)
        player.setYellowKey(0);
    if(player.getBlueKey() < 0)
        player.setBlueKey(0);
    player.killBlock();
}

REGIST_OBJECT(Key);