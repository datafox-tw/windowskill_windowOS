#include "SDL2/SDL.h"

#include <SDL2/SDL_mixer.h>

#include "showWindow.h"

#include "basicbutton.h"

#include "texture.h"

#include "skill.h"

#include "player.h"

#include "window.h"

#include "enemy.h"

#include "variable.h"

#include "timer.h"

#include "bullet.h"

#include "collisionManager.h"

#include "graphics.h"

#include <iostream>

using namespace std;
int COLLISION_ANIMATION[4][6] = {
    {
        16,
        12,
        8,
        4,
        2,
        1
    },
    {
        16,
        12,
        8,
        4,
        2,
        1
    },
    {
        16,
        12,
        8,
        4,
        2,
        1
    },
    {
        16,
        12,
        8,
        4,
        2,
        1
    }
};
int COLLISION_STATUS[4] = {
    6,
    6,
    6,
    6
};

int volumnsetting = 1;

Window StartWindow;
Window gameWindow;
Window skillTreeWindow;
Window pauseWindow;
Window gameOverWindow;
Window gameWinnerWindow;

ShowWindow showwindow;

LTexture gTimeTextTexture;
LTexture gHPTextTexture;
LTexture gcoinsTextTexture;
LTexture gPauseTextTexture;
LTexture gSoundTextTexture;

LTimer timer;

Mix_Music * gMusic = NULL;
Mix_Chunk * gShoot = NULL;
Mix_Chunk * gDestroy = NULL;
Mix_Chunk * gSelfDamage = NULL;
Mix_Chunk * gCoin = NULL;
Mix_Chunk * gExpand = NULL;
Mix_Chunk * gGameover = NULL;
Mix_Chunk * gWin = NULL;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization fail \n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
            success = false;
        }
        //Create gameWindow
        if (!gameWindow.init()) {
            printf("gameWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(gameWindow.showWindow(), "window");

        //Create skillTreeWindow
        if (!skillTreeWindow.init()) {
            printf("skillTreeWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(skillTreeWindow.showWindow(), "skilltree");
        SDL_HideWindow(skillTreeWindow.showWindow());

        //Create pauseWindow
        if (!pauseWindow.init()) {
            printf("pauseWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(pauseWindow.showWindow(), "setting");
        SDL_HideWindow(pauseWindow.showWindow());

        //Create gameoverWindow
        if (!gameOverWindow.init()) {
            printf("gameoverWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(gameOverWindow.showWindow(), "game over");
        SDL_HideWindow(gameOverWindow.showWindow());

        //Create gameWinnerWindow
        if (!gameWinnerWindow.init()) {
            printf("gameWinnerWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(gameWinnerWindow.showWindow(), "game WINNER");
        SDL_HideWindow(gameWinnerWindow.showWindow());

        //Create Startwindow
        if (!StartWindow.init()) {
            printf("StartWindow could not be created!\n");
            success = false;
        }
        SDL_SetWindowTitle(StartWindow.showWindow(), "StartWindow");
        SDL_HideWindow(StartWindow.showWindow());

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }

        if (!loadMedia()) {
            success = false;
            printf("Failed to load media!\n");
        }

        //Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
        Mix_Chunk * soundEffect = Mix_LoadWAV("path/to/sound_effect.wav");

        gMusic = Mix_LoadMUS("sound/bgm3.mp3");
        gShoot = Mix_LoadWAV("sound/shoot.wav");
        gDestroy = Mix_LoadWAV("sound/mini_bomb.wav");
        gSelfDamage = Mix_LoadWAV("sound/self_damaged.wav");
        gCoin = Mix_LoadWAV("sound/coin.wav");
        gExpand = Mix_LoadWAV("sound/expand.wav");
        gGameover = Mix_LoadWAV("sound/gameover.wav");
        gWin = Mix_LoadWAV("sound/win.wav");

        IMG_Init(IMG_INIT_PNG);
    }

    return success;
}

void button_Init(Player & player) {
    for (int i = 0; i < 8; ++i) {
        int offsetX, offsetY;
        if (i % 2 == 0) {
            offsetY = -170;
            offsetX = (-275 + 150 * (i / 2));
        } else {
            offsetY = 80;
            offsetX = (-275 + 150 * (i / 2));
        }

        std::string label;
        switch (i) {
        case 0:
            label = "speedUp";
            break;
        case 1:
            label = "wealth++";
            break;
        case 2:
            label = "freeze";
            break;
        case 3:
            label = "bounce";
            break;
        case 4:
            label = "fireRate";
            break;
        case 5:
            label = "multiShot";
            break;
        case 6:
            label = "maxHP";
            break;
        case 7:
            label = "refuel";
            break;
        }
        const std::string imagePath = "img/" + label + ".png";
        Button button(skillTreeWindow.showRenderer(), player.getSkill(), (SCREEN_WIDTH / 2 + offsetX), (SCREEN_HEIGHT / 2 + offsetY) + 50, 100, 50, label, i, imagePath);

        skillTreeWindow.addButton(button);
    }
}

void close() {
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gShoot);
    Mix_FreeChunk(gDestroy);
    Mix_FreeChunk(gSelfDamage);
    Mix_FreeChunk(gCoin);
    Mix_FreeChunk(gGameover);
    gameWindow.close();
    skillTreeWindow.close();
    pauseWindow.close();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char * args[]) {
    if (!init()) {
        printf("Failed to initialize!");
    } else {
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(gMusic, -1);
        }

        Player player(gameWindow.showRenderer(), 100, 100);
        EnemyManager enemyManager(gameWindow.showRenderer()); // Create an EnemyManager object
        button_Init(player);
        CollisionManager collisionManager(2, 5, 5, 5);
        bool quit = false;
        bool start = false;
        SDL_Event e;
        timer.start();
        int count = 0;
        while (!quit) {
			
            Uint32 frameStart = SDL_GetTicks();

            while (SDL_PollEvent( & e) != 0) {
                gameWindow.handleEvent(e, player);
                skillTreeWindow.handleEvent(e, player);
                pauseWindow.handleEvent(e, player);
                gameOverWindow.handleEvent(e, player);
                gameWinnerWindow.handleEvent(e, player);
                StartWindow.handleEvent(e, player);
                if (gameWindow.hasKeyboardFocus()) player.handleEvent(e);

                if (!gameWindow.isShown()) quit = true;

                if (e.type == SDL_KEYDOWN && !gameOverWindow.isShown() && !gameWinnerWindow.isShown() && !StartWindow.isShown()) {
                    switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        if (skillTreeWindow.isShown()) SDL_HideWindow(skillTreeWindow.showWindow());
                        else skillTreeWindow.focus();
                        break;

                    case SDLK_ESCAPE:
                        if (pauseWindow.isShown()) SDL_HideWindow(pauseWindow.showWindow());
                        else pauseWindow.focus();
                        break;
                    }
                }
                if (e.type == SDL_KEYDOWN && gameOverWindow.isShown()) {
                    if (e.key.keysym.sym == SDLK_SPACE) SDL_HideWindow(gameOverWindow.showWindow());
                }
                if (e.type == SDL_KEYDOWN && gameWinnerWindow.isShown()) {
                    if (e.key.keysym.sym == SDLK_SPACE) SDL_HideWindow(gameWinnerWindow.showWindow());
                }
                if (e.type == SDL_KEYDOWN && StartWindow.isShown()) {
                    if (e.key.keysym.sym == SDLK_SPACE) SDL_HideWindow(StartWindow.showWindow());
                }
            }
            if (count == 0) {
                player.resetMovementFlags();
                StartWindow.focus();
                showwindow.showStartWindow();
                showwindow.restart(player, timer, gameWindow, enemyManager);
            }
            if (player.show_current_HP() == 0) {
                player.resetMovementFlags();
                Mix_PlayChannel(-1, gGameover, 0);
                gameOverWindow.focus();
                showwindow.showGameOverWindow(player, timer);
                showwindow.restart(player, timer, gameWindow, enemyManager);
            }
            if (timer.getTicks() >= 300000) {
                player.resetMovementFlags();
                Mix_PlayChannel(-1, gWin, 0);
                gameWinnerWindow.focus();
                showwindow.showWinnerWindow(player, timer);
                showwindow.restart(player, timer, gameWindow, enemyManager);
            }

            if (gameWindow.hasKeyboardFocus()) {
                timer.unpause();

                gameWindow.shrinkWindow(player, enemyManager);

                player.update(player, enemyManager);
                enemyManager.update(player); // Update the EnemyManager with the player
                collisionManager.checkBulletEnemyCollision(player, enemyManager.getEnemies(), enemyManager.getEliteEnemies(), enemyManager.getEliteEnemies2(), enemyManager.getEliteEnemies3(), player.getBullets());
                collisionManager.checkPlayerEnemyCollision(player, enemyManager.getEnemies(), enemyManager.getEliteEnemies(), enemyManager.getEliteEnemies2(), enemyManager.getEliteEnemies3());

                showwindow.showGameWindow(player, timer);
                player.render();
                enemyManager.render(); // Render enemies

                SDL_RenderPresent(gameWindow.showRenderer()); // update screen

                Uint32 frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < FRAME_DELAY) {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
            } else {
                timer.pause();
            }

            if (skillTreeWindow.hasKeyboardFocus()) {
                player.resetMovementFlags();
                showwindow.showSkillTreeWindow(e, player);
            }

            if (pauseWindow.hasKeyboardFocus()) {
                player.resetMovementFlags();
                showwindow.showPauseWindow();
            }
            if (player.getSkill().show_coins() >= 50) {
                showwindow.Shouldupdate();
            }
            if (timer.getTicks() >= 50 && timer.getTicks() < 3000) {
                showwindow.grade1();
            }
            if (timer.getTicks() >= 30000 && timer.getTicks() < 33000) {
                showwindow.grade2();
            }
            if (timer.getTicks() >= 60000 && timer.getTicks() < 63000) {
                showwindow.grade3();
            }
            if (timer.getTicks() >= 90000 && timer.getTicks() < 93000) {
                showwindow.grade4();
            }
            if (timer.getTicks() >= 120000 && timer.getTicks() < 123000) {
                showwindow.grade5();
            }
            if (timer.getTicks() >= 180000 && timer.getTicks() < 183000) {
                showwindow.grade6();
            }
            if (timer.getTicks() >= 240000 && timer.getTicks() < 243000) {
                showwindow.grade7();
            }
            count++;

        }
    }

    close();
    return 0;
}