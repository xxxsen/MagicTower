include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objects)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_executable(MagicTower main.cpp tools/MagicFactory.cpp
        objects/MagicObject.cpp FloorLoader.cpp FloorLoader.h Global.cpp
        Tower.cpp objects/Player.cpp objects/Enemy.cpp
        objects/Building.cpp objects/NPC.cpp objects/Skill.cpp
        Floor.cpp objects/Stair.cpp objects/Potion.cpp
        objects/Gems.cpp objects/Equip.cpp Consts.cpp objects/Buildings.cpp
        objects/Plant.cpp tools/WordingCreator.cpp objects/Key.cpp
        tools/ImageCreator.cpp Dialog.cpp DrawPanel.cpp
        tools/WordingStore.cpp utils/Utility.cpp utils/XPrintf.cpp objects/NPCs.cpp utils/TowerLog.cpp utils/TowerLog.h)

target_link_libraries(MagicTower SDL_image SDL_ttf SDL jsoncpp)
