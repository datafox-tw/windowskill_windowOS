#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "variable.h"
#include "SDL2/SDL.h" 
#include <cstdio>
#include "bullet.h"
#include "enemy.h"
#include "skill.h"
#include <vector>

class Player {
public:
    Player(SDL_Renderer* renderer, int x, int y);
    ~Player();

    void handleEvent(SDL_Event& e);
    void update(Player & player, EnemyManager& enemyManager);
    void render();
    void restart();
    
    int show_total_HP();
    int show_current_HP();
    void decreaseHP();
    void decreaseHP(int);
    
	double getX() const;
	double getY() const;
    void setPlayerPosition(double newX, double newY);
    int getRadius();
    void setValue(int v, Uint32 rate, int MaxHP, int CurrentHP, int mShot, int b);
    void resetMovementFlags();
    void setVelocity(int newVelocity);
    int getVelocity() const;
    
    std::vector<Bullet>& getBullets() {return bullets;}
    Skill& getSkill()	{return skill;}
    
    int getBulletFired();
    int getEnemyKilled();
    int getBossKilled();
    
    void killEnemy();
    void killBoss();
    friend class ShowWindow; 
    
private:
    double x, y;
    int radius;
    int velocity;
    int total_HP = 20;
	int current_HP = 20;
	int slowdownTimer = 0;
	
	int multiShot;
	int bounce;
	
    bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	
	std::vector<Bullet> bullets;
	Skill skill;
	
    SDL_Renderer* renderer;
    int mouseX;
	int mouseY;
	
	Uint32 lastBulletTime;
	Uint32 lastMultiShotTime;
	Uint32 NowTime;
	Uint32 fireRate = 500;
	
	int bulletFired = 0;
	int enemyKilled = 0;
	int bossKilled = 0;
};
#endif
