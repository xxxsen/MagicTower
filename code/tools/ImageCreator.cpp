//
// Created by sen on 18-2-17.
//

#include "ImageCreator.h"
#include "Global.h"
#include "Consts.h"
#include "utils/Utility.h"
#include <json/json.h>
#include <fstream>
#include <cassert>
#include <iostream>
#include <utils/TowerLog.h>

ImageCreator::ImageCreator()
{
    int ret = IMG_Init(IMG_INIT_PNG);
    assert(ret != -1);
}

ImageCreator::ImageCreator(const ImageCreator &)
{

}

ImageCreator &ImageCreator::instance()
{
    static ImageCreator pic;
    return pic;
}

bool ImageCreator::init(const Global &bs)
{
    Json::Value v;
    bool result = Utility::loadJson(bs.imgPath, v);
    (void)result;
    assert(result);
    for(Json::Value::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if(!it->isMember("id") || !it->isMember("img") || ! it->isMember("location"))
        {
            TR_ERROR("Load image failed, not found id/img/location! json:%s", it->toStyledString().c_str());
            assert(false);
            return false;
        }
        uint32_t id = (*it)["id"].asUInt();
        std::string cfgImg = (*it)["img"].asString();
        std::string img = bs.basicRoot + "/" + cfgImg;
        std::map<std::string, std::pair<uint32_t, uint32_t>> tmp;
        Json::Value value = (*it)["location"];
        assert(value.isArray() || value.isObject());
        if(value.isArray())
        {
            tmp.insert(std::make_pair("", std::make_pair(value[0].asInt(), value[1].asInt())));
        }
        else
        {
            assert(value.isObject());
            Json::Value::Members members = value.getMemberNames();
            for(Json::Value::Members::const_iterator inner = members.begin(); inner != members.end(); ++inner)
            {
                assert(value[*inner].type() == Json::ValueType::arrayValue);
                tmp.insert(std::make_pair(*inner, std::make_pair(value[*inner][0].asInt(), value[*inner][1].asInt())));
            }
        }
        SDL_Surface *goodImg = NULL;
        if(mapper_.count(cfgImg) != 0)
        {
            goodImg = mapper_[cfgImg];
        }
        else
        {
            SDL_Surface *tmpImg = IMG_Load(img.c_str());
            if(tmpImg == NULL)
            {
                TR_ERROR("Load raw image failed, img:%s, e:%s", img.c_str(), SDL_GetError());
                assert(false);
                return false;
            }
            goodImg = SDL_DisplayFormat(tmpImg);
            if(goodImg == NULL)
            {
                TR_ERROR("Load image info, but get display image failed, img:%s, e:%s", img.c_str(), SDL_GetError());
                assert(false);
                return false;
            }
            SDL_FreeSurface(tmpImg);
            mapper_[cfgImg] = goodImg;
        }
        uint8_t r, g, b;
        SDL_GetRGB(*(uint8_t *)(goodImg->pixels), goodImg->format, &r, &g, &b);
        TR_TRACE("Load img, id:%d, img:%s, RGB:(%d, %d, %d)", id, img.c_str(), r, g, b);
        SDL_SetColorKey(goodImg, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(goodImg->format, r, g, b));
        assert(store_.count(id) == 0);
        PicList &lst = store_[id];
        lst.pic = goodImg;
        for(auto &item : tmp)
        {
            SDL_Rect *rect = new SDL_Rect();
            rect->x = item.second.second * bs.DEFAULT_ICON_WIDTH;
            rect->y = item.second.first * bs.DEFAULT_ICON_HEIGHT;
            rect->w = static_cast<Uint16>(bs.DEFAULT_ICON_WIDTH);
            rect->h = static_cast<Uint16>(bs.DEFAULT_ICON_HEIGHT);
            lst.loc.insert(std::make_pair(item.first, rect));
            TR_NORMAL("Create image, id:%d, img:%s, rect:(%d, %d)", id, cfgImg.c_str(), rect->x, rect->y);
        }

    }
    TR_NORMAL("Image creator init success!");
    return true;
}

bool ImageCreator::create(uint32_t id, PicList *item)
{
    if(store_.count(id) == 0)
    {
        TR_ERROR("Not found image in image store, may not config in pic.json? id:%d", id);
        assert(false);
        return false;
    }
    item = &store_[id];
    return true;
}

bool ImageCreator::create(uint32_t id, const std::string &subkey, PicItem &item)
{
    if(store_.count(id) == 0 || store_.at(id).loc.count(subkey) == 0)
    {
        TR_ERROR("Not found image key in store, id:%d, subkey:%s", id, subkey.c_str());
        assert(false);
        return false;
    }
    item.pic = store_.at(id).pic;
    item.loc = store_.at(id).loc.at(subkey);
    return true;
}

bool ImageCreator::create(const std::string &key, PicItem &item)
{
    auto index = key.find("#");
    if(index == std::string::npos)
    {
        TR_ERROR("Not found key delimiter '#' in key-string:%s", key.c_str());
        assert(false);
        return false;
    }
    uint32_t id = static_cast<uint32_t>(strtoul(key.substr(0, index).c_str(), NULL, 10));
    std::string subkey = key.substr(index + 1);
    return create(id, subkey, item);
}

bool ImageCreator::createAndCopy(const std::string &key, PicItem &item)
{
    bool result = create(key, item);
    if(!result)
    {
        TR_ERROR("Not found key in store, key:%s", key.c_str());
        assert(false);
        return false;
    }
    item.pic = SDL_DisplayFormat(item.pic);
    if(item.pic == NULL)
    {
        TR_ERROR("Copy pic failed, key:%s", key.c_str());
        assert(false);
        return false;
    }
    return true;
}
