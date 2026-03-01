/*#include "SDL2/SDL.h" */
#include "window.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "skill.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "variable.h"
#include <Windows.h>
#include <iostream>

using namespace std;
extern int COLLISION_ANIMATION[4][6];
extern int COLLISION_STATUS[4];
Window::Window(){
	//Initialize non-existant window
	mWindow = NULL;
	mRenderer = NULL;

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mShown = false;
	mWindowID = -1;
}

int Window::getuseryimuX(){
   SDL_DisplayMode mode;
   SDL_GetDesktopDisplayMode(0, &mode);
   int w = mode.w;
   int h = mode.h;
   return w;
}

int Window::getuseryimuY(){
   SDL_DisplayMode mode;
   SDL_GetDesktopDisplayMode(0, &mode);
   int w = mode.w;
   int h = mode.h;
   return h;
}

bool Window::init(){
	mWindow = SDL_CreateWindow( "CreateWindow", 200, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if( mWindow != NULL ){
		mMouseFocus = true;
		mKeyboardFocus = true;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED);
		if( mRenderer == NULL ){
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
		}
		else{
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );	//Initialize renderer color
			mWindowID = SDL_GetWindowID( mWindow );	//Grab window identifier
			mShown = true;	//Flag as opened
		}
	}
	else{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return mWindow != NULL && mRenderer != NULL;
}

void Window::handleEvent(SDL_Event& e, Player& player){
	for (auto& button : buttons)
        button.handleEvent(e, player, player.getSkill());  // Pass an instance of the Skill class
	
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID ){
		switch( e.window.event ){
			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_RenderPresent( mRenderer );
			break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent( mRenderer );
			break;

			//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			break;
			
			//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;

			//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;
			
			//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

			//Window maximized
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
            break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
            break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow( mWindow );
			break;
		}
	}
}

void Window::focus(){
	if( !mShown )	SDL_ShowWindow( mWindow );		//Restore window if needed
	SDL_RaiseWindow( mWindow );	//Move window forward
}


void Window::render() {
    if (!mMinimized) {
        // Clear screen
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
        SDL_RenderClear(mRenderer);

        // Render buttons
        for (const auto& button : buttons) {
            button.render();
        }
    }
}

void Window::free(){
	if( mWindow != NULL )	SDL_DestroyWindow( mWindow );
	mMouseFocus = false;
	mKeyboardFocus = false;
}

int Window::getHeight(){
	int h, w;
	SDL_GetWindowSize(mWindow, &w, &h);
	return h;
}

int Window::getWidth(){
	int h, w;
	SDL_GetWindowSize(mWindow, &w, &h);
	return w;
}

bool Window::hasMouseFocus(){
	return mMouseFocus;
}

bool Window::hasKeyboardFocus(){
	return mKeyboardFocus;
}

bool Window::isMinimized(){
	return mMinimized;
}

bool Window::isShown(){
	return mShown;
}



void Window::shrinkWindow(Player & player, EnemyManager& enemyManager){
	int x;
	int y;
	SDL_GetWindowPosition(mWindow, &x, &y);
	static bool shrink_from_position = false;
	if(shrink_from_position == false){
		if(this->getWidth() > 320) 	SDL_SetWindowSize(mWindow, this->getWidth() - 1, this->getHeight());
		if(this->getHeight() > 240)	SDL_SetWindowSize(mWindow, this->getWidth(), this->getHeight() - 1);
	}
	else if(shrink_from_position == true){
		if(this->getWidth() > 320){
			SDL_SetWindowSize(mWindow, this->getWidth() - 1, this->getHeight());
			SDL_SetWindowPosition(mWindow, x + 1, y);
			x += 1;
			player.setPlayerPosition(player.getX() - 1, player.getY());
			enemyManager.shift_enemy_position(-1, 0);
			for (auto& bullet : player.getBullets())	bullet.setBulletPosition(bullet.getX() - 1, bullet.getY());
		}
		if(this->getHeight() > 240){
			SDL_SetWindowSize(mWindow, this->getWidth(), this->getHeight() - 1);
			SDL_SetWindowPosition(mWindow, x, y + 1);
			y += 1;
			player.setPlayerPosition(player.getX(), player.getY() - 1);
			enemyManager.shift_enemy_position(0, -1);
			for (auto& bullet : player.getBullets())	bullet.setBulletPosition(bullet.getX(), bullet.getY() - 1);
		}
	}
	shrink_from_position = !shrink_from_position;

	if(COLLISION_STATUS[0] < 6 && x > 10){
		player.setPlayerPosition(player.getX() + COLLISION_ANIMATION[0][COLLISION_STATUS[0]], player.getY());
		enemyManager.shift_enemy_position(COLLISION_ANIMATION[0][COLLISION_STATUS[0]], 0);
		SDL_SetWindowSize(mWindow, this->getWidth() + COLLISION_ANIMATION[0][COLLISION_STATUS[0]], this->getHeight());
		SDL_SetWindowPosition(mWindow, x - COLLISION_ANIMATION[0][COLLISION_STATUS[0]], y);
		x -= COLLISION_ANIMATION[0][COLLISION_STATUS[0]];
		for (auto& bullet : player.getBullets())
			bullet.setBulletPosition(bullet.getX() + COLLISION_ANIMATION[0][COLLISION_STATUS[0]], bullet.getY());
		COLLISION_STATUS[0]++;
	}
	if(COLLISION_STATUS[1] < 6 && y > 10){
		player.setPlayerPosition(player.getX(), player.getY() + COLLISION_ANIMATION[1][COLLISION_STATUS[1]]);
		enemyManager.shift_enemy_position(0, COLLISION_ANIMATION[1][COLLISION_STATUS[1]]);
		SDL_SetWindowSize(mWindow, this->getWidth(), this->getHeight() + COLLISION_ANIMATION[1][COLLISION_STATUS[1]]);
		SDL_SetWindowPosition(mWindow, x, y - COLLISION_ANIMATION[1][COLLISION_STATUS[1]]);
		y -= COLLISION_ANIMATION[1][COLLISION_STATUS[1]];
		for (auto& bullet : player.getBullets())
			bullet.setBulletPosition(bullet.getX(), bullet.getY() + COLLISION_ANIMATION[1][COLLISION_STATUS[1]]);
		COLLISION_STATUS[1]++;
	}
	if(COLLISION_STATUS[2] < 6 && x + this->getWidth() < this->getuseryimuX() - 10){
		SDL_SetWindowSize(mWindow, this->getWidth() + COLLISION_ANIMATION[2][COLLISION_STATUS[2]], this->getHeight());
		COLLISION_STATUS[2]++;
	}
	if(COLLISION_STATUS[3] < 6 && y + this->getHeight() < this->getuseryimuY() - 30){
		SDL_SetWindowSize(mWindow, this->getWidth(), this->getHeight() + COLLISION_ANIMATION[3][COLLISION_STATUS[3]]);
		COLLISION_STATUS[3]++;
	}
}

void Window::close(){
	SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

