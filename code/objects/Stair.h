//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_STAIR_H
#define MAGICTOWER_STAIR_H

#include "MagicObject.h"

class Stair : public MagicObject
{
public:
    Stair();

public:
    void setType(StairType st);
    StairType getType() const;

public:
    bool construct(const Json::Value &v) override;

    void doCollision(Player &player) override;

private:
    StairType st_;
};


#endif //MAGICTOWER_STAIR_H
