//
// Created by sen on 18-2-16.
//

#include <ios>
#include <fstream>
#include <json/json.h>
#include <cassert>
#include "Global.h"
#include "utils/Utility.h"

Global::Global()
{

}

Global::Global(const Global &)
{

}

void Global::init(const std::string &file)
{
    Json::Value v;
    bool result = Utility::loadJson(file, v);
    (void)result;
    assert(result);

    basicRoot = v["basic_root"].asString();
    mapPath = basicRoot + "/map/" + "map.json";
    resPath = basicRoot + "/res/" + "res.json";
    fontPath = basicRoot + "/font/" + "font.json";
    imgPath = basicRoot + "/img/" + "pic.json";
    wordingPath = basicRoot + "/wording/" + "wording.json";

    BATTLE_SUCC_FINISH_MSGID = v["battle_finish_msg"]["succ"].asUInt();
    BATTLE_FAIL_FINISH_MSGID = v["battle_finish_msg"]["fail"].asUInt();
    DEFAULT_DIALOG_LOC_X = v["dialog"]["location"]["x"].asUInt();
    DEFAULT_DIALOG_LOC_Y = v["dialog"]["location"]["y"].asUInt();
    DEFAULT_DIALOG_IMGID = v["dialog"]["img"].asString();
    DEFAULT_ICON_WIDTH = v["icon"]["w"].asUInt();
    DEFAULT_ICON_HEIGHT = v["icon"]["h"].asUInt();
    GAME_OVER_MSGID = v["game_over_msg"].asUInt();
    DEFAULT_HERO_ID = v["default_hero_id"].asUInt();
    DEFAULT_ROAD_ID = v["default_road_id"].asUInt();
    DEFAULT_OK_BTN_MSGID = v["default_btn"]["ok"].asString();
    DEFAULT_CANCEL_BTN_MSGID = v["default_btn"]["cancel"].asString();
    DEFAULT_SELECT_DIALOG_IMGID = v["select_dialog"]["img"].asString();
    DEFAULT_SELECT_ITEM_IMGID = v["select_dialog"]["item_img"].asString();
    DEFAULT_SELECT_DIALOG_LOC_X = v["select_dialog"]["location"]["x"].asUInt();
    DEFAULT_SELECT_DIALOG_LOC_Y = v["select_dialog"]["location"]["y"].asUInt();
    DEFAULT_ALERT_MSGID = v["alert_msgid"].asUInt();
    DEFAULT_NO_MONEY_MSGID = v["no_money_msgid"].asUInt();
    if(v.isMember("log_level"))
        DEFAULT_LOG_LEVEL = v["log_level"].asInt();
    else
        DEFAULT_LOG_LEVEL = 0;
    if(v.isMember("log_file"))
        DEFAULT_LOG_FILE = v["log_file"].asString();
}

Global &Global::instance()
{
    static Global gb;
    return gb;
}
