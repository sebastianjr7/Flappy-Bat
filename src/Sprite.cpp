#include "Sprite.h"
#include "System.h"
#include "Constants.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace myEngine {

    Sprite::Sprite(float x, float y, float w, float h) : rect{x,y,w,h} {
    }

    Sprite::Sprite(float x, float y, float w, float h, std::string img) : rect{x,y,w,h} {
        SDL_Surface* surface = IMG_Load((constants::gResPath + "images/" + img).c_str());
        rect = {x,y,(float)surface->w, (float)surface->h};
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surface);
        SDL_FreeSurface(surface);
    }
    

    void Sprite::draw() const {
        SDL_RenderCopyF(sys.getRen(), texture, NULL, &getRect());
    }

    Sprite::~Sprite() {
        SDL_DestroyTexture(texture);
    }
}