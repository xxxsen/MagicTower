//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_MAGICOBJECT_H
#define MAGICTOWER_MAGICOBJECT_H

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <json/value.h>
#include "Consts.h"

class MagicObject;
class Player;
typedef std::shared_ptr<MagicObject> MagicObjectPtr;

class MagicFactory;

class MagicObject
{
public:
    explicit MagicObject(MOType type);
    virtual ~MagicObject();

public:
    virtual void doCollision(Player &player);
    virtual bool construct(const Json::Value &v);
    virtual void backup(Json::Value &v);
    void restore(const Json::Value &v);

public:

    MagicObject &setDesc(const std::string &desc);
    MagicObject &setID(uint32_t id);
    MagicObject &setName(const std::string &name);
    MagicObject &setBasicPic(const std::string &path);
    MagicObject &setDirectionPic(const std::vector<std::string> &paths);
    TowerDirection getCurrentDirection() const;
    const std::string &getDESC() const;
    uint32_t getID() const;
    const std::string &getName() const;
    const std::string &getCurrentPic() const;
    const std::string &getSpecPic(TowerDirection dc) const;
    void changeDirection(TowerDirection tc);
    MOType getMagicObjectType() const;
    int32_t getCoin() const;
    int32_t getExp() const;
    MagicObject &setCoin(int32_t coin);
    MagicObject &setExp(int32_t exp);


private:
    std::string desc_;
    uint32_t id_;
    std::string name_;
    std::vector<std::string> picGroup_;
    TowerDirection dc_;
    MOType type_;
    int32_t exp_;
    int32_t coin_;
};

class BasicFactory
{
public:
    virtual ~BasicFactory();

public:
    virtual MagicObjectPtr create() = 0;
};

class MagicClassRegister
{
public:
    MagicClassRegister(const std::string &name, BasicFactory *target);
};

#define REGIST_OBJECT(CLASS_NAME) \
class FACTORY_##CLASS_NAME : public BasicFactory\
{\
public:\
    MagicObjectPtr create() \
    {\
        return MagicObjectPtr(new CLASS_NAME()); \
    }\
public:\
    static const MagicClassRegister reg_; \
}; \
const MagicClassRegister FACTORY_##CLASS_NAME::reg_(#CLASS_NAME, new FACTORY_##CLASS_NAME())


#endif //MAGICTOWER_MAGICOBJECT_H
