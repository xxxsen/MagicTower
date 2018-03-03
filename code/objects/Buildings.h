//
// Created by sen on 18-2-17.
//

#ifndef MAGICTOWER_BUILDINGS_H
#define MAGICTOWER_BUILDINGS_H

#include "Building.h"

class Wall : public Building
{
public:
    void doCollision(Player &player) override;
};

class Road : public Building
{
public:
    void doCollision(Player &player) override;
};

class Door : public Building
{
public:
    Door();

public:
    bool construct(const Json::Value &v) override;

    void doCollision(Player &player) override;

public:
    int32_t getCost() const;
    void setCost(uint32_t cost);

private:
    int32_t cost_;
};

class RedDoor : public Door
{
public:
    RedDoor();

public:
    void doCollision(Player &player) override;
};

class BlueDoor : public Door
{
public:
    void doCollision(Player &player) override;
};

class YellowDoor : public Door
{
public:
    void doCollision(Player &player) override;
};

class AffectBlock : public Road
{
public:
    AffectBlock();

public:
    void doCollision(Player &player) override;
    bool construct(const Json::Value &v) override;

public:
    void setCost(int32_t cost);
    int32_t getCost() const;
    void setAutoDelete(int32_t v);
    int32_t getAutoDelete() const;

private:
    int32_t cost_;
    int32_t autoDelete_;
};

class Lava : public AffectBlock
{
public:
    void doCollision(Player &player) override;
};

#endif //MAGICTOWER_BUILDINGS_H
