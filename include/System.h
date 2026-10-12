#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

#define W_INDOW_W 900
#define W_INDOW_H 900

namespace myEngine{
    class System {
    private:
        SDL_Texture* bgTx;
        SDL_FRect bgRect;
        SDL_Window* win;
        SDL_Renderer* ren;
        TTF_Font* font;
        std::map<std::string, Mix_Chunk*> sounds;

    public:
        System(/* args */);
        ~System();
        SDL_Renderer* getRen() const;
        TTF_Font* getFont() const;
        void addSound(std::string name, std::string file);
        Mix_Chunk* getSound(std::string name) const;
        void setBG(std::string img);
        int getWindowWidth() const { return W_INDOW_W;};
        int getWindowHeight() const { return W_INDOW_H;};
        SDL_Texture* getBgTx() {return bgTx;};
        SDL_FRect& getBgRect() {return bgRect;};
    };
    
    extern System sys;
}

#endif