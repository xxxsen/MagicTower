//
// Created by sen on 18-2-16.
//

#include <cassert>
#include "Player.h"
#include "FloorLoader.h"
#include "Tower.h"

Player::Player()
        : Enemy(MO_PLAYER), redKeySize_(1), blueKeySize_(1), yellowKeySize_(1), currentPos_(0, 0), currentFloor_(0), tower_(NULL)
{
    floorView_.insert(0);
    isDie_ = false;
}

Player &Player::setYellowKey(int32_t key)
{
    yellowKeySize_ = key;
    return *this;
}

Player &Player::setBlueKey(int32_t key)
{
    blueKeySize_ = key;
    return *this;
}

Player &Player::setRedKey(int32_t key)
{
    redKeySize_ = key;
    return *this;
}

int32_t Player::getRedKey() const
{
    return redKeySize_;
}

int32_t Player::getYellowKey() const
{
    return yellowKeySize_;
}

int32_t Player::getBlueKey() const
{
    return blueKeySize_;
}

bool Player::construct(const Json::Value &v)
{
    if(v.isMember("red_key"))
        setRedKey(v["red_key"].asUInt());
    if(v.isMember("blue_key"))
        setBlueKey(v["blue_key"].asUInt());
    if(v.isMember("yellow_key"))
        setYellowKey(v["yellow_key"].asUInt());
    return Enemy::construct(v);
}

void Player::goUpstair()
{
    goSpecFloor(currentFloor_ + 1);
}

void Player::goDownStair()
{
    if(currentFloor_ != 0)
        goSpecFloor(currentFloor_ - 1);
    else
        goSpecFloor(currentFloor_);
}

uint32_t Player::getCurrentFloor() const
{
    return currentFloor_;
}

void Player::refresh()
{
    if(tower_)
        tower_->drawFloor();
}

const TowerPoint &Player::getCurrentPos() const
{
    return currentPos_;
}

const std::set<uint32_t> Player::getVistedFloor() const
{
    return floorView_;
}

void Player::goSpecFloor(uint32_t floor)
{
    uint32_t old = currentFloor_;
    floorView_.insert(floor);
    currentFloor_ = floor;
    if(old < currentFloor_)
        goToDownStairIndex();
    else
        goToUpStairIndex();
}

bool Player::isDie() const
{
    return isDie_;
}

void Player::goBack()
{
    currentPos_ = oldPos_;
}

void Player::move(const TowerPoint &point)
{
    if(oldPos_.x == -1)
    {
        currentPos_ = oldPos_ = point;
    }
    else
    {
        oldPos_ = currentPos_;
        currentPos_ = point;
    }
}

void Player::goToDownStairIndex()
{
    TowerPoint next = FloorLoader::instance().getFloor(currentFloor_).locateDownStairPoint(currentFloor_);
    move(next);
}

void Player::goToUpStairIndex()
{
    TowerPoint next = FloorLoader::instance().getFloor(currentFloor_).locateUpStairPoint(currentFloor_);
    move(next);
}

void Player::killBlock()
{
    FloorLoader::instance().getFloor(currentFloor_).raw()[currentPos_.y][currentPos_.x].clearFrontground();
}

void Player::goDie()
{
    isDie_ = true;
}

void Player::attachTower(Tower *tower)
{
    tower_ = tower;
}


REGIST_OBJECT(Player);
