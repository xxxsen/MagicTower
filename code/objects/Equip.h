//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_EQUIP_H
#define MAGICTOWER_EQUIP_H

#include "MagicObject.h"

class Equip : public MagicObject
{
public:
    Equip();

public:
    void doCollision(Player &player) override;
    bool construct(const Json::Value &v) override;
};

class Sword : public Equip
{
public:
    void doCollision(Player &player) override;

    bool construct(const Json::Value &v) override;
};

#endif //MAGICTOWER_EQUIP_H
