#include <iostream>
#include <map>
#include "System.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

namespace myEngine {

    System::System(/* args */) {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
            cerr << "SDL_Init-fel: " << SDL_GetError() << endl;
            exit(-1);
        }
        win = SDL_CreateWindow("Flappy Bat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_INDOW_W, W_INDOW_H, SDL_WINDOW_SHOWN);
        if (win == nullptr) {
            cerr << "SDL_CreateWindow-Fel: " << SDL_GetError() << endl;
            SDL_Quit();
            exit(-1);
        }
        ren = SDL_CreateRenderer(win, -1, 0);
        if (ren == nullptr) {
            cerr << "SDL_CreateRenderer-Fel: " << SDL_GetError() << endl;
            exit(-1);
        }

        if (TTF_Init() == -1) { 
            cerr << "TTF_Init-fel: " << SDL_GetError() << endl;
            exit(-1);
        }

        font = TTF_OpenFont((constants::gResPath + "fonts/formulaWide.ttf").c_str(), 36);
        //font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 36);

        if (Mix_OpenAudio(
            22050, // Frequency
            AUDIO_S16SYS, // Format
            2, // No of channels
            4096 // Buffer chunck size
            ) != 0) {
            // Initialization failed.
        }

        addSound("start","winStart.ogg");
        addSound("click","laser.ogg");
        addSound("quit", "winShutdown.ogg");
        addSound("music", "music.ogg");

    }

    
    System::~System() {
        TTF_CloseFont(font);
        TTF_Quit();

        for (pair<string, Mix_Chunk*> pair: sounds) {
            Mix_FreeChunk(pair.second);
        }
        Mix_CloseAudio();
        
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
    }

    SDL_Renderer* System::getRen() const {
        return ren;
    }
    
    TTF_Font* System::getFont() const {
        return font;
    }

    void System::addSound(string name, string file) {
        Mix_Chunk* newSound = Mix_LoadWAV((constants::gResPath + "sounds/" + file).c_str());
        if (newSound != NULL) {
            sounds.insert({name, newSound});
        } else {
            cerr << "Mix_LoadWav-fel: " << SDL_GetError() << " ["<< file <<"] " << endl;
        }
    }

    Mix_Chunk* System::getSound(string name) const {
        Mix_Chunk* s = nullptr;
        for (pair<string, Mix_Chunk*> pair: sounds) {
            if (name == pair.first) {
                s = pair.second;
            }
        }
        return s;
    }

    void System::setBG(std::string img) {
        SDL_Surface* bgSurf = IMG_Load((constants::gResPath + "images/" + img).c_str());
        bgRect = {0,0,(float)bgSurf->w, W_INDOW_H};
        bgTx = SDL_CreateTextureFromSurface(sys.getRen(),bgSurf);
        SDL_FreeSurface(bgSurf);
    }
    
    System sys;

}