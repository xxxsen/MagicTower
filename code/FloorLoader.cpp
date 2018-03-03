//
// Created by sen on 18-2-16.
//

#include <assert.h>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include "FloorLoader.h"
#include "objects/MagicObject.h"
#include "tools/MagicFactory.h"
#include "utils/Utility.h"
#include "utils/TowerLog.h"

FloorLoader::FloorLoader()
{

}

bool FloorLoader::init(const Global &bs, const MagicFactory &fac)
{
    Json::Value v;
    bool result = Utility::loadJson(bs.mapPath, v);
    if(!result)
    {
        TR_ERROR("Load json object failed, path:%s", bs.mapPath.c_str());
        assert(false);
        return false;
    }
    const Json::Value item = v["floor_layout_list"];
    floors_.resize(item.size());
    int k = 0;
    for(Json::Value::const_iterator it = item.begin(); it != item.end(); ++it)
    {
        std::string location = bs.basicRoot + "/" + it->asString();
        Json::Value floor;
        result = Utility::loadJson(location, floor);
        if(!result)
        {
            assert(false);
            return false;
        }
        if(!floor.isMember("up_index"))
        {
            TR_ERROR("Load floor info but not found up index!");
            assert(false);
            return false;
        }
        if(!floor.isMember("down_index"))
        {
            TR_ERROR("Load floor info but not found down index!!!!");
            assert(false);
            return false;
        }
        if(!floor.isMember("map"))
        {
            TR_ERROR("Load floor info but not found floor map info!");
        }
        floors_[k].setUpIndex(TowerPoint(floor["up_index"][0].asInt(), floor["up_index"][1].asInt()));
        floors_[k].setDownIndex(TowerPoint(floor["down_index"][0].asInt(), floor["down_index"][1].asInt()));
        const Json::Value fm = floor["map"];
        for(int i = 0; i < fm.size(); ++i)
        {
            for(int j = 0; j < fm[i].size(); ++j)
            {
                MagicObjectPtr back;
                MagicObjectPtr front;
                if(fm[i][j].isArray())
                {
                    back = fac.create(fm[i][j][0].asUInt());
                    front = fac.create(fm[i][j][1].asUInt());

                }
                else
                {
                    back = fac.create(bs.DEFAULT_ROAD_ID);
                    front = fac.create(fm[i][j].asUInt());
                }
                assert(front != nullptr);
                assert(back != nullptr);
                floors_[k].set(j, i, front, back);

            }
        }
        TR_NORMAL("Load floor map:%d success, up index:(%d, %d), down index:(%d, %d)",
                  k,
                  floors_[k].getUpIndex().x, floors_[k].getUpIndex().y,
                  floors_[k].getDownIndex().x, floors_[k].getDownIndex().y
        );
        ++k;
    }
    TR_NORMAL("Floor info init success!");
    return true;
}

Floor &FloorLoader::getFloor(uint32_t floor)
{
    assert(floor < floors_.size());
    return floors_.at(floor);
}

FloorLoader &FloorLoader::instance()
{
    static FloorLoader loader;
    return loader;
}

uint32_t FloorLoader::floorSize() const
{
    return static_cast<uint32_t>(floors_.size());
}

