//
// Created by sen on 18-2-16.
//

#include "Floor.h"
#include "objects/Stair.h"
#include <cassert>

void Block::setFrontground(const MagicObjectPtr &obj)
{
    front_ = obj;
}

void Block::setBackground(const MagicObjectPtr &obj)
{
    back_ = obj;
}

void Block::clear()
{
    clearFrontground();
    clearBackground();
}

void Block::clearFrontground()
{
    front_.reset();
}

void Block::clearBackground()
{
    back_.reset();
}

const MagicObjectPtr &Block::getFrontground() const
{
    return front_;
}

const MagicObjectPtr &Block::getBackground() const
{
    return back_;
}

bool Block::hasFrontground() const
{
    return front_ ? true : false;
}

bool Block::hasBackground() const
{
    return back_ ? true : false;
}

Floor::Floor()
{
    grid_.resize(MAX_LINE_LENGTH);
    for(int i = 0; i < MAX_LINE_LENGTH; ++i)
    {
        grid_[i].resize(MAX_LINE_LENGTH);
    }
}

Floor::RoadGrid &Floor::raw()
{
    return grid_;
}

const Block &Floor::indexAt(int x, int y)
{
    assert(x < grid_.size());
    assert(y < grid_.size());
    return grid_[y][x];
}

const void Floor::set(int x, int y, const MagicObjectPtr &front, const MagicObjectPtr &back)
{
    grid_[y][x].setFrontground(front);
    grid_[y][x].setBackground(back);
}

const void Floor::set(int x, int y, const MagicObjectPtr &back)
{
    grid_[y][x].setBackground(back);
}

void Floor::search(std::vector<SearchItem> &result, MOType type, BlockGround bg)
{
    for(int y = 0; y < grid_.size(); ++y)
    {
        for(int x = 0; x < grid_[0].size(); ++x)
        {
            if(bg == BG_FRONT)
            {
                if(grid_[y][x].hasFrontground())
                {
                    if(grid_[y][x].getFrontground()->getMagicObjectType() == type)
                    {
                        result.emplace_back(SearchItem(grid_[y][x].getFrontground(), x, y));
                    }
                }
            }
            else if(bg == BG_BACK)
            {
                if(grid_[y][x].hasBackground())
                {
                    if(grid_[y][x].getBackground()->getMagicObjectType() == type)
                    {
                        result.emplace_back(SearchItem(grid_[y][x].getBackground(), x, y));
                    }
                }
            }
        }
    }
}

SearchItem::SearchItem()
{

}

SearchItem::SearchItem(const MagicObjectPtr &item, int x, int y)
{
    this->item = item;
    this->x = x;
    this->y = y;
}

TowerPoint Floor::locateUpStairPoint(uint32_t floor)
{
    return up_;
}

TowerPoint Floor::locateDownStairPoint(uint32_t floor)
{
    return down_;
}

void Floor::setUpIndex(const TowerPoint &tp)
{
    up_ = tp;
}

void Floor::setDownIndex(const TowerPoint &tp)
{
    down_ = tp;
}

const TowerPoint &Floor::getUpIndex() const
{
    return up_;
}

const TowerPoint &Floor::getDownIndex() const
{
    return down_;
}
