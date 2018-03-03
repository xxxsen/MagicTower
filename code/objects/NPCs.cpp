//
// Created by sen on 18-2-19.
//

#include <iostream>
#include <utils/TowerLog.h>
#include "NPCs.h"
#include "Player.h"
#include "DrawPanel.h"
#include "Dialog.h"

BusinessNPC::BusinessNPC()
{

}

void BusinessNPC::doCollision(Player &player)
{
    SelectDialogNPC::doCollision(player);
    if(hasSelected())
    {
        TR_DEBUG("Hero select item index:%d", getSelected());
        switch(getSelected())
        {
            case 0:
                player.setRedKey(player.getRedKey() + 1);
                break;
            case 1:
                player.setYellowKey(player.getYellowKey() + 1);
                break;
            case 2:
                player.setBlueKey(player.getBlueKey() + 1);
        }
    }
}

REGIST_OBJECT(BusinessNPC);

Shop::Shop()
{

}

void Shop::doCollision(Player &player)
{
    bool wouldBreak = false;
    while(true)
    {
        SelectDialogNPC::doCollision(player);
        if(!hasSelected())
            break;
        switch(getSelected())
        {
            case 0:
                if(player.getCoin() < 3)
                    wouldBreak = true;
                else
                {
                    player.setCoin(player.getCoin() - 3);
                    player.setATK(player.getATK() + 10);
                }
                break;
            case 1:
                if(player.getCoin() < 3)
                    wouldBreak = true;
                else
                {
                    player.setCoin(player.getCoin() - 3);
                    player.setDFS(player.getDFS() + 10);
                }
                break;
            case 2:
                if(player.getCoin() < 3)
                    wouldBreak = true;
                else
                {
                    player.setCoin(player.getCoin() - 3);
                    player.setHP(player.getHP() + 500);
                }
                break;
            case 3:
                if(player.getCoin() < 20)
                    wouldBreak = true;
                else
                {
                    player.setCoin(player.getCoin() - 20);
                    player.setSP(player.getSP() + 1);
                }
                break;
        }
        if(wouldBreak)
            break;
        player.refresh();
    }
    if(wouldBreak)
    {
        DrawPanel::instance().newMsgBox(WordingStore::instance().get(Global::instance().DEFAULT_NO_MONEY_MSGID)->at(0))->show();
    }
}

REGIST_OBJECT(Shop);