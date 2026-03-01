#pragma once
#ifndef BASICBUTTON_H
#define BASICBUTTON_H
#include "SDL2/SDL.h"
#include <string>

#include "Skill.h"

#include "player.h"

#include <functional>

//class Skill;
class Player;
class Button {
    public: Button(SDL_Renderer * renderer, Skill & skill, int x, int y, int width, int height, std::string & label, int skilltype,
        const std::string & imagepath);
    ~Button();

    bool isClicked(int mouseX, int mouseY) const;
    void render() const;
    void handleEvent(SDL_Event & e, Player & player, Skill & skill);

    int returnskill() {
        return skilltype;
    }

    std::string GetSkillLevelText() const;
    std::string GetSkillCostText() const;

    SDL_Texture * loadTexture(const std::string & imagePath, SDL_Renderer * renderer);
    void renderTexture(SDL_Texture * tex, SDL_Renderer * renderer, int x, int y, int w, int h);
    SDL_Texture * imageTexture;
    SDL_Rect rect;
    SDL_Renderer * renderer;
    SDL_Window * mWindow;
    std::string labelText;
    std::string costText;
    std::string imagePath;
    int skilltype = 0;
    Skill * skill;
    std:: function < void(Player & , Skill & ) > onClick;
    void setOnClickFunction();
    void renderCurrentLevel() const;
};
#endif // BASICBUTTON_H