#ifndef BUTTON_H
#define BUTTON_H
#include "Sprite.h"
#include <string>

namespace myEngine {

    class Button : public Sprite{
    private:
        std::string text;
        SDL_Texture* upIcon, *downIcon;
        bool isDown = false;
    protected:
        Button(float x, float y, int w, int h, std::string txt);
    public:
        static Button* getInstance(float x, float y, int w, int h, std::string txt);
        void mouseDown(const SDL_Event&);
        void mouseUp(const SDL_Event&);
        virtual void perform(Button* source) {};
        void update();
        void draw() const;
        ~Button();
    };
    
}

#endif