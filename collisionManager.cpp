#include <SDL2/SDL_mixer.h>

#include <vector>

#include <algorithm>

#include <cmath>

#include "CollisionManager.h"

#include "Bullet.h"

#include "Enemy.h"

#include "EliteEnemy.h"

#include "Player.h"

#include "Skill.h"

extern Mix_Chunk * gSelfDamage;
extern Mix_Chunk * gDestroy;

CollisionManager::CollisionManager(int enemycoin, int eliteenemycoin, int eliteenemy2coin, int eliteenemy3coin): enemycoin(2), eliteenemycoin(5), eliteenemy2coin(5), eliteenemy3coin(5) {}
CollisionManager::~CollisionManager() {}

void CollisionManager::checkBulletEnemyCollision(Player & player, std::vector < Enemy > & enemies,
    std::vector < EliteEnemy > & eliteEnemies, std::vector < EliteEnemy2 > & eliteEnemies2, std::vector < EliteEnemy3 > & eliteEnemies3, std::vector < Bullet > & bullets) {
    for (auto & currentBullet: bullets) {
        for (auto & currentEnemy: enemies) {
            if (sqrt(pow((currentEnemy.getX() - (double) currentBullet.getX()), 2) + pow((currentEnemy.getY() - (double) currentBullet.getY()), 2)) <=
                (currentEnemy.getRadius() + currentBullet.getRadius()) && currentBullet.isAlive()) {
                currentEnemy.decreaseHP();
                currentEnemy.setValue(player.getSkill().getFreeze());
                currentBullet.set0health();
                if (!currentEnemy.isAlive()) {
                    Mix_PlayChannel(-1, gDestroy, 0);
                    player.getSkill().add_coins(player.getSkill().getEnemyCoin()); // Use the instance of Skill to call add_coins
                    player.killEnemy();
                }
                break;
            }
        }

        for (auto & currentEliteEnemy: eliteEnemies) {
            if (sqrt(pow((currentEliteEnemy.getX() - (double) currentBullet.getX()), 2) + pow((currentEliteEnemy.getY() - (double) currentBullet.getY()), 2)) <=
                (currentEliteEnemy.getRadius() + currentBullet.getRadius()) && currentBullet.isAlive()) {
                currentEliteEnemy.decreaseHP();
                currentEliteEnemy.setValue(player.getSkill().getFreeze());
                currentBullet.set0health();
                if (!currentEliteEnemy.isAlive()) {
                    Mix_PlayChannel(-1, gDestroy, 0);
                    player.getSkill().add_coins(player.getSkill().getEliteEnemyCoin()); // Use the instance of Skill to call add_coins
                    player.killEnemy();
                }
                break;
            }
        }

        for (auto & currentEliteEnemy2: eliteEnemies2) {
            if (sqrt(pow((currentEliteEnemy2.getX() - (double) currentBullet.getX()), 2) + pow((currentEliteEnemy2.getY() - (double) currentBullet.getY()), 2)) <=
                (currentEliteEnemy2.getRadius() + currentBullet.getRadius()) && currentBullet.isAlive()) {
                currentEliteEnemy2.decreaseHP();
                currentEliteEnemy2.setValue(player.getSkill().getFreeze());
                currentBullet.set0health();
                if (!currentEliteEnemy2.isAlive()) {
                    Mix_PlayChannel(-1, gDestroy, 0);
                    player.getSkill().add_coins(player.getSkill().getEliteEnemy2Coin()); // Use the instance of Skill to call add_coins
                    player.killEnemy();
                }
                break;
            }
        }

        for (auto & currentEliteEnemy3: eliteEnemies3) {
            if (sqrt(pow((currentEliteEnemy3.getX() - (double) currentBullet.getX()), 2) + pow((currentEliteEnemy3.getY() - (double) currentBullet.getY()), 2)) <=
                (currentEliteEnemy3.getRadius() + currentBullet.getRadius()) && currentBullet.isAlive()) {
                currentEliteEnemy3.decreaseHP();
                currentEliteEnemy3.setValue(player.getSkill().getFreeze());
                currentBullet.set0health();
                if (!currentEliteEnemy3.isAlive()) {
                    Mix_PlayChannel(-1, gDestroy, 0);
                    player.getSkill().add_coins(player.getSkill().getEliteEnemy3Coin()); // Use the instance of Skill to call add_coins
                    player.killEnemy();
                }
                break;
            }
        }
    }
}

void CollisionManager::checkPlayerEnemyCollision(Player & player, std::vector < Enemy > & enemies,
    std::vector < EliteEnemy > & eliteEnemies, std::vector < EliteEnemy2 > & eliteEnemies2, std::vector < EliteEnemy3 > & eliteEnemies3) {
    for (auto & currentEnemy: enemies) {
        if (sqrt(pow((currentEnemy.getX() - (double) player.getX()), 2) + pow((currentEnemy.getY() - (double) player.getY()), 2)) <=
            (currentEnemy.getRadius() + player.getRadius())) {
            currentEnemy.setHPto0();
            player.decreaseHP();
            Mix_PlayChannel(-1, gSelfDamage, 0);
            if (player.show_current_HP() == 0) return;
        }
    }

    for (auto & currentEliteEnemy: eliteEnemies) {
        if (sqrt(pow((currentEliteEnemy.getX() - (double) player.getX()), 2) + pow((currentEliteEnemy.getY() - (double) player.getY()), 2)) <=
            (currentEliteEnemy.getRadius() + player.getRadius())) {
            currentEliteEnemy.setHPto0();
            player.decreaseHP(2);
            Mix_PlayChannel(-1, gSelfDamage, 0);
            if (player.show_current_HP() == 0) return;
        	}
        for (auto & currentEliteBullet: currentEliteEnemy.getBullets()) {
            if (sqrt(pow((currentEliteBullet.getX() - (double) player.getX()), 2) + pow((currentEliteBullet.getY() - (double) player.getY()), 2)) <=
                (currentEliteBullet.getRadius() + player.getRadius())) {
                currentEliteBullet.set0health();
                player.decreaseHP();
                Mix_PlayChannel(-1, gSelfDamage, 0);
                if (player.show_current_HP() == 0) return;
            }
        }
    }
    for (auto & currentEliteEnemy2: eliteEnemies2) {
        if (sqrt(pow((currentEliteEnemy2.getX() - (double) player.getX()), 2) + pow((currentEliteEnemy2.getY() - (double) player.getY()), 2)) <=
            (currentEliteEnemy2.getRadius() + player.getRadius())) {
            currentEliteEnemy2.setHPto0();
            player.decreaseHP(2);
            Mix_PlayChannel(-1, gSelfDamage, 0);
            if (player.show_current_HP() == 0) return;
        }
        for (auto & currentEliteBullet2: currentEliteEnemy2.getBullets()) {
            if (sqrt(pow((currentEliteBullet2.getX() - (double) player.getX()), 2) + pow((currentEliteBullet2.getY() - (double) player.getY()), 2)) <=
                (currentEliteBullet2.getRadius() + player.getRadius())) {
                currentEliteBullet2.set0health();
                player.decreaseHP();
                Mix_PlayChannel(-1, gSelfDamage, 0);
                if (player.show_current_HP() == 0) return;
                int newVelocity = player.getVelocity() - 1;
                player.setVelocity(std::max(newVelocity, 1));
            }
        }
	}
    for (auto & currentEliteEnemy3: eliteEnemies3) {
        if (sqrt(pow((currentEliteEnemy3.getX() - (double) player.getX()), 2) + pow((currentEliteEnemy3.getY() - (double) player.getY()), 2)) <=
            (currentEliteEnemy3.getRadius() + player.getRadius())) {
            currentEliteEnemy3.setHPto0();
            player.decreaseHP(2);
            Mix_PlayChannel(-1, gSelfDamage, 0);
            if (player.show_current_HP() == 0) return;
        }

        for (auto & currentEliteBullet3: currentEliteEnemy3.getBullets()) {
            if (sqrt(pow((currentEliteBullet3.getX() - (double) player.getX()), 2) + pow((currentEliteBullet3.getY() - (double) player.getY()), 2)) <=
                (currentEliteBullet3.getRadius() + player.getRadius())) {
                currentEliteBullet3.set0health();
                player.decreaseHP();
                Mix_PlayChannel(-1, gSelfDamage, 0);
                if (player.show_current_HP() == 0) return;
                int newVelocity = player.getVelocity() - 1;
                player.setVelocity(std::max(newVelocity, 1));
            }
        }
    }

}

void CollisionManager::setValue(int plus) {
    enemycoin += plus;
    eliteenemycoin += plus;
    eliteenemy2coin += plus;
    eliteenemy3coin += plus;
}