#include <cmath>

#include <iostream>

#include "EliteBullet.h"

#include "variable.h"

#include "window.h"

#include "player.h"

extern Window gameWindow;
extern int COLLISION_STATUS[4];

EliteBullet::EliteBullet(int startX, int startY): Bullet(startX, startY, 1, 4, 5) {
    // initialize elite bullet speed and survival status
}

EliteBullet::~EliteBullet() {
    // Any resources can be released here, if any
}

void EliteBullet::update() {
    Uint32 currentTime = SDL_GetTicks(); // Get the current time

    // Check if enough time has passed since the last elite bullet shot
    if (this -> isAlive()) {
        // Update elite bullet position
        x += velocityX;
        y += velocityY;

        if (x < -1000 || y < -1000 || x > 1000 || y > 1000) {
            this -> set0health();
        }
    }
}

void EliteBullet::render(SDL_Renderer * renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
}

EliteBullet2::EliteBullet2(int startX, int startY): Bullet(startX, startY, 1, 6, 5) {
    // initialize elite bullet speed and survival status
}

EliteBullet2::~EliteBullet2() {
    // Any resources can be released here, if any
}

void EliteBullet2::update() {
    Uint32 currentTime = SDL_GetTicks(); // Get the current time

    // Check if enough time has passed since the last elite bullet shot
    if (this -> isAlive()) {
        // Update elite bullet position
        x += velocityX;
        y += velocityY;

        if (x < -1000 || y < -1000 || x > 1000 || y > 1000) {
            this -> set0health();
        }
    }
}

void EliteBullet2::render(SDL_Renderer * renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
}

EliteBullet3::EliteBullet3(int startX, int startY): Bullet(startX, startY, 1, 3, 5) {
    // initialize elite bullet speed and survival status
}

EliteBullet3::~EliteBullet3() {
    // Any resources can be released here, if any
}

void EliteBullet3::update() {
    Uint32 currentTime = SDL_GetTicks(); // Get the current time

    // Check if enough time has passed since the last elite bullet shot
    if (this -> isAlive()) {
        // Update elite bullet position
        x += velocityX;
        y += velocityY;

        if (x < -1000 || y < -1000 || x > 1000 || y > 1000) {
            this -> set0health();
        }
    }
}

void EliteBullet3::render(SDL_Renderer * renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
}