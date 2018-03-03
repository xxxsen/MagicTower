//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Building.h"

Building::Building()
        : MagicObject(MO_BUILDING)
{

}

bool Building::construct(const Json::Value &v)
{
    return MagicObject::construct(v);
}

REGIST_OBJECT(Building);