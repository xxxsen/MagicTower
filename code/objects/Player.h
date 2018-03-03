//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_HERO_H
#define MAGICTOWER_HERO_H

#include <set>
#include "Enemy.h"

class Tower;

class Player : public Enemy
{
public:
    Player();

public:
    Player &setYellowKey(int32_t key);
    Player &setBlueKey(int32_t key);
    Player &setRedKey(int32_t key);
    int32_t getRedKey() const;
    int32_t getYellowKey() const;
    int32_t getBlueKey() const;

public:
    void move(const TowerPoint &point);
    void goDie();
    void goBack();
    void goUpstair();
    void goDownStair();
    void goToDownStairIndex();
    void goToUpStairIndex();
    void killBlock();
    uint32_t getCurrentFloor() const;
    void refresh();
    const TowerPoint &getCurrentPos() const;
    const std::set<uint32_t> getVistedFloor() const;
    void attachTower(Tower *tower);

public:
    bool isDie() const;

protected:
    void goSpecFloor(uint32_t floor);

public:
    bool construct(const Json::Value &v) override;

private:
    int32_t redKeySize_;
    int32_t blueKeySize_;
    int32_t yellowKeySize_;
    uint32_t currentFloor_;
    TowerPoint currentPos_;
    TowerPoint oldPos_;
    std::set<uint32_t> floorView_;
    bool isDie_;
    Tower *tower_;
};


#endif //MAGICTOWER_HERO_H
