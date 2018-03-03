//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_NPC_H
#define MAGICTOWER_NPC_H

#include "MagicObject.h"

class NPC : public MagicObject
{
public:
    NPC();

public:
    bool construct(const Json::Value &v) override;

public:
    void doCollision(Player &player) override;

public:
    uint32_t getWording() const;

private:
    uint32_t wording_;
};

class SelectDialogNPC : public NPC
{
public:
    SelectDialogNPC();

public:
    bool construct(const Json::Value &v) override;

    void doCollision(Player &player) override;

public:
    bool hasSelected() const;
    int32_t getSelected() const;
    int32_t getBeforeWording() const;
    int32_t getAfterWording() const;
    bool hasBeforeWording() const;
    bool hasAfterWording() const;

private:
    int32_t selected_;
    int32_t before_;
    int32_t after_;
};


#endif //MAGICTOWER_NPC_H
