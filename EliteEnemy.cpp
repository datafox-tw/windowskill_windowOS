#include "EliteEnemy.h"

#include <cstdlib>

#include <ctime>

#include <cmath>

#include "variable.h"

#include <algorithm>

#include "player.h"

#include "window.h"

#include "timer.h"

extern LTimer timer;

EliteEnemy::EliteEnemy(SDL_Renderer * renderer, int speed): Enemy(renderer, 6, 3, 25), speed(speed), lastBulletTime(0), NowTime(0), fireRate(2000) {}

EliteEnemy::~EliteEnemy() {
    // Boss destructor code, if needed
}

void EliteEnemy::update(const Player & player) {
    // Calculate the direction vector to the player
    double angle = atan2(player.getY() - y, player.getX() - x);

    Uint32 t = timer.getTicks();
    if (freeze < 1 && t - freezeTime >= 3000) freeze = 1;

    // Set the speed component of the enemy. Here you can adjust the speed of the enemy.
    double velocityX = static_cast < double > (cos(angle) * speed * freeze);
    double velocityY = static_cast < double > (sin(angle) * speed * freeze);

    // Update enemy position
    x += velocityX;
    y += velocityY;

    NowTime = timer.getTicks();

    if ((NowTime - lastBulletTime) >= fireRate) {
        EliteBullet newBullet(x, y);
        newBullet.setDirectionToMouse(x, y, player.getX(), player.getY());
        eliteBullets.push_back(newBullet);
        lastBulletTime = NowTime;
    }

//    fireRate -= 500;
    lastFireRateDecreaseTime = NowTime;
    for (auto & eliteBullet: eliteBullets) eliteBullet.update(); // Update all bullets
    // Remove dead bullets
    eliteBullets.erase(std::remove_if(eliteBullets.begin(), eliteBullets.end(), [](const EliteBullet & b) {
        return !b.isAlive();
    }), eliteBullets.end());

}

void EliteEnemy::render(int r, int g, int b) {
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

    for (const auto & eliteBullet: eliteBullets)
        if (eliteBullet.isAlive()) eliteBullet.render(renderer);
}

EliteEnemy2::EliteEnemy2(SDL_Renderer * renderer): Enemy(renderer, 4, 3, 15), lastBulletTime(0), NowTime(0), fireRate(2000) {}

EliteEnemy2::~EliteEnemy2() {

}

void EliteEnemy2::update(const Player & player) {
    // Calculate the direction vector to the player
    double angle = atan2(player.getY() - y, player.getX() - x);

    Uint32 t = timer.getTicks();
    if (freeze < 1 && t - freezeTime >= 3000) freeze = 1;

    // Set the speed component of the enemy. Here you can adjust the speed of the enemy.
    double velocityX = static_cast < double > (cos(angle) * speed * freeze);
    double velocityY = static_cast < double > (sin(angle) * speed * freeze);

    // Update enemy position
    x += velocityX;
    y += velocityY;

    NowTime = timer.getTicks();

    if ((NowTime - lastBulletTime) >= fireRate) {
        EliteBullet2 newBullet(x, y);
        newBullet.setDirectionToMouse(x, y, player.getX(), player.getY());
        eliteBullets2.push_back(newBullet);
        lastBulletTime = NowTime;
    }

    for (auto & eliteBullet2: eliteBullets2) eliteBullet2.update(); // Update all bullets

    // Remove dead bullets
    eliteBullets2.erase(std::remove_if(eliteBullets2.begin(), eliteBullets2.end(), [](const EliteBullet2 & b) {
        return !b.isAlive();
    }), eliteBullets2.end());
}

void EliteEnemy2::render(int r, int g, int b) {
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

    for (const auto & eliteBullet2: eliteBullets2)
        if (eliteBullet2.isAlive()) eliteBullet2.render(renderer);

}

EliteEnemy3::EliteEnemy3(SDL_Renderer * renderer, int speed): Enemy(renderer, 10, 2, 40), speed(2.5), lastBulletTime(0), NowTime(0), fireRate(4000) {}

EliteEnemy3::~EliteEnemy3() {
    // Boss destructor code, if needed
}

void EliteEnemy3::update(const Player & player) {
    // Calculate the direction vector to the player
    double angle = atan2(player.getY() - y, player.getX() - x);

    Uint32 t = timer.getTicks();
    if (freeze < 1 && t - freezeTime >= 3000) freeze = 1;

    // Set the speed component of the enemy. Here you can adjust the speed of the enemy.
    double velocityX = static_cast < double > (cos(angle) * speed * freeze);
    double velocityY = static_cast < double > (sin(angle) * speed * freeze);

    // Update enemy position
    x += velocityX;
    y += velocityY;
    NowTime = timer.getTicks();
    if ((NowTime - lastBulletTime) >= fireRate) {
        EliteBullet3 newBullet(x, y);
        newBullet.setDirectionToMouse(x, y, x + 100, y + 100);
        eliteBullets3.push_back(newBullet);
        EliteBullet3 newBullet2(x, y);
        newBullet2.setDirectionToMouse(x, y, x - 100, y - 100);
        eliteBullets3.push_back(newBullet2);
        EliteBullet3 newBullet3(x, y);
        newBullet3.setDirectionToMouse(x, y, x + 100, y - 100);
        eliteBullets3.push_back(newBullet3);
        EliteBullet3 newBullet4(x, y);
        newBullet4.setDirectionToMouse(x, y, x - 100, y + 100);
        eliteBullets3.push_back(newBullet4);
        EliteBullet3 newBullet5(x, y);
        newBullet5.setDirectionToMouse(x, y, x, y + 200);
        eliteBullets3.push_back(newBullet5);
        EliteBullet3 newBullet6(x, y);
        newBullet6.setDirectionToMouse(x, y, x + 200, y);
        eliteBullets3.push_back(newBullet6);
        EliteBullet3 newBullet7(x, y);
        newBullet7.setDirectionToMouse(x, y, x, y - 200);
        eliteBullets3.push_back(newBullet7);
        EliteBullet3 newBullet8(x, y);
        newBullet8.setDirectionToMouse(x, y, x - 200, y);
        eliteBullets3.push_back(newBullet8);
        lastBulletTime = NowTime;
    }
    // Update all bullets
    for (auto & eliteBullet3: eliteBullets3)
        eliteBullet3.update();
    // Remove dead bullets
    eliteBullets3.erase(
        std::remove_if(eliteBullets3.begin(), eliteBullets3.end(),
            [](const EliteBullet3 & b) {
                return !b.isAlive();
            }),
        eliteBullets3.end());

}

void EliteEnemy3::render(int r, int g, int b) {
    if (freeze == 1) SDL_SetRenderDrawColor(renderer, 0, r, g, b);
    else SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
        a = static_cast < int > (x + (radius - 1) * std::cos(angle));
        b = static_cast < int > (y + (radius - 1) * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
    for (const auto & eliteBullet3: eliteBullets3)
        if (eliteBullet3.isAlive()) eliteBullet3.render(renderer);
}