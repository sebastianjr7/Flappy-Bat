#include "System.h"
#include "Label.h"
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

namespace myEngine {

    Label* Label::getInstance(float x, float y, int w, int h, std::string txt) {
        return new Label(x,y,w,h,txt);
    };

    Label::Label(float x, float y, int w, int h, std::string txt) 
    : Sprite(x,y,w,h), text(txt)
    {
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {255,255,255});
        rect = {x,y,(float)surf->w*2,(float)surf->h*2};
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    string Label::getText() const {
        return text;
    }

    void Label::setText(string newText){
        text = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {255,255,255});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
    
    void Label::draw() const {
        SDL_RenderCopyF(sys.getRen(), texture, NULL, &getRect());
    }

    void Label::update(){}

    Label::~Label() {
        SDL_DestroyTexture(texture);
    }
}