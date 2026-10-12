#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

namespace myEngine {
    class GameObject : public Sprite {
    private:
    protected:
        bool isJumping = false;
        float velocity = 0;
        float lift;
        float gravity;
        GameObject(float x, float y, std::string img);
    public:
        static GameObject* getInstance(float x, float y, std::string img);
        void update();
        void mouseDown(const SDL_Event& e);
        void mouseUp(const SDL_Event& e);
        void mouseMotion(const SDL_Event& e);
        void keyDown(const SDL_Event& e);
        void keyUp(const SDL_Event& e);
        void jump();
        void fall();
        virtual bool checkCollision(const Sprite* other) const;
        ~GameObject();
    };
    

    
}

#endif