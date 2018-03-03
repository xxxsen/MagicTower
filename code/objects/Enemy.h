//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_ENEMY_H
#define MAGICTOWER_ENEMY_H

#include "NPC.h"
#include "Skill.h"
#include "MagicObject.h"
#include "tools/WordingStore.h"
#include <vector>

class Enemy : public MagicObject
{
public:
    Enemy();
    explicit Enemy(MOType type);

public:
    int32_t getHP() const;
    int32_t getMP() const;
    int32_t getSP() const;
    int32_t getATK() const;
    int32_t getDFS() const;
    void setHP(int32_t hp);
    void setMP(int32_t mp);
    void setSP(int32_t sp);
    void setATK(int32_t atk);
    void setDFS(int32_t dfs);

public:
    void doCollision(Player &player);
    bool construct(const Json::Value &v) override;
    void backup(Json::Value &v) override;

private:
    int32_t hp_;
    int32_t mp_;
    int32_t sp_;
    int32_t atk_;
    int32_t dfs_;

protected:
    bool wouldMiss(int lhs, int rhs);

public:
    void setResistance(SKCompatibility sk, int32_t v);
    int32_t getResistance(SKCompatibility sk);
    void increaseResistance(SKCompatibility sk, int32_t v);
    void decreaseResitance(SKCompatibility sk, int32_t v);
    void addSkill(Skill *sk);


protected:
    uint32_t createRnd();

private:
    typedef std::vector<Skill *> SkillList;
    SkillList skl_;
    typedef std::map<SKCompatibility, int32_t> SkResistance;
    SkResistance resistance_;
};



#endif //MAGICTOWER_ENEMY_H
