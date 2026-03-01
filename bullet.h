#ifndef BULLET_H
#define BULLET_H
#include "SDL2/SDL.h"

#include "enemy.h"

class Player;

class Bullet {
    public: Bullet(int startX, int startY, int h, int speed, int r); // create bullet
    ~Bullet(); // delete bullet

    void update(); // update the status of the bullet
    void render(SDL_Renderer * renderer) const; // help "render" the bullets

    bool isAlive() const {
        return health;
    } // check the status

    void setDirectionToMouse(int startX, int startY, int mouseX, int mouseY); // check the position from player to mouse
    void set0health() {
        health = 0;
    }
    int getX();
    int getY();
    void setBulletPosition(int newX, int newY);
    int getRadius();

    protected: int x;
    int y;
    int radius;
    int health;
    int bulletSpeed;
    double velocityX;
    double velocityY;
};

#endif // BULLET_H