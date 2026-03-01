#include "basicbutton.h"

#include "SDL2/SDL_ttf.h"

#include "SDL2/SDL.h"

#include <iostream>

#include "player.h"

#include "skill.h"

#include "window.h"

#include "texture.h"

#include "enemy.h"

#include <functional>

#include <SDL2/SDL_image.h>

#include "showwindow.h"

#include "collisionmanager.h"

#include <SDL2/SDL_mixer.h>

extern TTF_Font * gFont16;
extern Window skillTreeWindow;
extern Mix_Chunk * gCoin;
using namespace std;
extern ShowWindow showwindow;

//Enemy enemy; // renderer, 2, 3, 15

Button::Button(SDL_Renderer * renderer, Skill & skill, int x, int y, int width, int height, std::string & label, int skilltype,
    const std::string & imagePath): renderer(renderer), labelText(label), skill( & skill), skilltype(skilltype), imagePath(imagePath) {
    // Set button position and dimensions
    rect = {
        x,
        y,
        width,
        height
    };
    onClick = nullptr; // Initialize onClick to nullptr
    // Set button click behavior based on label
    if (label == "speedUp") {
        std::cout << "Here is speedUp" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.speedUpgrade(player, showwindow);
        };
    } else if (label == "wealth++") {
        std::cout << "Here is wealth" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.wealthUpgrade(player, showwindow);
        };
    } else if (label == "freeze") {
        std::cout << "Here is freeze" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.freezeUpgrade(showwindow);
        }; // enemy, showwindow
    } else if (label == "bounce") {
        std::cout << "Here is bounce" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.bounceUpgrade(player, showwindow);
        };
    } else if (label == "fireRate") {
        std::cout << "Here is fireRate" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.fireRateUpgrade(player, showwindow);
        };
    } else if (label == "multiShot") {
        std::cout << "Here is multiShot" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.multiShotUpgrade(player, showwindow);
        };
    } else if (label == "maxHP") {
        std::cout << "Here is maxHP" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.maxHPUpgrade(player, showwindow);
        };
    } else if (label == "refuel") {
        std::cout << "Here is refuel" << std::endl;
        onClick = [this](Player & player, Skill & skill) {
            skill.refuel(player, showwindow);
        };
    }
}

Button::~Button() {}

void Button::handleEvent(SDL_Event & e, Player & player, Skill & skill) {
    if (skillTreeWindow.isShown() && e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState( & mouseX, & mouseY);
        if (isClicked(mouseX, mouseY)) {
            cout << "Skilltype: " << skilltype << endl;
            Mix_PlayChannel(-1, gCoin, 0);
            onClick(player, skill);
        }
    }
}

std::string Button::GetSkillLevelText() const {
    std::string levelText;

    switch (skilltype) {
    case 0:
        levelText = std::to_string(skill -> getSpeedLevel());
        break;
    case 1:
        levelText = std::to_string(skill -> getWealthLevel());
        break;
    case 2:
        levelText = std::to_string(skill -> getFreezeLevel());
        break;
    case 3:
        levelText = std::to_string(skill -> getBounceLevel());
        break;
    case 4:
        levelText = std::to_string(skill -> getFireRateLevel());
        break;
    case 5:
        levelText = std::to_string(skill -> getMultiShotLevel());
        break;
    case 6:
        levelText = std::to_string(skill -> getMaxHPLevel());
        break;
    case 7:
        levelText = std::to_string(skill -> getrefuelLevel());
        break;
    default:
        levelText = "not applicable"; // Handle the default case as needed
    }

    return levelText;
}

std::string Button::GetSkillCostText() const {
    std::string costText;

    switch (skilltype) {
    case 0:
        costText = std::to_string(skill -> getSpeedCost());
        break;
    case 1:
        costText = std::to_string(skill -> getWealthCost());
        break;
    case 2:
        costText = std::to_string(skill -> getFreezeCost());
        break;
    case 3:
        costText = std::to_string(skill -> getBounceCost());
        break;
    case 4:
        costText = std::to_string(skill -> getFireRateCost());
        break;
    case 5:
        costText = std::to_string(skill -> getMultiShotCost());
        break;
    case 6:
        costText = std::to_string(skill -> getMaxHPCost());
        break;
    case 7:
        costText = std::to_string(skill -> getrefuelCost());
        break;
    default:
        costText = "not applicable"; // Handle the default case as needed
    }

    return costText;
}

void Button::render() const {
    if (skillTreeWindow.isShown()) {
        // labeltext
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        SDL_RenderFillRect(renderer, & rect);
        SDL_Color textColorWhite = {
            255,
            255,
            255,
            255
        };
        SDL_Color textColorBlack = {
            0,
            0,
            0,
            255
        };
        SDL_Surface * textSurface = TTF_RenderText_Solid(gFont16, labelText.c_str(), textColorBlack);
        SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textX = rect.x + (rect.w - textSurface -> w) / 2;
        int textY = rect.y + (rect.h - textSurface -> h) / 2;
        SDL_Rect destinationRect = {
            textX,
            textY,
            textSurface -> w,
            textSurface -> h
        };
        SDL_RenderCopy(renderer, textTexture, nullptr, & destinationRect);

        //current level: Leveltext
        std::string levelText = "Current level: " + GetSkillLevelText();
        SDL_Surface * levelSurface = TTF_RenderText_Solid(gFont16, levelText.c_str(), textColorWhite);
        SDL_Texture * levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
        int levelTextX = rect.x + (rect.w - levelSurface -> w) / 2;
        int levelTextY = rect.y + rect.h + 5;
        SDL_Rect levelDestRect = {
            levelTextX,
            levelTextY,
            levelSurface -> w,
            levelSurface -> h
        };
        SDL_RenderCopy(renderer, levelTexture, nullptr, & levelDestRect);

        //current level: Leveltext
        std::string costText = "Cost: " + GetSkillCostText();
        SDL_Surface * costSurface = TTF_RenderText_Solid(gFont16, costText.c_str(), textColorWhite);
        SDL_Texture * costTexture = SDL_CreateTextureFromSurface(renderer, costSurface);
        int costTextX = rect.x + (rect.w - costSurface -> w) / 2;
        int costTextY = rect.y + rect.h + 20;
        SDL_Rect costDestRect = {
            costTextX,
            costTextY,
            costSurface -> w,
            costSurface -> h
        };
        SDL_RenderCopy(renderer, costTexture, nullptr, & costDestRect);

        SDL_Texture * imageTexture = IMG_LoadTexture(renderer, imagePath.c_str());
        int imageX = rect.x + (rect.w - 100) / 2; // Adjust the position as needed
        int imageY = rect.y - 100;
        SDL_Rect dst;
        dst.x = imageX;
        dst.y = imageY;
        dst.w = 100;
        dst.h = 100;
        SDL_RenderCopy(renderer, imageTexture, nullptr, & dst);

        // Clean up resources
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(levelSurface);
        SDL_DestroyTexture(levelTexture);
        SDL_FreeSurface(costSurface);
        SDL_DestroyTexture(costTexture);
    }
}
bool Button::isClicked(int mouseX, int mouseY) const {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
}