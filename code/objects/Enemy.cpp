//
// Created by sen on 18-2-16.
//

#include <cassert>
#include <iostream>
#include <utils/TowerLog.h>
#include "Enemy.h"
#include "tools/WordingStore.h"
#include "Dialog.h"
#include "DrawPanel.h"
#include "Player.h"
#include "utils/XPrintf.h"

Enemy::Enemy()
    : Enemy(MO_ENEMY)
{

}

void Enemy::setResistance(SKCompatibility sk, int32_t v)
{
    resistance_[sk] = v;
}

int32_t Enemy::getResistance(SKCompatibility sk)
{
    auto iter = resistance_.find(sk);
    if(iter == resistance_.end())
        return 0;
    return iter->second;
}

void Enemy::increaseResistance(SKCompatibility sk, int32_t v)
{
    setResistance(sk, getResistance(sk) + v);
}

void Enemy::decreaseResitance(SKCompatibility sk, int32_t v)
{
    setResistance(sk, getResistance(sk) - v);
}

void Enemy::addSkill(Skill *sk)
{
    skl_.push_back(sk);
}

void Enemy::doCollision(Player &player)
{
    if(player.getATK() < getDFS())
    {
        DrawPanel::instance().newMsgBox(WordingStore::instance().get(Global::instance().DEFAULT_ALERT_MSGID)->at(0))->show();
        player.goBack();
        return ;
    }

    bool result = true;
    Json::Value bak;
    backup(bak);
    int32_t playerCost = 0;
    int32_t turn = 0;
    while(true)
    {
        ++turn;
        //勇者攻击部分
        if(!wouldMiss(player.getSP(), getSP()))
        {
            int32_t cost = (player.getATK() * player.getATK()) / (player.getATK() + getDFS());
            setHP(getHP() - cost);
            TR_TRACE("Hero beat monster:%s, cost:%d damage!", getName().c_str(), cost);
        }
        if(getHP() == 0)
            break;
        if(!wouldMiss(getSP(), player.getSP()))
        {
            int32_t cost = (getATK() * getATK()) / (getATK() + player.getDFS());
            player.setHP(player.getHP() - cost);
            playerCost += cost;
            TR_TRACE("Monster:%s beat hero,cost:%d damage!", getName().c_str(), cost);
        }
        if(player.getHP() == 0)
        {
            result = false;
            break;
        }
    }
    if(!result)
    {
        player.goBack();
        player.goDie();
        DrawPanel::instance().newMsgBox(
                sen::utils::xsprintf(WordingStore::instance().get(Global::instance().BATTLE_FAIL_FINISH_MSGID)->at(0).c_str(), getName(), getHP(), getMP(), getSP(), getATK(), getDFS())
        )->show();
    }
    else
    {
        player.killBlock();
        DrawPanel::instance().newMsgBox(sen::utils::xsprintf(WordingStore::instance().get(Global::instance().BATTLE_SUCC_FINISH_MSGID)->at(0).c_str(), turn, getName(), playerCost, getCoin(), getExp()))->show();
        player.setCoin(player.getCoin() + getCoin());
        player.setExp(player.getExp() + getExp());
    }
    restore(bak);
}

bool Enemy::construct(const Json::Value &v)
{
    if(v.isMember("hp"))
        setHP(v["hp"].asUInt());
    if(v.isMember("mp"))
        setMP(v["mp"].asUInt());
    if(v.isMember("speed"))
        setSP(v["speed"].asUInt());
    if(v.isMember("atk"))
        setATK(v["atk"].asUInt());
    if(v.isMember("dfs"))
        setDFS(v["dfs"].asUInt());
    return MagicObject::construct(v);
}

Enemy::Enemy(MOType type)
        : MagicObject(type), hp_(1), mp_(1), sp_(1), atk_(1), dfs_(0)
{

}

void Enemy::setHP(int32_t hp)
{
    hp_ = std::max(hp, 0);
}

void Enemy::setMP(int32_t mp)
{
    mp_ = std::max(mp, 0);
}

void Enemy::setSP(int32_t sp)
{
    sp_ = std::max(sp, 0);
}

void Enemy::setATK(int32_t atk)
{
    atk_ = std::max(atk, 0);
}

void Enemy::setDFS(int32_t dfs)
{
    dfs_ = std::max(dfs, 0);
}

int32_t Enemy::getHP() const
{
    return hp_;
}

int32_t Enemy::getMP() const
{
    return mp_;
}

int32_t Enemy::getSP() const
{
    return sp_;
}

int32_t Enemy::getATK() const
{
    return atk_;
}

int32_t Enemy::getDFS() const
{
    return dfs_;
}

uint32_t Enemy::createRnd()
{
    return static_cast<uint32_t>(rand() % 100 + 1);
}

bool Enemy::wouldMiss(int lhs, int rhs)
{
    if(lhs >= rhs)
        return false;
    uint32_t rnd = createRnd();
    return rnd <= rhs - lhs;
}

void Enemy::backup(Json::Value &v)
{
    v["hp"] = getHP();
    v["mp"] = getMP();
    v["speed"] = getSP();
    v["atk"] = getATK();
    v["dfs"] = getDFS();
    MagicObject::backup(v);
}

REGIST_OBJECT(Enemy);