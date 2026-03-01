
#pragma once
#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H
#include <vector>
#include "player.h"
#include "Skill.h"
#include "timer.h"
#include "window.h"
#include "enemy.h"
#include "timer.h"
#include "texture.h"
#include "SDL2/SDL.h"
#include "basicbutton.h"
class ShowWindow {
public:
	ShowWindow();
	~ShowWindow();
	const std::vector<Button>& getButtons() const {return buttons;}
	void addButton(const Button& button) {buttons.push_back(button);}
	void restart(Player &player, LTimer &time, Window &window, EnemyManager &enemyManager);
	void showGameOverWindow(Player &player, LTimer &time);
	void showWinnerWindow(Player &player, LTimer &time);
	void showGameWindow(Player& player, LTimer& timer);
	void showPauseWindow();
	void showStartWindow();
	void grade1();
	void grade2();
	void grade3();
	void grade4();
	void grade5();
	void grade6();
	void grade7();
	void showSkillTreeWindow(SDL_Event& e, Player& player);

	void Shouldupdate();
	void setValue(int i);
protected:
	std::vector<Button> buttons;
	int showType = 0;
	Uint32 showTime = 0;
	void ReachMaxLevel(); // type 1
	void NoMoney();	// type 2
	void UpdateSuccess();	// type 3
};
#endif