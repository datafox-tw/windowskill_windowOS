#include "Enemy.h"

#include <cstdlib>

#include <ctime>

#include <cmath>

#include <algorithm>

#include "player.h"

#include "window.h"

#include "variable.h"

#include "EliteEnemy.h"

#include "timer.h"


extern Window gameWindow;
extern LTimer timer;
extern SDL_Renderer * mRenderer;

Enemy::Enemy(SDL_Renderer * renderer, int health, int speed, int radius): renderer(renderer), health(health), speed(speed), radius(radius), freeze(1), freezeTime(-3000) {
    do {
        x = rand() % (2 * SCREEN_WIDTH) - 0.5 * SCREEN_WIDTH;
        y = rand() % (2 * SCREEN_HEIGHT) - 0.5 * SCREEN_HEIGHT;
    } while (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= SCREEN_HEIGHT);
}

Enemy::~Enemy() {}

void Enemy::update(const Player & player) {
    if (player.getX() != x || player.getY() != y) {
        // Calculate the direction vector to the player
        double angle = atan2(player.getY() - y, player.getX() - x);

        Uint32 t = timer.getTicks();
        if (freeze < 1 && t - freezeTime >= 3000) freeze = 1;
        double velocityX = static_cast < double > (cos(angle) * speed * freeze);
        double velocityY = static_cast < double > (sin(angle) * speed * freeze);

        // Update enemy position
        x += velocityX;
        y += velocityY;
    }
}

void Enemy::render(int r, int g, int b) {
    if (freeze == 1) SDL_SetRenderDrawColor(renderer, 0, r, g, b);
    else SDL_SetRenderDrawColor(renderer, 0, 176, 224, 230);
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
        a = static_cast < int > (x + (radius - 1) * std::cos(angle));
        b = static_cast < int > (y + (radius - 1) * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
}

bool Enemy::isAlive() const {
    return health > 0;
}

double Enemy::getX() {
    return x;
}

double Enemy::getY() {
    return y;
}

int Enemy::getRadius() {
    return radius;
}

void Enemy::decreaseHP() {
    health--;
}

void Enemy::setHPto0() {
    health = 0;
}

void Enemy::set_enemy_position(double newX, double newY) {
    x = newX;
    y = newY;
}

void Enemy::setValue(double f) {
    freeze = f;
    freezeTime = timer.getTicks();
}

// EnemyManager class implementation
EnemyManager::EnemyManager(SDL_Renderer * renderer): renderer(renderer) {
    enemies.emplace_back(renderer, 2, 2, 15); // Initial enemy creation
}

EnemyManager::~EnemyManager() {}

void EnemyManager::update(const Player & player) {
    // Check if it's time to spawn a new enemy
    Uint32 currentTime = timer.getTicks();
    if (currentTime - lastEnemyRespawnTime >= EnemyRespawnInterval) {
        Enemy newEnemy(renderer, 2, 2, 15);
        enemies.push_back(newEnemy); // Create a new enemy and add it to the vector
        lastEnemyRespawnTime = timer.getTicks(); // Update last respawn time
    }

    if (currentTime - lastEliteEnemyRespawnTime >= EliteEnemyRespawnInterval) {
        EliteEnemy newEliteEnemy(renderer, 1);
        eliteEnemies.push_back(newEliteEnemy); // Create a new enemy and add it to the vector
        lastEliteEnemyRespawnTime = timer.getTicks(); // Update last respawn time
    }

    if (currentTime - lastEliteEnemy2RespawnTime >= EliteEnemy2RespawnInterval) {
        EliteEnemy2 newEliteEnemy2(renderer);
        eliteEnemies2.push_back(newEliteEnemy2); // Create a new enemy and add it to the vector
        lastEliteEnemy2RespawnTime = timer.getTicks(); // Update last respawn time
    }

    if (currentTime - lastEliteEnemy3RespawnTime >= EliteEnemy3RespawnInterval) {
        EliteEnemy3 newEliteEnemy3(renderer, 6);
        eliteEnemies3.push_back(newEliteEnemy3); // Create a new enemy and add it to the vector
        lastEliteEnemy3RespawnTime = timer.getTicks(); // Update last respawn time
    }

    if (currentTime >= 0 && currentTime < 30000) {
        EnemyRespawnInterval = 5000;
        EliteEnemyRespawnInterval = 15000;

    }
    if (currentTime >= 30000 && currentTime < 60000) {
        EnemyRespawnInterval = 4000;
        EliteEnemyRespawnInterval = 10000;

    }
    if (currentTime >= 60000 && currentTime < 120000) {
        EnemyRespawnInterval = 4000;
        EliteEnemyRespawnInterval = 10000;
        EliteEnemy2RespawnInterval = 15000;
        EliteEnemy3RespawnInterval = 30000;

    }

    if (currentTime >= 120000 && currentTime < 180000) {
        EliteEnemyRespawnInterval = 8000;
        EliteEnemy2RespawnInterval = 12000;
        EliteEnemy3RespawnInterval = 20000;
    }

    if (currentTime >= 90000 && currentTime < 180000) {
        EnemyRespawnInterval = 3000;
    }

    if (currentTime >= 180001 && currentTime < 240000) {
        EliteEnemyRespawnInterval = 6000;
        EliteEnemy2RespawnInterval = 10000;
        EliteEnemy3RespawnInterval = 15000;
    }

    if (currentTime >= 180001) {
        EnemyRespawnInterval = 2000;
    }

    if (currentTime >= 240001) {
        EliteEnemyRespawnInterval = 4000;
        EliteEnemy2RespawnInterval = 70000;
        EliteEnemy3RespawnInterval = 10000;
    }

    // Update all enemies
    for (auto & enemy: enemies) {
        if (enemy.isAlive()) enemy.update(player);
    }

    for (auto & eliteEnemy: eliteEnemies) {
        if (eliteEnemy.isAlive()) eliteEnemy.update(player);
    }

    for (auto & eliteEnemy: eliteEnemies) {
        if (eliteEnemy.isAlive()) eliteEnemy.update(player);
    }

    for (auto & eliteEnemy2: eliteEnemies2) {
        if (eliteEnemy2.isAlive()) eliteEnemy2.update(player);
    }

    for (auto & eliteEnemy3: eliteEnemies3) {
        if (eliteEnemy3.isAlive()) eliteEnemy3.update(player);
    }

    // Remove dead enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy & e) {
        return !e.isAlive();
    }), enemies.end());
    eliteEnemies.erase(std::remove_if(eliteEnemies.begin(), eliteEnemies.end(), [](const EliteEnemy & e) {
        return !e.isAlive();
    }), eliteEnemies.end());
    eliteEnemies2.erase(std::remove_if(eliteEnemies2.begin(), eliteEnemies2.end(), [](const EliteEnemy2 & e) {
        return !e.isAlive();
    }), eliteEnemies2.end());
    eliteEnemies3.erase(std::remove_if(eliteEnemies3.begin(), eliteEnemies3.end(), [](const EliteEnemy3 & e) {
        return !e.isAlive();
    }), eliteEnemies3.end());

    if (enemies.size() == 0) {
        Enemy newEnemy(renderer, 2, 2, 15);
        enemies.push_back(newEnemy);
    }
}

void EnemyManager::render() {
    // Render all enemies
    for (auto & enemy: enemies) {
        if (enemy.isAlive()) enemy.render(0, 255, 255);
    }

    for (auto & eliteEnemy: eliteEnemies) {
        if (eliteEnemy.isAlive()) eliteEnemy.render(255, 0, 0);
    }

    for (auto & eliteEnemy2: eliteEnemies2) {
        if (eliteEnemy2.isAlive()) eliteEnemy2.render(255, 255, 0);
    }

    for (auto & eliteEnemy3: eliteEnemies3) {
        if (eliteEnemy3.isAlive()) eliteEnemy3.render(255, 0, 255);
    }
}

void EnemyManager::shift_enemy_position(int newX, int newY) {
    for (auto & enemy: enemies) {
        enemy.set_enemy_position(enemy.getX() + newX, enemy.getY() + newY);
    }

    for (auto & eliteEnemy: eliteEnemies) {
        eliteEnemy.set_enemy_position(eliteEnemy.getX() + newX, eliteEnemy.getY() + newY);

        for (auto & eliteBullet: eliteEnemy.getBullets()) {
            eliteBullet.setBulletPosition(eliteBullet.getX() + newX, eliteBullet.getY() + newY);
        }
    }

    for (auto & eliteEnemy2: eliteEnemies2) {
        eliteEnemy2.set_enemy_position(eliteEnemy2.getX() + newX, eliteEnemy2.getY() + newY);

        for (auto & eliteBullet: eliteEnemy2.getBullets()) {
            eliteBullet.setBulletPosition(eliteBullet.getX() + newX, eliteBullet.getY() + newY);
        }
    }

    for (auto & eliteEnemy3: eliteEnemies3) {
        eliteEnemy3.set_enemy_position(eliteEnemy3.getX() + newX, eliteEnemy3.getY() + newY);
    }
}

void EnemyManager::restart() {
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy & e) {
        return e.isAlive();
    }), enemies.end());
    eliteEnemies.erase(std::remove_if(eliteEnemies.begin(), eliteEnemies.end(), [](const EliteEnemy & e) {
        return e.isAlive();
    }), eliteEnemies.end());
    eliteEnemies2.erase(std::remove_if(eliteEnemies2.begin(), eliteEnemies2.end(), [](const EliteEnemy2 & e) {
        return e.isAlive();
    }), eliteEnemies2.end());
    eliteEnemies3.erase(std::remove_if(eliteEnemies3.begin(), eliteEnemies3.end(), [](const EliteEnemy3 & e) {
        return e.isAlive();
    }), eliteEnemies3.end());
    lastEnemyRespawnTime = 0;
    lastEliteEnemyRespawnTime = 0;
    lastEliteEnemy2RespawnTime = 0;
    lastEliteEnemy3RespawnTime = 0;
}