#ifndef ENEMY_H
#define ENEMY_H
#include "SDL.h" 
#include <vector>

class Player;
class EliteEnemy;
class EliteEnemy2;
class EliteEnemy3;
class Enemy {
public:
    Enemy(SDL_Renderer* renderer, int health, int speed, int radius);
    virtual ~Enemy();
    void update();
    void update(const Player& player);
    void render(int r, int g, int b);
    bool isAlive() const;
    double getX();
    double getY();
    int getRadius();
    void set_enemy_position(double newX, double newY);
	void decreaseHP();
	void setHPto0();
	void setValue(double f);
	
protected:
    SDL_Renderer* renderer;
    double x;
    double y;
    int health;
    int radius;
    float speed;
    double freeze;
    Uint32 freezeTime;
};

class EnemyManager {
public:
    EnemyManager(SDL_Renderer* renderer);
    ~EnemyManager();
    void restart();
	void update();
    void update(const Player& player);
    void render();
    void shift_enemy_position(int newX, int newY);
	std::vector<Enemy>& getEnemies() {return enemies;}
	std::vector<EliteEnemy>& getEliteEnemies()	{return eliteEnemies;}
	std::vector<EliteEnemy2>& getEliteEnemies2()	{return eliteEnemies2;}
	std::vector<EliteEnemy3>& getEliteEnemies3()	{return eliteEnemies3;}
	
	Uint32 getLastEnemyRespawnTime()const {return lastEnemyRespawnTime;}
    Uint32 getEnemyRespawnInterval()const {return EnemyRespawnInterval;}
private:
    SDL_Renderer* renderer;
    std::vector<Enemy> enemies;
    std::vector<EliteEnemy> eliteEnemies;
    std::vector<EliteEnemy2> eliteEnemies2;
    std::vector<EliteEnemy3> eliteEnemies3;
    Uint32 lastEnemyRespawnTime = 0;
    Uint32 lastUpdateTime = 0;
    Uint32 EnemyRespawnInterval = 5000;
    Uint32 lastEliteEnemyRespawnTime = 0;
    Uint32 EliteEnemyRespawnInterval = 10000;
    Uint32 lastEliteEnemy2RespawnTime = 0;
    Uint32 EliteEnemy2RespawnInterval = 22000;
    Uint32 lastEliteEnemy3RespawnTime = 0;
    Uint32 EliteEnemy3RespawnInterval = 40000;
};

#endif //ENEMY_H
