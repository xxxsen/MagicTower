//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_OBJECTFACTORY_H
#define MAGICTOWER_OBJECTFACTORY_H

#include "objects/MagicObject.h"
#include "Global.h"
#include <string>
#include <map>
#include <cstdint>

class MagicFactory
{
private:
    MagicFactory();
    MagicFactory(const MagicFactory &);

public:
    bool init(const Global &bs);

public:
    static MagicFactory &instance();

public:
    MagicObjectPtr create(uint32_t id) const;
    MagicObjectPtr create(const std::string &name) const;
    void regist(const std::string &name, BasicFactory *fac);

private:
    typedef std::map<std::string, BasicFactory *> FatoryMap;
    FatoryMap facMap_;
    typedef std::map<uint32_t, MagicObjectPtr> MagicObjectStore;
    MagicObjectStore store_;

};


#endif //MAGICTOWER_OBJECTFACTORY_H
