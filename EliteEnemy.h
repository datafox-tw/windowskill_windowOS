#ifndef ELITEENEMY_H
#define ELITEENEMY_H

#include "Enemy.h"

#include "variable.h"

#include "eliteBullet.h"

#include "SDL.h"

#include <vector>


class EliteEnemy: public Enemy {
    public: EliteEnemy(SDL_Renderer * renderer, int speed);
    ~EliteEnemy();
    // Add any additional functions or members specific to Boss if needed

    void update(const Player & player);
    void render(int r, int g, int b);

    std::vector < EliteBullet > & getBullets() {
        return eliteBullets;
    }

    private: Uint32 lastBulletTime;
    Uint32 NowTime;
    int speed;
    Uint32 fireRate;
    Uint32 lastFireRateDecreaseTime;
    std::vector < EliteBullet > eliteBullets;
};

class EliteEnemy2: public Enemy {
    public: EliteEnemy2(SDL_Renderer * renderer);
    ~EliteEnemy2();

    void update(const Player & player);
    void render(int r, int g, int b);

    std::vector < EliteBullet2 > & getBullets() {
        return eliteBullets2;
    }

    private: Uint32 lastBulletTime;
    Uint32 NowTime;
    Uint32 fireRate;
    Uint32 lastFireRateDecreaseTime;
    Uint32 gameStartTime;
    std::vector < EliteBullet2 > eliteBullets2;
};

class EliteEnemy3: public Enemy {
    public: EliteEnemy3(SDL_Renderer * renderer, int speed);
    ~EliteEnemy3();

    void update(const Player & player);
    void render(int r, int g, int b);
    std::vector < EliteBullet3 > & getBullets() {
        return eliteBullets3;
    }
    private: Uint32 gameStartTime;
    Uint32 lastBulletTime;
    Uint32 NowTime;
    int speed;
    Uint32 fireRate;
    Uint32 lastFireRateDecreaseTime;
    std::vector < EliteBullet3 > eliteBullets3;

};

#endif // BOSS_H