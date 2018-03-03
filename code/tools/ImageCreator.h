//
// Created by sen on 18-2-17.
//

#ifndef MAGICTOWER_PICCREATOR_H
#define MAGICTOWER_PICCREATOR_H

#include <SDL/SDL_image.h>
#include <utility>
#include <string>
#include <map>
#include <vector>
#include "Global.h"

class PicList
{
public:
    SDL_Surface *pic;
    std::map<std::string, SDL_Rect *> loc;
};

class PicItem
{
public:
    SDL_Surface *pic;
    SDL_Rect *loc;
};

class ImageCreator
{
private:
    ImageCreator();
    ImageCreator(const ImageCreator &);

public:
    static ImageCreator &instance();

public:
    bool init(const Global &bs);
    bool create(uint32_t id, PicList *item);
    bool create(uint32_t id, const std::string &subkey, PicItem &item);
    bool create(const std::string &key, PicItem &item);
    bool createAndCopy(const std::string &key, PicItem &item);

private:
    typedef std::map<uint32_t, PicList> PicStore;
    typedef std::map<std::string, SDL_Surface *> PicMapper;
    PicStore store_;
    PicMapper mapper_;
};


#endif //MAGICTOWER_PICCREATOR_H
