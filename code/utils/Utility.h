//
// Created by sen on 18-2-18.
//

#ifndef MAGICTOWER_UTILITY_H
#define MAGICTOWER_UTILITY_H

#include <json/json.h>

class Utility
{
public:
    static bool loadJson(const std::string &file, Json::Value &v);
};

#endif //MAGICTOWER_UTILITY_H
