//
// Created by sen on 18-2-19.
//

#ifndef MAGICTOWER_NPCS_H
#define MAGICTOWER_NPCS_H


#include "NPC.h"

class BusinessNPC : public SelectDialogNPC
{
public:
    BusinessNPC();

public:
    void doCollision(Player &player) override;

};

class Shop : public SelectDialogNPC
{
public:
    Shop();

public:
    void doCollision(Player &player) override;
};


#endif //MAGICTOWER_NPCS_H
