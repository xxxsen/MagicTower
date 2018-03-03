//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_GLOBAL_H
#define MAGICTOWER_GLOBAL_H

#include <string>

class Global
{
private:
    Global();
    Global(const Global &);

public:
    static Global &instance();

public:
    void init(const std::string &file);

public:
    std::string basicRoot;
    std::string mapPath;
    std::string resPath;
    std::string fontPath;
    std::string imgPath;
    std::string wordingPath;


public:
    uint32_t BATTLE_SUCC_FINISH_MSGID;
    uint32_t BATTLE_FAIL_FINISH_MSGID;
    uint32_t DEFAULT_DIALOG_LOC_X;
    uint32_t DEFAULT_DIALOG_LOC_Y;
    std::string DEFAULT_DIALOG_IMGID;
    uint32_t DEFAULT_ICON_WIDTH;
    uint32_t DEFAULT_ICON_HEIGHT;
    uint32_t GAME_OVER_MSGID;
    uint32_t DEFAULT_HERO_ID;
    uint32_t DEFAULT_ROAD_ID;
    std::string DEFAULT_OK_BTN_MSGID;
    std::string DEFAULT_CANCEL_BTN_MSGID;
    std::string DEFAULT_SELECT_DIALOG_IMGID;
    std::string DEFAULT_SELECT_ITEM_IMGID;
    uint32_t DEFAULT_SELECT_DIALOG_LOC_X;
    uint32_t DEFAULT_SELECT_DIALOG_LOC_Y;
    uint32_t DEFAULT_ALERT_MSGID;
    uint32_t DEFAULT_NO_MONEY_MSGID;
    int32_t DEFAULT_LOG_LEVEL;
    std::string DEFAULT_LOG_FILE;

};


#endif //MAGICTOWER_GLOBAL_H
