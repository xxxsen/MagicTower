//
// Created by sen on 18-2-16.
//

#include <cassert>
#include <iostream>
#include <utils/TowerLog.h>
#include "MagicObject.h"
#include "tools/MagicFactory.h"
#include "Player.h"

MagicObject::MagicObject(MOType type)
    : id_(-1), dc_(DC_DOWN), type_(type)
{

}

MagicObject::~MagicObject()
{

}


MagicObject &MagicObject::setDesc(const std::string &desc)
{
    desc_ = desc;
    return *this;
}

MagicObject &MagicObject::setID(uint32_t id)
{
    id_ = id;
    return *this;
}

const std::string &MagicObject::getDESC() const
{
    return desc_;
}

uint32_t MagicObject::getID() const
{
    return id_;
}

MagicObject &MagicObject::setBasicPic(const std::string &path)
{
    for(int i = 0; i < 4; ++i)
        picGroup_.push_back(path);
    return *this;
}

MagicObject &MagicObject::setDirectionPic(const std::vector<std::string> &paths)
{
    assert(paths.size() == 4);
    picGroup_ = paths;
    return *this;
}

const std::string &MagicObject::getCurrentPic() const
{
    return picGroup_.at(dc_);
}

void MagicObject::changeDirection(TowerDirection tc)
{
    dc_ = tc;
}

MOType MagicObject::getMagicObjectType() const
{
    return type_;
}

void MagicObject::doCollision(Player &player)
{
    player.goBack();
}

MagicObject &MagicObject::setName(const std::string &name)
{
    name_ = name;
    return *this;
}

const std::string &MagicObject::getName() const
{
    return name_;
}

bool MagicObject::construct(const Json::Value &v)
{
    if(v.isMember("id"))
    {
        setID(v["id"].asUInt());
    }
    else
    {
        assert(false);
        return false;
    }
    if(v.isMember("desc"))
        setDesc(v["desc"].asString());
    else
        setDesc("default objects!");
    if(v.isMember("name"))
        setName(v["name"].asString());
    else
        setName("no name objects!");
    if(v.isMember("img"))
    {
        if(v["img"].isString())
            setBasicPic(v["img"].asString());
        else if(v["img"].isArray())
        {
            std::vector<std::string> dir;
            for(Json::Value::const_iterator it = v["img"].begin(); it != v["img"].end(); ++it)
            {
                dir.push_back(it->asString());
            }
            assert(dir.size() == 4);
            setDirectionPic(dir);
        }
    }
    else
    {
        setBasicPic("res/null.bmp");
    }
    if(v.isMember("exp"))
        setExp(v["exp"].asInt());
    else
        setExp(0);
    if(v.isMember("coin"))
        setCoin(v["coin"].asInt());
    else
        setCoin(0);
    return true;
}

TowerDirection MagicObject::getCurrentDirection() const
{
    return dc_;
}

const std::string &MagicObject::getSpecPic(TowerDirection dc) const
{
    return picGroup_.at(dc);
}

void MagicObject::backup(Json::Value &v)
{
    v["id"] = getID();
    v["desc"] = getDESC();
    v["img"] = getCurrentPic();
    v["name"] = getName();
    v["coin"] = getCoin();
    v["exp"] = getExp();
}

void MagicObject::restore(const Json::Value &v)
{
    construct(v);
}

int32_t MagicObject::getCoin() const
{
    return coin_;
}

int32_t MagicObject::getExp() const
{
    return exp_;
}

MagicObject &MagicObject::setCoin(int32_t coin)
{
    coin_ = coin;
    return *this;
}

MagicObject &MagicObject::setExp(int32_t exp)
{
    exp_ = exp;
    return *this;
}


BasicFactory::~BasicFactory()
{

}

MagicClassRegister::MagicClassRegister(const std::string &name, BasicFactory *target)
{
    MagicFactory::instance().regist(name, target);
    TR_NORMAL("Regist object type:%s", name.c_str());
}
