//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_BUILDING_H
#define MAGICTOWER_BUILDING_H

#include "MagicObject.h"

class Building : public MagicObject
{
public:
    Building();

public:
    bool construct(const Json::Value &v) override;
};


#endif //MAGICTOWER_BUILDING_H
