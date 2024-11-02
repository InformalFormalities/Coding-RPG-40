#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

struct Character {
	std::string name;
	//By default character is alive.
	bool isAlive = true;
	//Can't go above 100 health.
	const int MAX_HEALTH = 100;
	//Can't go under 0 health.
	const int MIN_HEALTH = 0;
	//Default to a healthy 100 health.
	int health = 100;
	//attackPwr is defined as how many HP points they hit for.
	int attackPwr = 35;
	//defense is defined as how much damage is mitigated per attack.
	//If attackPwr is 25, and defense is 10, then you are only hit for 15 hp as opposed to a normal 25.
	int defense = 10;
	//fortifyAmount is defined as how much health you regain while fortifying.
	int fortifyAmount = 10;
	//Player's balance is in terms of gold coins.
	int balance = 0;
	//Number of health potions player has (by default 3).
	int healthPotions = 3;
	//How much a health potion heals for.
	const int POTION_HEAL_AMOUNT = 30;
};

#endif
