#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <string>

namespace myEngine {
    
    class Sprite {
    private:
        Sprite(const Sprite&) = delete; //förbjuder kopering
        const Sprite& operator=(const Sprite&) = delete; //förbjuder tilldelning
    protected:
        SDL_Texture* texture;
        SDL_FRect rect;
        bool isCollided = false;
        bool playerControl = false;
        bool isDraggable = false;
        bool drag = false;
        Sprite(float x, float y, float w, float h);
        Sprite(float x, float y, float w, float h, std::string img);
    public:
        ~Sprite();
        virtual void mouseDown(const SDL_Event&) {};
        virtual void mouseUp(const SDL_Event&) {};
        virtual void mouseMotion(const SDL_Event&) {};
        virtual void keyDown(const SDL_Event&) {};
        virtual void keyUp(const SDL_Event&) {};
        virtual void draw() const;
        virtual void update() = 0;
        virtual void enablePlayerControl() { playerControl = true; };
        virtual void enableDragging() { isDraggable = true; };
        virtual bool isPlayerControllable(){ return playerControl; };
        virtual bool isPlayerDraggable(){ return isDraggable; };
        virtual bool hasCollided(){ return isCollided; };
        const SDL_FRect& getRect() const {return rect;};
        SDL_FRect& setRect() {return rect;};
    };
}

#endif