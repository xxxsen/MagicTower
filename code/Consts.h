//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_CONSTS_H
#define MAGICTOWER_CONSTS_H

class TowerPoint
{
public:
    TowerPoint(int, int);
    TowerPoint();

public:
    int x;
    int y;
};

enum TowerDirection { DC_UP, DC_DOWN, DC_LEFT, DC_RIGHT };
enum MOType { MO_PLAYER = 10,
    MO_NPC = 20, MO_BUILDING = 30,
    MO_ENEMY = 40, MO_SKILL = 50,
    MO_STAIR = 60, MO_POTION = 70,
    MO_GEM = 80, MO_EQUIP = 90, MO_PLANT, MO_KEY };
enum SKCompatibility { SP_KING, SP_WOOD, SP_WATER, SP_FIRE, SP_DIRT, SP_LIGHT, SP_DARK };
enum StairType { ST_UP = 0, ST_DOWN = 1 };
enum BlockGround { BG_BACK, BG_FRONT };
enum KeyType { KEY_RED, KEY_BLUE, KEY_YELLOW };
enum TRLOG_LEVEL { TR_LV_TRACE, TR_LV_DEBUG, TR_LV_NORMAL, TR_LV_ERROR, TR_LV_FATAL };


#endif //MAGICTOWER_CONSTS_H
