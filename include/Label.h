#ifndef LABEL_H
#define LABEL_H
#include "Sprite.h"
#include <string>

namespace myEngine {

    class Label : public Sprite {
    private:
        std::string text;
    protected:
        Label(float x, float y, int w, int h, std::string txt);
    public:
        static Label* getInstance(float x, float y, int w, int h, std::string txt);
        std::string getText() const;
        void setText(std::string newText);
        void draw() const;
        void update();
        ~Label();
    };

}
#endif