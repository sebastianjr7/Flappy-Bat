#include "System.h"
#include "Session.h"
#include "Label.h"
#include "Button.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

#define W_INDOW_W 900
#define W_INDOW_H 900

using namespace std;
using namespace myEngine;

Session ses;
int value = 0;
int score = 0;
bool isGameOver;
Label* scoreLbl;
vector<Sprite*> obstacles;

class Bat : public GameObject {
private:
protected:
    Bat(float x, float y, string img) : GameObject (x,y, img) {
        gravity = 0.252;
        lift = -9;
        enablePlayerControl();
    }
public:
    static Bat* getInstance(int x, int  y, string img) {
        return new Bat(x,y,img);
    }

    void update() {
        fall();
        checkBoundaries();
        for (Sprite* s : obstacles) {
            if (checkCollision(s)) {
                isCollided = true;
                isGameOver = true;
            }
        }
    }

    void checkBoundaries() {
        //prevents from going off window, up (if) and down (else if)
        if (getRect().y < 0 - getRect().h/2) {
            setRect().y = 0 - getRect().h/2;
            velocity = 0;
        } else if (getRect().y + getRect().h > W_INDOW_H) {
            setRect().y = W_INDOW_H - getRect().h;
            isCollided = true;
            isGameOver = true;
        }
    }

};

class Pipe : public Sprite {
private:

protected:
    Pipe(float x, float y, string img) : Sprite(x,y,32,32, img){}
public:
    static Pipe* getInstance(int x, int y, string img) {
        return new Pipe(x,y,img);
    }
    void update() {
        if (getRect().x <= 0 - getRect().w) { 
            ses.remove(this);
            setRect().x = W_INDOW_W;
            score++;
            scoreLbl->setText(to_string(score));
        }
        else { 
            setRect().x-=4; 
        }
    }
};


int main(int argc, char** argv) {
    sys.setBG("gcbg.png");
    scoreLbl = Label::getInstance(350,100,100,70,to_string(score));
    ses.add(scoreLbl);
    Sprite* bat = Bat::getInstance(50,W_INDOW_H/2,"bat.png");
    ses.add(bat);
    Sprite* pipeUp1 = Pipe::getInstance(W_INDOW_W,W_INDOW_H-250,"pipeDown.png");
    Sprite* pipeDown1 = Pipe::getInstance(W_INDOW_W*1.33,-100,"pipeUp.png");
    Sprite* pipeUp2 = Pipe::getInstance(W_INDOW_W*1.66,W_INDOW_H-250,"pipeDown.png");
    Sprite* pipeDown2 = Pipe::getInstance(W_INDOW_W*2,-100,"pipeUp.png");

    ses.add(pipeUp1);
    obstacles.push_back(pipeUp1);
    ses.add(pipeDown1);
    obstacles.push_back(pipeDown1);
    ses.add(pipeUp2);
    obstacles.push_back(pipeUp2);
    ses.add(pipeDown2);
    obstacles.push_back(pipeDown2);

    ses.run();
    ses.endGame(score);

    return 0;
}