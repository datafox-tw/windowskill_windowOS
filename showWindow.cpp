#include "player.h"
#include "Skill.h"
#include "timer.h"
#include "window.h"
#include "enemy.h"
#include "timer.h"
#include "texture.h"
#include "SDL2/SDL.h"
#include "basicbutton.h"
#include "variable.h"
#include "showwindow.h"
#include <iostream>
using namespace std;
extern Window gameWindow;
extern Window pauseWindow;
extern Window skillTreeWindow;
extern Window gameOverWindow;
extern Window gameWinnerWindow;
extern Window StartWindow;

extern TTF_Font* gFont28;
extern TTF_Font* gFont36;
extern TTF_Font* gFont16;

extern LTexture gTimeTextTexture;
extern LTexture gHPTextTexture;
extern LTexture gcoinsTextTexture;
extern LTexture gPauseTextTexture;
extern LTexture gSoundTextTexture;

ShowWindow::ShowWindow(){}
ShowWindow::~ShowWindow() {}

void ShowWindow::restart(Player &player, LTimer &time, Window &window, EnemyManager &enemyManager){
	showType = 0;
	showTime = 0;
	player.restart();
	enemyManager.restart();
	//gameWindow restart
	SDL_SetWindowPosition(window.showWindow(), 200, 100);
	SDL_SetWindowSize(window.showWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//time restart
	time.stop();
	time.start();
	time.pause();
}

void ShowWindow::showGameOverWindow(Player &player, LTimer &time){
	gameOverWindow.render();
	
	LTexture gameOverTexture;
	LTexture coinCollectedTexture;
	LTexture timeSurvivedTexture;
	LTexture bulletFiredTexture;
	LTexture enemyKilledTexture;
	LTexture bossKilledTexture;
	LTexture restartTexture;
	
	SDL_Color textColor = { 255, 255, 255, 255};
	
	std::stringstream gameOverText;
	std::stringstream coinCollectedText;
	std::stringstream timeSurvivedText;
	std::stringstream bulletFiredText;
	std::stringstream enemyKilledText;
	std::stringstream bossKilledText;
	std::stringstream restartText;
	
	gameOverText.str( "" );
	gameOverText << "Game Over";
	coinCollectedText.str( "" );
	coinCollectedText << "Coin Collected: " << player.getSkill().show_coins();
	timeSurvivedText.str( "" );
	timeSurvivedText << "Time Survived: " << (time.getTicks()/1000.0) << " seconds";
	bulletFiredText.str( "" );
	bulletFiredText << "Bullet Fired: " << player.getBulletFired();
	enemyKilledText.str( "" );
	enemyKilledText<< "Enemy Killed: " << player.getEnemyKilled();
	bossKilledText.str( "" );
	bossKilledText << "Boss Killed: " << player.getBossKilled();
	restartText.str( "" );
	restartText << "Press SPACE to restart.";
		
	gameOverTexture.loadFromRenderedText(gFont36, gameOverText.str().c_str(), textColor, gameOverWindow.showRenderer());
	coinCollectedTexture.loadFromRenderedText(gFont28, coinCollectedText.str().c_str(), textColor, gameOverWindow.showRenderer());
	timeSurvivedTexture.loadFromRenderedText(gFont28, timeSurvivedText.str().c_str(), textColor, gameOverWindow.showRenderer());
	bulletFiredTexture.loadFromRenderedText(gFont28, bulletFiredText.str().c_str(), textColor, gameOverWindow.showRenderer());
	enemyKilledTexture.loadFromRenderedText(gFont28, enemyKilledText.str().c_str(), textColor, gameOverWindow.showRenderer());
	bossKilledTexture.loadFromRenderedText(gFont28, bossKilledText.str().c_str(), textColor, gameOverWindow.showRenderer());
	restartTexture.loadFromRenderedText(gFont16, restartText.str().c_str(), textColor, gameOverWindow.showRenderer());	
		
	gameOverTexture.render( (gameOverWindow.getWidth() - gameOverTexture.getWidth())/2, 75, gameOverWindow.showRenderer());
	coinCollectedTexture.render( (gameOverWindow.getWidth() - coinCollectedTexture.getWidth())/2, 140, gameOverWindow.showRenderer());
	timeSurvivedTexture.render( (gameOverWindow.getWidth() - timeSurvivedTexture.getWidth())/2, 180, gameOverWindow.showRenderer());
	bulletFiredTexture.render( (gameOverWindow.getWidth() - bulletFiredTexture.getWidth())/2, 220, gameOverWindow.showRenderer());
	enemyKilledTexture.render( (gameOverWindow.getWidth() - enemyKilledTexture.getWidth())/2, 260, gameOverWindow.showRenderer());
	bossKilledTexture.render( (gameOverWindow.getWidth() - bossKilledTexture.getWidth())/2, 300, gameOverWindow.showRenderer());
	restartTexture.render( (gameOverWindow.getWidth() - restartTexture.getWidth())/2,
						   gameOverWindow.getHeight() - restartTexture.getHeight() - 20, gameOverWindow.showRenderer());
}


void ShowWindow::showWinnerWindow(Player &player, LTimer &time){
	gameWinnerWindow.render();
	
	LTexture gameOverTexture;
	LTexture coinCollectedTexture;
	LTexture timeSurvivedTexture;
	LTexture bulletFiredTexture;
	LTexture enemyKilledTexture;
	LTexture bossKilledTexture;
	LTexture restartTexture;
	
	SDL_Color textColor = { 255, 255, 255, 255};
	
	std::stringstream gameOverText;
	std::stringstream coinCollectedText;
	std::stringstream timeSurvivedText;
	std::stringstream bulletFiredText;
	std::stringstream enemyKilledText;
	std::stringstream bossKilledText;
	std::stringstream restartText;
	
	gameOverText.str( "" );
	gameOverText << "You win this game! Congrats!!";
	coinCollectedText.str( "" );
	coinCollectedText << "Coin Collected: " << player.getSkill().show_coins();
	timeSurvivedText.str( "" );
	timeSurvivedText << "Time Survived: " << (time.getTicks()/1000.0) << " seconds";
	bulletFiredText.str( "" );
	bulletFiredText << "Bullet Fired: " << player.getBulletFired();
	enemyKilledText.str( "" );
	enemyKilledText<< "Enemy Killed: " << player.getEnemyKilled();
	bossKilledText.str( "" );
	bossKilledText << "Boss Killed: " << player.getBossKilled();
	restartText.str( "" );
	restartText << "Press SPACE to Play the game again!.";
		
	gameOverTexture.loadFromRenderedText(gFont36, gameOverText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	coinCollectedTexture.loadFromRenderedText(gFont28, coinCollectedText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	timeSurvivedTexture.loadFromRenderedText(gFont28, timeSurvivedText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	bulletFiredTexture.loadFromRenderedText(gFont28, bulletFiredText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	enemyKilledTexture.loadFromRenderedText(gFont28, enemyKilledText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	bossKilledTexture.loadFromRenderedText(gFont28, bossKilledText.str().c_str(), textColor, gameWinnerWindow.showRenderer());
	restartTexture.loadFromRenderedText(gFont16, restartText.str().c_str(), textColor, gameWinnerWindow.showRenderer());	

	gameOverTexture.render( (gameWinnerWindow.getWidth() - gameOverTexture.getWidth())/2, 75, gameWinnerWindow.showRenderer());
	coinCollectedTexture.render( (gameWinnerWindow.getWidth() - coinCollectedTexture.getWidth())/2, 140, gameWinnerWindow.showRenderer());
	timeSurvivedTexture.render( (gameWinnerWindow.getWidth() - timeSurvivedTexture.getWidth())/2, 180, gameWinnerWindow.showRenderer());
	bulletFiredTexture.render( (gameWinnerWindow.getWidth() - bulletFiredTexture.getWidth())/2, 220, gameWinnerWindow.showRenderer());
	enemyKilledTexture.render( (gameWinnerWindow.getWidth() - enemyKilledTexture.getWidth())/2, 260, gameWinnerWindow.showRenderer());
	bossKilledTexture.render( (gameWinnerWindow.getWidth() - bossKilledTexture.getWidth())/2, 300, gameWinnerWindow.showRenderer());
	restartTexture.render( (gameWinnerWindow.getWidth() - restartTexture.getWidth())/2,
						   gameWinnerWindow.getHeight() - restartTexture.getHeight() - 20, gameWinnerWindow.showRenderer());
}

void ShowWindow::showGameWindow(Player& player, LTimer& timer){
	gameWindow.render();
	
	std::stringstream timeText;		//In memory text stream
	std::stringstream HPText;
	std::stringstream coinsText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as black
	
	//Set text to be rendered
	timeText.str( "" );
	timeText << ( timer.getTicks() / 1000.f ) << "/300 sec" ; 
	HPText.str("");
	HPText << "HP: " << player.show_current_HP() << "/" << player.show_total_HP();
	coinsText.str( "" );
	coinsText << "coins: " << player.getSkill().show_coins();

	//Render text
	gTimeTextTexture.loadFromRenderedText(gFont28, timeText.str().c_str(), textColor, gameWindow.showRenderer());
	gHPTextTexture.loadFromRenderedText(gFont28, HPText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.loadFromRenderedText(gFont28, coinsText.str().c_str(), textColor, gameWindow.showRenderer());
				
	gTimeTextTexture.render(0, 0, gameWindow.showRenderer());
	gHPTextTexture.render(gameWindow.getWidth() - gHPTextTexture.getWidth(), 0, gameWindow.showRenderer());
	gcoinsTextTexture.render(gameWindow.getWidth() - gcoinsTextTexture.getWidth(), gHPTextTexture.getHeight(), gameWindow.showRenderer());
}

void ShowWindow::showPauseWindow(){
	pauseWindow.render();
	
	std::stringstream pauseText;
	std::stringstream soundText;
	SDL_Color textColor = { 255, 255, 255, 255};
	
	pauseText.str( "" );
	pauseText << "Pause";
	soundText.str( "" );
	soundText << "Sound";

	gPauseTextTexture.loadFromRenderedText(gFont28, pauseText.str().c_str(), textColor, pauseWindow.showRenderer());
	gSoundTextTexture.loadFromRenderedText(gFont28, soundText.str().c_str(), textColor, pauseWindow.showRenderer());
	gPauseTextTexture.render((SCREEN_WIDTH - gPauseTextTexture.getWidth())/2, 100, pauseWindow.showRenderer());
	gSoundTextTexture.render((SCREEN_WIDTH - gSoundTextTexture.getWidth())/2, 120+gPauseTextTexture.getHeight(), pauseWindow.showRenderer());
	
	SDL_RenderPresent( pauseWindow.showRenderer() );
}

void ShowWindow::showStartWindow(){
	StartWindow.render();
	LTexture nameTexture;
	LTexture titleTexture;
	LTexture ruleTexture;
	LTexture ruleTexture2;
	LTexture ruleTexture3;
	LTexture ruleTexture4;
	LTexture ruleTexture5;
	LTexture ruleTexture6;
	std::stringstream nameText;
	std::stringstream titleText;
	std::stringstream ruleText;
	std::stringstream ruleText2;
	std::stringstream ruleText3;
	std::stringstream ruleText4;
	std::stringstream ruleText5;
	std::stringstream ruleText6;
	SDL_Color textColor = { 255, 255, 255, 255};
	SDL_Color TitleColor = { 200, 45, 214, 255};
	SDL_Color nameColor = { 89, 181, 177, 255};
	titleText.str( "" );
	nameText << "b10703049 B10202010 B12901122 Final Project";	
	titleText.str( "" );
	titleText << "d(OuO)b [WindowsKill Game] d(OuO)b";
	ruleText.str( "" );
	ruleText << "Press Space to start, Use WASD to move";
	ruleText2.str( "" );
	ruleText2 << "Press Space to view the Upgrade interface";
	ruleText3.str( "" );
	ruleText3 << "Press ESC to pause and set the volumn";
	ruleText4.str( "" );
	ruleText4 << "Your goal is to survive for 300 seconds.";
	ruleText5.str( "" );
	ruleText5 << "Dodge the enemy and bullets! Good luck.";
	ruleText6.str( "" );
	ruleText6 << "Please use the English keyboard to play the game. (press shift)";
	nameTexture.loadFromRenderedText(gFont28, nameText.str().c_str(), nameColor, StartWindow.showRenderer());
	titleTexture.loadFromRenderedText(gFont36, titleText.str().c_str(), TitleColor, StartWindow.showRenderer());
	ruleTexture.loadFromRenderedText(gFont28, ruleText.str().c_str(), textColor, StartWindow.showRenderer());
	ruleTexture2.loadFromRenderedText(gFont28, ruleText2.str().c_str(), textColor, StartWindow.showRenderer());
	ruleTexture3.loadFromRenderedText(gFont28, ruleText3.str().c_str(), textColor, StartWindow.showRenderer());
	ruleTexture4.loadFromRenderedText(gFont28, ruleText4.str().c_str(), textColor, StartWindow.showRenderer());
	ruleTexture5.loadFromRenderedText(gFont28, ruleText5.str().c_str(), textColor, StartWindow.showRenderer());
	ruleTexture6.loadFromRenderedText(gFont16, ruleText6.str().c_str(), textColor, StartWindow.showRenderer());
	nameTexture.render((StartWindow.getWidth() - nameTexture.getWidth())/2, 150, StartWindow.showRenderer());
	titleTexture.render((StartWindow.getWidth() - titleTexture.getWidth())/2, 70, StartWindow.showRenderer());
	ruleTexture.render((StartWindow.getWidth() - ruleTexture.getWidth())/2, 200, StartWindow.showRenderer());
	ruleTexture2.render((StartWindow.getWidth() - ruleTexture2.getWidth())/2, 250, StartWindow.showRenderer());
	ruleTexture3.render((StartWindow.getWidth() - ruleTexture3.getWidth())/2, 300, StartWindow.showRenderer());
	ruleTexture4.render((StartWindow.getWidth() - ruleTexture4.getWidth())/2, 350, StartWindow.showRenderer());
	ruleTexture5.render((StartWindow.getWidth() - ruleTexture5.getWidth())/2, 400, StartWindow.showRenderer());
	ruleTexture6.render((StartWindow.getWidth() - ruleTexture6.getWidth())/2, 450, StartWindow.showRenderer());
	SDL_RenderPresent( StartWindow.showRenderer());
}


void ShowWindow::showSkillTreeWindow(SDL_Event& e, Player& player) {
    for (auto& button : buttons) {
        button.handleEvent(e, player, player.getSkill());
    }

    skillTreeWindow.render();
    for (const auto& button : buttons) {
        button.render();
    }
    
    if(showType != 0){
    	if (SDL_GetTicks() - showTime >= 1000)	showType = 0;
    	switch(showType){
    		case 1:
    			this->ReachMaxLevel();
    			break;
    		case 2:
    			this->NoMoney();
    			break;
    		case 3:
    			this->UpdateSuccess();
    			break;
		}
	}

    std::stringstream coinsText;
    SDL_Color textColor = {255, 255, 255, 255}; // Set text color as white
    coinsText.str("");
    coinsText << "coins: " << player.getSkill().show_coins();
    gcoinsTextTexture.loadFromRenderedText(gFont28, coinsText.str().c_str(), textColor, skillTreeWindow.showRenderer());
    gcoinsTextTexture.render(skillTreeWindow.getWidth() - gcoinsTextTexture.getWidth() - 10, 0, skillTreeWindow.showRenderer());
    SDL_RenderPresent(skillTreeWindow.showRenderer());
}

void ShowWindow::ReachMaxLevel(){
	std::stringstream MaxLevelText;	
	SDL_Color textColor = { 0, 255, 0, 255};	//Set text color as white
	MaxLevelText.str( "" );
	MaxLevelText << "You have reached maximum level!" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, MaxLevelText.str().c_str(), textColor, skillTreeWindow.showRenderer());
	gcoinsTextTexture.render(125, 230, skillTreeWindow.showRenderer());
	SDL_RenderPresent(skillTreeWindow.showRenderer());
}

void ShowWindow::NoMoney(){
	std::stringstream NoMoneyText;	
	SDL_Color textColor = { 130, 230, 0, 255};
	NoMoneyText.str( "" );
	NoMoneyText << "You have not enough money!" ;
	gcoinsTextTexture.loadFromRenderedText(gFont36, NoMoneyText.str().c_str(), textColor, skillTreeWindow.showRenderer());
	gcoinsTextTexture.render(130, 230, skillTreeWindow.showRenderer());
	SDL_RenderPresent(skillTreeWindow.showRenderer());
}

void ShowWindow::UpdateSuccess(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 0, 255, 0, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Update Successfully! Congrats." ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, skillTreeWindow.showRenderer());
	gcoinsTextTexture.render(140, 230, skillTreeWindow.showRenderer());
	SDL_RenderPresent(skillTreeWindow.showRenderer());
}

void ShowWindow::Shouldupdate(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Press Space to Update skills" ;
	gcoinsTextTexture.loadFromRenderedText(gFont16, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}
void ShowWindow::grade1(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 1" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade2(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 2" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade3(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 3" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade4(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 4" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade5(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 5" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade6(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 6" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::grade7(){
	std::stringstream UpdateText;	
	SDL_Color textColor = { 255, 255, 255, 255};	//Set text color as white
	UpdateText.str( "" );
	UpdateText << "Level 7" ;
	gcoinsTextTexture.loadFromRenderedText(gFont28, UpdateText.str().c_str(), textColor, gameWindow.showRenderer());
	gcoinsTextTexture.render((gameWindow.getWidth() - gcoinsTextTexture.getWidth())/2, gameWindow.getHeight()*(0.9), gameWindow.showRenderer());
}

void ShowWindow::setValue(int i){
	showType = i;
	showTime = SDL_GetTicks();
}