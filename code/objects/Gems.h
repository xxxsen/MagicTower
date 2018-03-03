//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_GEM_H
#define MAGICTOWER_GEM_H


#include "MagicObject.h"

class Gem : public MagicObject
{
public:
    Gem();

public:
    void setValue(int32_t v);
    int32_t getValue() const;

public:
    bool construct(const Json::Value &v) override;

    void doCollision(Player &player) override;

private:
    int32_t v_;
};

class AtkGem : public Gem
{
public:
    void doCollision(Player &player) override;
};

class DefGem : public Gem
{
public:
    void doCollision(Player &player) override;
};

class SPGem : public Gem
{
public:
    void doCollision(Player &player) override;
};

class HPGem : public Gem
{
public:
    void doCollision(Player &player) override;
};

class MPGem : public Gem
{
public:
    void doCollision(Player &player) override;
};

#endif //MAGICTOWER_GEM_H
