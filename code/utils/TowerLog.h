//
// Created by sen on 18-3-2.
//

#ifndef MAGICTOWER_TOWERLOG_H
#define MAGICTOWER_TOWERLOG_H

#include "Consts.h"
#include <string>
#include "XPrintf.h"

#ifdef __WIN32
#define __TOWER_PATH_SEP_CHAR__ '\\'
#else
#define __TOWER_PATH_SEP_CHAR__ '/'
#endif

#define TR_LOG(lv, fmt, ...) do {\
    if(lv >= TowerLog::instance().getLevel()) {\
        char __tmpbuf[8192]; \
        uint32_t __tmpbuflen = snprintf(__tmpbuf, sizeof(__tmpbuf), "[%s][%s][%s:%d][%s] " fmt "\n", TowerLog::getTime().c_str(), strrchr(__FILE__, __TOWER_PATH_SEP_CHAR__) + 1, __FUNCTION__, __LINE__,  TowerLog::lvToStr(lv), ##__VA_ARGS__); \
        TowerLog::instance().write(__tmpbuf, __tmpbuflen); \
    }\
} while(false)
#define TR_TRACE(fmt, ...) TR_LOG(TR_LV_TRACE, fmt, ##__VA_ARGS__)
#define TR_DEBUG(fmt, ...) TR_LOG(TR_LV_DEBUG, fmt, ##__VA_ARGS__)
#define TR_NORMAL(fmt, ...) TR_LOG(TR_LV_NORMAL, fmt, ##__VA_ARGS__)
#define TR_ERROR(fmt, ...) TR_LOG(TR_LV_ERROR, fmt, ##__VA_ARGS__)
#define TR_FATAL(fmt, ...) TR_LOG(TR_LV_FATAL, fmt, ##__VA_ARGS__)

class TowerLog
{
private:
    TowerLog();
    TowerLog(const TowerLog &);

public:
    ~TowerLog();

public:
    static TowerLog &instance();
    TRLOG_LEVEL getLevel() const;
    bool init(TRLOG_LEVEL lv, const std::string &file);
    void destroy();
    void write(const char *buf, uint32_t len);

public:
    static const char *lvToStr(TRLOG_LEVEL lv);
    static std::string getTime();

private:
    TRLOG_LEVEL lv_;
    FILE *p_;
    bool isConsole_;
};


#endif //MAGICTOWER_TOWERLOG_H
