//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_FLOORLOADER_H
#define MAGICTOWER_FLOORLOADER_H

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <stdint.h>
#include "Global.h"
#include "tools/MagicFactory.h"
#include "Floor.h"


class FloorLoader
{
private:
    FloorLoader();

public:
    static FloorLoader &instance();

public:
    bool init(const Global &bs, const MagicFactory &fac);
    Floor &getFloor(uint32_t floor);
    uint32_t floorSize() const;

private:
    std::vector<Floor> floors_;
};


#endif //MAGICTOWER_FLOORLOADER_H
