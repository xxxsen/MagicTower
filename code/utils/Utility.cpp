//
// Created by sen on 18-2-18.
//

#include <fstream>
#include "Utility.h"

class AutoClose
{
public:
    AutoClose(std::ifstream &in) : in_(in) { }
    ~AutoClose() { in_.close(); }

private:
    std::ifstream &in_;
};

bool Utility::loadJson(const std::string &file, Json::Value &v)
{
    std::ifstream in(file, std::ios::binary);
    if(!in.is_open())
        return false;
    AutoClose guard(in);
    (void)guard;
    Json::Reader reader;
    if(!reader.parse(in, v))
        return false;
    return true;
}
