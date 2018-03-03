//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_FLOOR_H
#define MAGICTOWER_FLOOR_H

#include "objects/MagicObject.h"

class Block
{
public:
    void setFrontground(const MagicObjectPtr &obj);
    void setBackground(const MagicObjectPtr &obj);
    void clear();
    void clearFrontground();
    void clearBackground();
    bool hasFrontground() const;
    bool hasBackground() const;
    const MagicObjectPtr &getFrontground() const;
    const MagicObjectPtr &getBackground() const;

private:
    MagicObjectPtr back_;
    MagicObjectPtr front_;
};

class SearchItem
{
public:
    SearchItem();
    SearchItem(const MagicObjectPtr &item, int x, int y);

public:
    MagicObjectPtr item;
    int x;
    int y;
};

typedef std::vector<SearchItem> SearchResult;

class Floor
{
    typedef std::vector<Block> RoadLine;
    typedef std::vector<RoadLine> RoadGrid;
    const static int MAX_LINE_LENGTH = 15;

public:
    Floor();

public:
    RoadGrid &raw();
    void search(std::vector<SearchItem> &result, MOType type, BlockGround bg);
    TowerPoint locateUpStairPoint(uint32_t floor);
    TowerPoint locateDownStairPoint(uint32_t floor);

    const Block &indexAt(int x, int y);
    const void set(int x, int y, const MagicObjectPtr &front, const MagicObjectPtr &back);
    const void set(int x, int y, const MagicObjectPtr &back);

public:
    void setUpIndex(const TowerPoint &tp);
    void setDownIndex(const TowerPoint &tp);
    const TowerPoint &getUpIndex() const;
    const TowerPoint &getDownIndex() const;

private:
    RoadGrid grid_;
    TowerPoint up_;
    TowerPoint down_;
};


#endif //MAGICTOWER_FLOOR_H
