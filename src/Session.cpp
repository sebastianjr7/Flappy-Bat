#include "Session.h"
#include "Sprite.h"
#include "System.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace myEngine {
    void Session::add(Sprite* s) {
        added.push_back(s);
    }

    void Session::remove(Sprite* s) {
        removed.push_back(s);
    }
    
    void Session::run() {
        int volume = 30;
        Mix_PlayChannel(-1, sys.getSound("start"), 0);
        Mix_PlayChannel(-1, sys.getSound("music"), -1);
        bool quit = false;
        while (!quit) {
            nextTick = SDL_GetTicks() + tickInterval;
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: 
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN: 
                        for (Sprite* s: comps) {
                            s->mouseDown(event);
                        };
                        //Mix_PlayChannel(-1, sys.getSound("click"), 0);
                        break;
                    case SDL_MOUSEBUTTONUP: 
                        for (Sprite* s: comps) {
                            s->mouseUp(event);
                        };
                        break;
                    case SDL_MOUSEMOTION: 
                        for (Sprite* s: comps) {
                            if (s->isPlayerDraggable()) {
                                s->mouseMotion(event);
                            }
                        };
                        break;
                    case SDL_KEYDOWN:
                        for (Sprite* s: comps) {
                            if (s->isPlayerControllable()) {
                                s->keyDown(event);
                            }
                            
                        };
                        switch (event.key.keysym.sym) {
                            case SDLK_LEFT: break;
                            case SDLK_RIGHT:  break;
                            case SDLK_UP: 
                                if (volume < 50) { volume+=10; }
                                break;
                            case SDLK_DOWN: 
                                if (volume > 0) { volume-=10; }
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        for (Sprite* c: comps) {
                            c->keyUp(event);
                        };
                        break;
                    default:
                        break;
                } //switch
            } //inner while
            Mix_Volume(-1,volume);
            SDL_SetRenderDrawColor(sys.getRen(), 30,30,30,255);
            SDL_RenderClear(sys.getRen());
            SDL_RenderCopyF(sys.getRen(), sys.getBgTx(), NULL, &sys.getBgRect());

            for (Sprite* s: comps) {
                s->draw();
                s->update();
                if (s->hasCollided()) {
                    quit = true;
                }
                
            }
            for(Sprite* s : added) {
                comps.push_back(s);
            }
            added.clear();

            for(Sprite* s : removed) {
                for (std::vector<Sprite*>:: iterator i = removed.begin(); i != removed.end();) {
                    if (*i == s) {
                        i = removed.erase(i);
                    } else {
                        i++;
                    }
                }
            }
            removed.clear();
            tick++;

            SDL_RenderPresent(sys.getRen());
            
            delay = nextTick - SDL_GetTicks(); //tickInterval
            if (delay > 0) { SDL_Delay(delay); }
        } //outer while
    }

    void Session::endGame(int finalScore) {
        std::string finalScoreStr = "Final Score: " + std::to_string(finalScore);
        SDL_Color finalScoreColor = {0,255,0};
        SDL_Surface* finalScoreSurf = TTF_RenderText_Solid(sys.getFont(), finalScoreStr.c_str(), finalScoreColor);
        SDL_Texture* finalScoreTx = SDL_CreateTextureFromSurface(sys.getRen(), finalScoreSurf);
        SDL_Rect finalScoreRect = {sys.getWindowWidth()/2 - finalScoreSurf->w/2, sys.getWindowHeight()/2 - finalScoreSurf->h/2, finalScoreSurf->w, finalScoreSurf->h};
        SDL_FreeSurface(finalScoreSurf);
        SDL_RenderClear(sys.getRen());
        SDL_RenderCopy(sys.getRen(), finalScoreTx, NULL, &finalScoreRect);
        SDL_RenderPresent(sys.getRen());
        Mix_PlayChannel(-1, sys.getSound("quit"), 0);

        SDL_Delay(5000);
    }

    int Session::getTick() const {
        return (tick*2)/100;
    }

    Session::~Session() {
    }
}