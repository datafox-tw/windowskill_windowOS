#ifndef SKILL_H
#define SKILL_H
#include "SDL2/SDL.h"
class Player;
class ShowWindow;
class CollisionManager;
class Enemy;
class Skill {

private:
    int coins = 0;
	int coinCollected = 0;
	int enemyCoin = 2;
	int eliteEnemyCoin = 5;
	int eliteEnemy2Coin = 5;
	int eliteEnemy3Coin = 1;
	
	//speed
	int speedLevel = 0;
	int speedTable[4] = {5, 6, 7, 8};
	int speedCost[3] = {10, 30, 50};
	
	//wealth
	int wealthLevel = 0;
	int wealthTable[7] = {1,1,1,1,2,2,3};
	int wealthCost[6] = {15,30,45,60,75,100};	
	
	int freezeLevel = 0;
	double freezeTable[6] = {1, 0.90, 0.80,0.70,0.60,0.50};
	int freezeCost[5] = {21,44,69,91,123};
	
	//bounce
	int bounceLevel = 0;
	int bounceCost = 70;
	
	//multi shot
	int multiShotLevel = 0;
	int multiShotCost[2] = {30, 90};
	
	//fire rate
	int fireRateLevel = 0;
	Uint32 fireRateTable[7] = {450, 400, 350, 300, 250, 200, 150};
	int fireRateCost[6] = {15, 30, 45, 60, 80, 100};
	
	//max health
	int maxHPLevel = 0;
	int maxHPTable[5] = {30, 40, 50, 70, 100};
	int maxHPCost[4] = {25, 50, 80, 120};
	
	int refuellevel = 0;
	int refuelCost[15] = {10,20,30,40,50,60,70,80,90,100,100,100,100,100,100};
	
public:
	Skill();
	~Skill();
	
    void add_coins(int add);
    void cost_coins(int cost);
    int show_coins();
    int show_coinCollected();
    int getEnemyCoin()	{return enemyCoin;}
    int getEliteEnemyCoin()	{return eliteEnemyCoin;}
    int getEliteEnemy2Coin()	{return eliteEnemy2Coin;}
    int getEliteEnemy3Coin()	{return eliteEnemy3Coin;}
    int getMultiShotLevel()	{return multiShotLevel;}
    int getSpeedLevel()		{return speedLevel;}
    int getFreezeLevel()	{return freezeLevel;}
    int getWealthLevel()	{return wealthLevel;}
    int getBounceLevel()	{return bounceLevel;}
    int getFireRateLevel()	{return fireRateLevel;}
    int getMaxHPLevel()		{return maxHPLevel;}
    int getrefuelLevel()	{return refuellevel;}
    
    int getSpeedCost()		{return speedCost[speedLevel];}
    int getFreezeCost()		{return freezeCost[freezeLevel];}
    int getWealthCost()		{return wealthCost[wealthLevel];}
    int getMultiShotCost()	{return multiShotCost[multiShotLevel];}
    int getBounceCost()		{return bounceCost;}
	int getFireRateCost()	{return fireRateCost[fireRateLevel];}
    int getMaxHPCost()		{return maxHPCost[maxHPLevel];}
    int getrefuelCost()		{return refuelCost[refuellevel];}
    
    double getFreeze()	{return freezeTable[freezeLevel];}
    
    void speedUpgrade(Player& player, ShowWindow& showWindow);
    void wealthUpgrade(Player& player, ShowWindow& showWindow);
    void freezeUpgrade(ShowWindow& showWindow);
    void bounceUpgrade(Player& player, ShowWindow& showWindow);
    void multiShotUpgrade(Player& player, ShowWindow& showWindow);
    void maxHPUpgrade(Player& player, ShowWindow& showWindow);
    void refuel(Player& player, ShowWindow& showWindow);
    void fireRateUpgrade(Player& player, ShowWindow& showWindow);

    void restart();
};

#endif // SKILL_H
