#include "System.h"
#include "Button.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL_image.h>

using namespace std;

namespace myEngine {

    Button* Button::getInstance(float x, float y, int w, int h, std::string txt) {
        return new Button(x,y,w,h,txt);
    };

    Button::Button(float x, float y, int w, int h, std::string txt) 
    : Sprite(x,y,w,h), text(txt)
    {
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), txt.c_str(), {0,0,0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
        upIcon = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/up.png").c_str());
        downIcon = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/down.png").c_str());
    }
    
    void Button::mouseDown(const SDL_Event& event) {
        SDL_FPoint p = {(float)event.button.x, (float)event.button.y};
        if (SDL_PointInFRect(&p,&getRect())) {
            isDown = true;
        }

    }

    void Button::mouseUp(const SDL_Event& event) {
        SDL_FPoint p = {(float)event.button.x, (float)event.button.y};
        if (SDL_PointInFRect(&p,&getRect()))
            perform(this);
        
        isDown = false;
    }

    void Button::draw() const {
        if (isDown) 
            SDL_RenderCopyF(sys.getRen(), downIcon, NULL, &getRect());
        else 
            SDL_RenderCopyF(sys.getRen(), upIcon, NULL, &getRect());
        
        
        SDL_RenderCopyF(sys.getRen(), texture, NULL, &getRect());
    }

    void Button::update() {}
    
    Button::~Button() {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(upIcon);
        SDL_DestroyTexture(downIcon);
    }
}