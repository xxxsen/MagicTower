//
// Created by sen on 18-3-2.
//

#include "TowerLog.h"

TowerLog::TowerLog()
    : lv_(TR_LV_TRACE), p_(NULL), isConsole_(false)
{

}

TowerLog::TowerLog(const TowerLog &)
{

}

TowerLog::~TowerLog()
{
    destroy();
}

TowerLog &TowerLog::instance()
{
    static TowerLog tl;
    return tl;
}

TRLOG_LEVEL TowerLog::getLevel() const
{
    return lv_;
}

bool TowerLog::init(TRLOG_LEVEL lv, const std::string &file)
{
    destroy();
    lv_ = lv;
    if(file.empty())
    {
        p_ = stdout;
        isConsole_ = true;
    }
    else
    {
        p_ = fopen(file.c_str(), "wb");
    }
    return false;
}

void TowerLog::destroy()
{
    if(p_)
    {
        if(!isConsole_)
        {
            fclose(p_);
        }
        isConsole_ = false;
        p_ = NULL;
    }
}

const char *TowerLog::lvToStr(TRLOG_LEVEL lv)
{
    static const char *LV_STR[] = {"LOG_TRACE", "LOG_DEBUG", "LOG_NORMAL", "LOG_ERROR", "LOG_FATAL"};
    int32_t index = lv;
    if(index > TR_LV_FATAL)
        index = TR_LV_FATAL;
    if(index < TR_LV_TRACE)
        index = TR_LV_TRACE;
    return LV_STR[index];
}

void TowerLog::write(const char *buf, uint32_t len)
{
    if(p_)
    {
        fwrite(buf, len, 1, p_);
        fflush(p_);
    }
    else
        fwrite(buf, len, 1, stdout);
}

std::string TowerLog::getTime()
{
    time_t t = time(NULL);
    char tmpBuf[64];
    size_t len = strftime(tmpBuf, sizeof(tmpBuf) - 2, "%Y-%m-%d %H:%M:%S", localtime(&t));
    tmpBuf[len] = 0;
    return std::string(tmpBuf);
}
