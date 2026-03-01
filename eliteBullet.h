// ELITEBULLET.H

#ifndef ELITEBULLET_H
#define ELITEBULLET_H

#include "SDL2/SDL.h"

#include "enemy.h"

#include "player.h"

#include "bullet.h"

class Player;

class EliteBullet: public Bullet {
    public: EliteBullet(int startX, int startY);
    ~EliteBullet();

    void update();
    void render(SDL_Renderer * renderer) const;

};

class EliteBullet2: public Bullet {
    public: EliteBullet2(int startX, int startY);
    ~EliteBullet2();

    void update();
    void render(SDL_Renderer * renderer) const;
};

class EliteBullet3: public Bullet {
    public: EliteBullet3(int startX, int startY);
    ~EliteBullet3();

    void update();
    void render(SDL_Renderer * renderer) const;
};

#endif // ELITEBULLET_H