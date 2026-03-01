#ifndef WINDOW_H
#define WINDOW_H
#include "SDL2/SDL.h"

#include "Skill.h"

#include "player.h"

#include "enemy.h"

#include "basicbutton.h"

class Window {
    public: Window(); //Intializes internals
    bool init(); //Creates window
    void focus(); //Focuses on window
    void render(); //Shows windows contents
    void free(); //Deallocates internal
    void handleEvent(SDL_Event & e, Player & player);

    const std::vector < Button > & getButtons() const {
        return buttons;
    }

    void addButton(const Button & button) {
        buttons.push_back(button);
    }
    //Window dimensions
    int getWidth();
    int getHeight();
    int getuseryimuX();
    int getuseryimuY();
    void shrinkWindow(Player & player, EnemyManager & enemyManager);

    //Window focii
    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
    bool isShown();

    //show window data
    SDL_Window * showWindow() {
        return mWindow;
    }
    SDL_Renderer * showRenderer() {
        return mRenderer;
    }

    void close();

    private: Skill skill;
    int mWindowID;
    SDL_Window * mWindow;
    SDL_Renderer * mRenderer;
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;
    bool mShown;
    std::vector < Button > buttons;

};

#endif