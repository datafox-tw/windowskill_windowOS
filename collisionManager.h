#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Bullet.h"

#include "Enemy.h"

#include "EliteEnemy.h"

#include "Player.h"

#include <vector>

#include "Skill.h"

class CollisionManager {
    public: CollisionManager(int enemycoin, int eliteenemycoin, int eliteenemy2coin, int eliteenemy3coin);
    ~CollisionManager();
    void checkBulletEnemyCollision(Player & player, std::vector < Enemy > & enemies,
        std::vector < EliteEnemy > & eliteEnemies, std::vector < EliteEnemy2 > & eliteEnemies2, std::vector < EliteEnemy3 > & eliteEnemies3, std::vector < Bullet > & bullets); // 
    void checkPlayerEnemyCollision(Player & player, std::vector < Enemy > & enemies,
        std::vector < EliteEnemy > & eliteEnemies, std::vector < EliteEnemy2 > & eliteEnemies2, std::vector < EliteEnemy3 > & eliteEnemies3);
    void setValue(int);

    private: int enemycoin;
    int eliteenemycoin;
    int eliteenemy2coin;
    int eliteenemy3coin;
};
#endif // COLLISIONMANAGER_H