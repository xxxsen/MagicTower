//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_POTION_H
#define MAGICTOWER_POTION_H

#include "MagicObject.h"

class Potion : public MagicObject
{
public:
    Potion();

public:
    bool construct(const Json::Value &v) override;
    void doCollision(Player &player) override;
};


#endif //MAGICTOWER_POTION_H
