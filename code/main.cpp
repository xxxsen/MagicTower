#include <iostream>
#include "Tower.h"
#include <string>

int main(int argc, char *argv[])
{
    std::string cfg = "./config.json";
    if(argc != 1)
        cfg = argv[1];
    Tower tower;
    tower.init(cfg);
    tower.process();
    return 0;
}