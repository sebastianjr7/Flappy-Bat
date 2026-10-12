#ifndef SESSION_H
#define SESSION_H
#include <string>
#include <vector>
#include "Sprite.h"
#include <SDL2/SDL_image.h>

#define FPS 60

namespace myEngine{

    class Session{
    private:
        std::vector<Sprite*> comps;
        std::vector<Sprite*> added;
        std::vector<Sprite*> removed;
        const int tickInterval = 1000 / FPS;
        Uint32 nextTick;
        int tick = 0;
        int delay;
    public:
        void add(Sprite* s);
        void remove(Sprite* s);
        void run();
        void endGame(int score);
        int getTick() const;
        ~Session();
    };


}

#endif