//
// Created by sen on 18-2-17.
//

#ifndef MAGICTOWER_KEY_H
#define MAGICTOWER_KEY_H


#include "MagicObject.h"

class Key : public MagicObject
{
public:
    Key();

public:
    bool construct(const Json::Value &v) override;

    void doCollision(Player &player) override;

    int32_t getSize();
    void setSize(uint32_t sz);
    KeyType getKeyType() const;
    void setKeyType(KeyType type);

public:
    int32_t sz_;
    KeyType type_;
};


#endif //MAGICTOWER_KEY_H
