//
// Created by sen on 18-2-16.
//

#include <assert.h>
#include "MagicFactory.h"
#include "utils/Utility.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <utils/TowerLog.h>

MagicFactory::MagicFactory()
{

}

MagicFactory::MagicFactory(const MagicFactory &)
{

}

bool MagicFactory::init(const Global &bs)
{
    Json::Value v;
    bool result = Utility::loadJson(bs.resPath, v);
    (void)result;
    assert(result);
    for(Json::Value::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if(it->isMember("class"))
        {
            MagicObjectPtr item = create((*it)["class"].asString());
            bool result = item->construct(*it);
            if(!result)
            {
                TR_ERROR("class:%s construct failed, json:%s", (*it)["class"].asString().c_str(), (*it).toStyledString().c_str());
                assert(result);
                return false;

            }
            if(store_.count(item->getID()) != 0)
            {
                TR_ERROR("class:%s, id:%d already exist in store!", (*it)["class"].asString().c_str(), item->getID());
                assert(false);
                return false;
            }
            store_[item->getID()] = item;
        }
        else
        {
            TR_ERROR("Object in res.json should has key:\"class\", item:%s", (*it).toStyledString().c_str());
            assert(false);
            return false;
        }
    }
    TR_NORMAL("Magic factory init success!");
    return true;
}

MagicFactory &MagicFactory::instance()
{
    static MagicFactory factory;
    return factory;
}

MagicObjectPtr MagicFactory::create(const std::string &name) const
{
    auto iter = facMap_.find(name);
    if(iter == facMap_.end())
    {
        TR_ERROR("Not found class:%s in magic factory, may not regist? use REGIST_OBJECT(%s); to regist it!", name.c_str(), name.c_str());
        assert(iter != facMap_.end());
        return MagicObjectPtr();
    }
    return iter->second->create();
}

void MagicFactory::regist(const std::string &name, BasicFactory *fac)
{
    facMap_[name] = fac;
}

MagicObjectPtr MagicFactory::create(uint32_t id) const
{
    auto iter = store_.find(id);
    if(iter == store_.end())
    {
        assert(false);
        TR_ERROR("Not found magic id:%d in store, may not use define in res.json file?", id);
        return MagicObjectPtr();
    }
    return iter->second;
}
