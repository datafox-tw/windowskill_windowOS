#include <SDL2/SDL_mixer.h>

#include <algorithm>

#include <cmath>

#include "player.h"

#include "variable.h"

#include "window.h"

#include "timer.h"

extern Window gameWindow;
extern LTimer timer;

extern Mix_Chunk * gShoot;
Player::Player(SDL_Renderer * r, int a, int b): renderer(r), x(a), y(b), radius(15), velocity(5.5), lastBulletTime(0),
    multiShot(0), bounce(0) {}
Player::~Player() {}

double Player::getX() const {
    return x;
}
double Player::getY() const {
    return y;
}
int Player::getRadius() {
    return radius;
}

void Player::handleEvent(SDL_Event & e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_w:
            movingUp = true;
            break;
        case SDLK_s:
            movingDown = true;
            break;
        case SDLK_a:
            movingLeft = true;
            break;
        case SDLK_d:
            movingRight = true;
            break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_w:
            movingUp = false;
            break;
        case SDLK_s:
            movingDown = false;
            break;
        case SDLK_a:
            movingLeft = false;
            break;
        case SDLK_d:
            movingRight = false;
            break;
        }
    }

    NowTime = timer.getTicks();

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        if ((NowTime - lastBulletTime) >= fireRate) {
            Mix_PlayChannel(-1, gShoot, 0);
            Bullet newBullet(x, y, 1 + bounce, 7, 3);
            newBullet.setDirectionToMouse(x, y, e.button.x, e.button.y);
            bullets.push_back(newBullet);
            bulletFired++;

            multiShot = skill.getMultiShotLevel();

            lastBulletTime = NowTime;
            lastMultiShotTime = NowTime;
        }
    } else if (e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0) {
        if ((NowTime - lastBulletTime) >= fireRate) {
            Mix_PlayChannel(-1, gShoot, 0);
            Bullet newBullet(x, y, 1 + bounce, 7, 3);
            newBullet.setDirectionToMouse(x, y, e.button.x, e.button.y);
            bullets.push_back(newBullet);
            bulletFired++;

            multiShot = skill.getMultiShotLevel();

            lastBulletTime = NowTime;
            lastMultiShotTime = NowTime;
        }
    }

    if (multiShot > 0) {
        if ((NowTime - lastMultiShotTime) >= 100) {
            Mix_PlayChannel(-1, gShoot, 0);
            int mouseX, mouseY;
            SDL_GetMouseState( & mouseX, & mouseY);
            Bullet newBullet(x, y, 1 + bounce, 7, 3);
            newBullet.setDirectionToMouse(x, y, mouseX, mouseY);
            bullets.push_back(newBullet);
            bulletFired++;
            multiShot -= 1;
            lastMultiShotTime = NowTime;
        }
    }
}

void Player::update(Player & player, EnemyManager & enemyManager) {
    if (movingUp && !movingLeft && !movingRight) y -= velocity;
    if (movingDown && !movingLeft && !movingRight) y += velocity;
    if (movingLeft && !movingUp && !movingDown) x -= velocity;
    if (movingRight && !movingUp && !movingDown) x += velocity;
    if (movingUp && movingLeft) {
        y -= velocity / 1.414;
        x -= velocity / 1.414;
    }
    if (movingUp && movingRight) {
        y -= velocity / 1.414;
        x += velocity / 1.414;
    }
    if (movingDown && movingLeft) {
        y += velocity / 1.414;
        x -= velocity / 1.414;
    }
    if (movingDown && movingRight) {
        y += velocity / 1.414;
        x += velocity / 1.414;
    }

    if (x < radius) x = radius;
    if (y < radius) y = radius;
    if (x > gameWindow.getWidth() - radius) x = gameWindow.getWidth() - radius;
    if (y > gameWindow.getHeight() - radius) y = gameWindow.getHeight() - radius;

    for (auto & bullet: bullets) bullet.update(); // Update all bullets

    // Remove dead bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet & b) {
        return !b.isAlive();
    }), bullets.end());
}

void Player::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
        a = static_cast < int > (x + (radius - 1) * std::cos(angle));
        b = static_cast < int > (y + (radius - 1) * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
    for (const auto & bullet: bullets)
        if (bullet.isAlive()) bullet.render(renderer);
}

int Player::show_total_HP() {
    return total_HP;
}
int Player::show_current_HP() {
    return current_HP;
}

// Overloaded decreaseHP function to allow different amounts of HP reduction
void Player::decreaseHP(int amount) {
    current_HP -= amount;
    if (current_HP < 0) {
        current_HP = 0;
    }
}

// Original decreaseHP function that reduces HP by 1 (backward compatible)
void Player::decreaseHP() {
    decreaseHP(1); // Calls the overloaded function with a default reduction of 1
}

void Player::setPlayerPosition(double newX, double newY) {
    x = newX;
    y = newY;
}

void Player::restart() {
    skill.restart();
    current_HP = 20;
    total_HP = 20;
    x = 100;
    y = 100;
    velocity = 5.5;
    fireRate = 500;
    bulletFired = 0;
    bounce = 0;
    enemyKilled = 0;
    bossKilled = 0;
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet & b) {
        return b.isAlive();
    }), bullets.end());
}

int Player::getBulletFired() {
    return bulletFired;
}

int Player::getEnemyKilled() {
    return enemyKilled;
}

int Player::getBossKilled() {
    return bossKilled;
}

void Player::killEnemy() {
    enemyKilled++;
}

void Player::killBoss() {
    bossKilled++;
    enemyKilled++;
}

void Player::setValue(int v, Uint32 rate, int MaxHP, int CurrentHP, int mShot, int b) {
    velocity = v;
    fireRate = rate;
    total_HP = MaxHP;
    current_HP = CurrentHP;
    multiShot = mShot;
    bounce = b;
}

void Player::setVelocity(int newVelocity) {
    velocity = newVelocity;
}

int Player::getVelocity() const {
    return velocity;
}

void Player::resetMovementFlags() {
    movingUp = false;
    movingDown = false;
    movingLeft = false;
    movingRight = false;
}