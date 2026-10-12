#include "GameObject.h"
#include <string>
#include <iostream>

namespace myEngine {
    GameObject::GameObject(float x, float y, std::string img) : Sprite(x,y,100,100,img) {
    }

    GameObject* GameObject::getInstance(float x, float y, std::string img) {
        return new GameObject(x,y,img);
    }

    void GameObject::update() {}

        
    void GameObject::mouseDown(const SDL_Event& event) {
        SDL_FPoint p = {(float)event.button.x, (float)event.button.y};
        if (SDL_PointInFRect(&p, &getRect()))
            drag = true;
    }
    void GameObject::mouseUp(const SDL_Event& event) {
        drag = false;
    }
    void GameObject::mouseMotion(const SDL_Event& event) {
        if (drag) {
            setRect().x += event.motion.xrel;
            setRect().y += event.motion.yrel;
        }
    }
    void GameObject::keyDown (const SDL_Event& event) {
        switch( event.key.keysym.sym ){
                    case SDLK_w: velocity = 0;setRect().y-=20; break;
                    case SDLK_a: velocity = 0;setRect().x-=20; break;
                    case SDLK_s: velocity = 0;setRect().y+=20; break;
                    case SDLK_d: velocity = 0;setRect().x+=20; break;

                    case SDLK_SPACE:
                        isJumping = true;
                        jump();
                        break;
                    default:
                        break;
                }
    }
    void GameObject::keyUp (const SDL_Event& event) {
        switch( event.key.keysym.sym ){
            case SDLK_w: break;
            case SDLK_a: break;
            case SDLK_s: break;
            case SDLK_d: break;

            case SDLK_SPACE: 
                isJumping = false;
                break;
            default:
                break;
        }
    }

    void GameObject::jump() {
        velocity = 0;
        velocity += lift;
    }

    void GameObject::fall() {        
        velocity += gravity; 
        setRect().y+=velocity;
    }

    bool GameObject::checkCollision(const Sprite* other) const {
        if (getRect().x + getRect().w > other->getRect().x &&
            getRect().x < other->getRect().w + other->getRect().x &&
            getRect().y + getRect().h > other->getRect().y &&
            getRect().y < other->getRect().h + other->getRect().y)
        {
            return true;
        }
        return false;
    };


    GameObject::~GameObject() {
    }
}