#include <cmath>

#include <iostream>

#include "bullet.h"

#include "variable.h"

#include "window.h"

#include "player.h"

#include <SDL2/SDL_mixer.h>

using namespace std;

extern Window gameWindow;
extern int COLLISION_STATUS[4];
extern Mix_Chunk * gExpand;

Bullet::Bullet(int startX, int startY, int h, int speed, int r): x(startX), y(startY), health(h), bulletSpeed(speed), radius(r) {
    // initialize bullet speed and survival status
}

Bullet::~Bullet() {
    // Any resources can be released here, if any
}

void Bullet::update() {
    if (this -> isAlive()) {
        // Update bullet position
        x += velocityX;
        y += velocityY;
        // Check if the bullet intersects with the screen
        if (x < radius) {
            Mix_PlayChannel(-1, gExpand, 0);
            COLLISION_STATUS[0] = 0;
            health--;
            x -= velocityX;
            velocityX *= -1;
        } else if (y < radius) {
            Mix_PlayChannel(-1, gExpand, 0);
            COLLISION_STATUS[1] = 0;
            health--;
            y -= velocityY;
            velocityY *= -1;

        } else if (x > gameWindow.getWidth() - radius) {
            Mix_PlayChannel(-1, gExpand, 0);
            COLLISION_STATUS[2] = 0;
            health--;
            x -= velocityX;
            velocityX *= -1;
        } else if (y > gameWindow.getHeight() - radius) {
            Mix_PlayChannel(-1, gExpand, 0);
            COLLISION_STATUS[3] = 0;
            health--;
            y -= velocityY;
            velocityY *= -1;
        }
    }
}

void Bullet::render(SDL_Renderer * renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color (red)
    for (int i = 0; i < CIRCLE_POINTS; ++i) {
        double angle = 2 * PI * i / CIRCLE_POINTS;
        int a = static_cast < int > (x + radius * std::cos(angle));
        int b = static_cast < int > (y + radius * std::sin(angle));
        SDL_RenderDrawPoint(renderer, a, b);
    }
}

void Bullet::setDirectionToMouse(int startX, int startY, int mouseX, int mouseY) {
    double angle = atan2(mouseY - startY, mouseX - startX); // Calculate the direction vector of the bullet

    // Set the speed component of the bullet. Here you can adjust the speed of the bullet.
    velocityX = static_cast < double > (cos(angle) * bulletSpeed);
    velocityY = static_cast < double > (sin(angle) * bulletSpeed);
}

int Bullet::getX() {
    return x;
}

int Bullet::getY() {
    return y;
}

void Bullet::setBulletPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

int Bullet::getRadius() {
    return radius;
}