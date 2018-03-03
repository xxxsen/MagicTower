//
// Created by sen on 18-2-18.
//

#include <cassert>
#include <json/json.h>
#include <utils/TowerLog.h>
#include "WordingStore.h"
#include "utils/Utility.h"

bool Wording::hasNext()
{
    return index_ < ptr_->size();
}

const std::string &Wording::next()
{
    return ptr_->at(index_++);
}

void Wording::reset()
{
    index_ = 0;
}

Wording::Wording()
    : index_(0)
{

}

void Wording::attach(const WordingListPtr &ptr)
{
    ptr_ = ptr;
}

bool WordingStore::init(const Global &bs)
{
    Json::Value v;
    bool result = Utility::loadJson(bs.wordingPath, v);
    assert(result);
    (void)result;
    for(Json::Value::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        const Json::Value &item = *it;
        if(!item.isMember("id") || !item.isMember("list"))
        {
            TR_ERROR("Not found id/list in json item, json:%s", item.toStyledString().c_str());
            assert(false);
            continue;
        }
        uint32_t id = item["id"].asUInt();
        const Json::Value &wordingList = item["list"];
        WordingListPtr lst(new WordingList());
        for(Json::Value::const_iterator it = wordingList.begin(); it != wordingList.end(); ++it)
        {
            lst->push_back(it->asString());
        }
        store_.insert(std::make_pair(id, lst));
    }
    TR_NORMAL("Wording store init success!");
    return true;
}

WordingListPtr WordingStore::get(uint32_t id)
{
    if(store_.count(id) == 0)
    {
        TR_ERROR("Not found wording id in wording store! id:%d", id);
        assert(false);
        return WordingListPtr();
    }
    return store_.at(id);
}

WordingStore::WordingStore()
{

}

WordingStore &WordingStore::instance()
{
    static WordingStore st;
    return st;
}
