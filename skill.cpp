#include <iostream>

#include "CollisionManager.h"
#include "ShowWindow.h"
#include "Skill.h"
#include "player.h"
using namespace std;
Skill::Skill() {}
Skill::~Skill() {}

void Skill::add_coins(int add) {
  coins += add;
  coinCollected += add;
}

void Skill::cost_coins(int cost) { coins -= cost; }
int Skill::show_coins() { return coins; }
int Skill::show_coinCollected() { return coinCollected; }

void Skill::speedUpgrade(Player& player, ShowWindow& showWindow) {
  if (speedLevel < 3 && coins >= speedCost[speedLevel]) {
    coins -= speedCost[speedLevel];
    speedLevel++;
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], player.show_current_HP(),
                    multiShotLevel, bounceLevel);
    showWindow.setValue(3);
  } else if (speedLevel == 3)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}
void Skill::wealthUpgrade(Player& player, ShowWindow& showWindow) {
  if (wealthLevel < 7 && coins >= wealthCost[wealthLevel]) {
    cost_coins(wealthCost[wealthLevel]);
    wealthLevel++;
    enemyCoin += (wealthTable[wealthLevel]);
    eliteEnemyCoin += (wealthTable[wealthLevel]);
    eliteEnemy2Coin += (wealthTable[wealthLevel]);
    eliteEnemy3Coin += (wealthTable[wealthLevel]);
    showWindow.setValue(3);
  } else if (wealthLevel == 7)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}

void Skill::freezeUpgrade(ShowWindow& showWindow) {
  if (freezeLevel < 5 && coins >= freezeCost[freezeLevel]) {
    coins -= freezeCost[freezeLevel];
    freezeLevel++;
    showWindow.setValue(3);
  } else if (freezeLevel == 5)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}

void Skill::bounceUpgrade(Player& player, ShowWindow& showWindow) {
  if (bounceLevel == 0 && coins >= bounceCost) {
    bounceLevel++;
    showWindow.setValue(3);
    cost_coins(70);
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], player.show_current_HP(),
                    multiShotLevel, bounceLevel);
  } else if (bounceLevel == 1)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}

void Skill::fireRateUpgrade(Player& player, ShowWindow& showWindow) {
  if (fireRateLevel < 6 && coins >= fireRateCost[fireRateLevel]) {
    cost_coins(fireRateCost[fireRateLevel]);
    fireRateLevel++;
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], player.show_current_HP(),
                    multiShotLevel, bounceLevel);
    showWindow.setValue(3);
  } else if (fireRateLevel == 6)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}

void Skill::multiShotUpgrade(Player& player, ShowWindow& showWindow) {
  if (multiShotLevel < 2 && coins >= multiShotCost[multiShotLevel]) {
    coins -= multiShotCost[multiShotLevel];
    multiShotLevel++;
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], player.show_current_HP(),
                    multiShotLevel, bounceLevel);
    showWindow.setValue(3);
  } else if (multiShotLevel == 2)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}
void Skill::maxHPUpgrade(Player& player, ShowWindow& showWindow) {
  if (maxHPLevel < 4 && coins >= maxHPCost[maxHPLevel]) {
    coins -= maxHPCost[maxHPLevel];
    maxHPLevel++;
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], 5 + player.show_current_HP(),
                    multiShotLevel, bounceLevel);
    showWindow.setValue(3);
  } else if (maxHPLevel == 4)
    showWindow.setValue(1);
  else
    showWindow.setValue(2);
}

void Skill::refuel(Player& player, ShowWindow& showWindow) {
  if (coins >= refuelCost[refuellevel]) {
    coins -= refuelCost[refuellevel];
    if (refuellevel < 9) refuellevel++;
    player.setValue(speedTable[speedLevel], fireRateTable[fireRateLevel],
                    maxHPTable[maxHPLevel], maxHPTable[maxHPLevel],
                    multiShotLevel, bounceLevel);
    showWindow.setValue(3);
  } else
    showWindow.setValue(2);
}

void Skill::restart() {
  coins = 0;
  coinCollected = 0;
  enemyCoin = 2;
  eliteEnemyCoin = 5;
  eliteEnemy2Coin = 8;
  eliteEnemy3Coin = 20;

  speedLevel = 0;
  freezeLevel = 0;
  bounceLevel = 0;
  fireRateLevel = 0;
  multiShotLevel = 0;
  maxHPLevel = 0;
  wealthLevel = 0;
}