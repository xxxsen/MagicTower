//
// Created by sen on 18-2-17.
//

#ifndef MAGICTOWER_WORDINGCREATOR_H
#define MAGICTOWER_WORDINGCREATOR_H

#include <SDL/SDL_ttf.h>
#include "Global.h"
#include <memory>
#include <vector>
#include <json/json.h>

typedef std::shared_ptr<SDL_Surface> SDL_SurfacePtr;

class WordingCreator
{
    static SDL_Color defaultColor_;

private:
    WordingCreator();
    ~WordingCreator();

public:
    bool init(const Global &bs);
    static WordingCreator &instance();

public:
    SDL_SurfacePtr createWording(const std::string &wording, SDL_Color color = defaultColor_);
    SDL_SurfacePtr createWording(SDL_Surface *bg, const std::string &wording, int x = 0, int y = 0, bool autoRelease = false, SDL_Color color = defaultColor_);
    SDL_SurfacePtr createWording(const std::vector<std::string> &wording, SDL_Color color = defaultColor_);
    SDL_SurfacePtr createWording(SDL_Surface *bg, const std::vector<std::string> &wording, int x = 0, int y = 0, bool autoRelease = false, SDL_Color color = defaultColor_);

private:
    TTF_Font *font_;
    uint32_t wordSize_;
};


#endif //MAGICTOWER_WORDINGCREATOR_H
