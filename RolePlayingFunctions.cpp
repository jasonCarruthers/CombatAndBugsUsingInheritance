#include <iostream>
#include <string>
#include "windows.h"
#include "RolePlaying.h"
using namespace std;


std::string SpeciesName[ Num__SpeciesTypes ] =
{
	"Human",
	"Elf",
	"Cyberdemon",
	"Balrog",
};


//Creature class functions
Creature::Creature(int newType, int newStrength, int newHitPoints)
{
	mType = newType;
	mStrength = newStrength;
	mHitPoints = newHitPoints;
}

int Creature::GetStrength() const
{
	return mStrength;
}

int Creature::GetHitPoints() const
{
	return mHitPoints;
}

void Creature::SetHitPoints(int newHitPoints)
{
	mHitPoints = newHitPoints;
}

std::string Creature::GetSpecies() const
{
	return SpeciesName[ mType ];
}

int Creature::GetDamage() const
{
	return 1 + rand() % mStrength;
}



/*
	- Every creature inflicts random damage, 0 < r <= strength
	- Elves: 10% chance of 2x damage
	- Demons: 5% chance of +50 damage
	- Balrogs: 2 attacks
*/

//Human class functions
Human::Human(int newStrength, int newHitPoints)
{
	mType = Species_Human;
	mStrength = newStrength;
	mHitPoints = newHitPoints;
}

int Human::GetDamage() const
{
	return Creature::GetDamage();
}


//Elf class functions
Elf::Elf(int newStrength, int newHitPoints)
{
	mType = Species_Elf;
	mStrength = newStrength;
	mHitPoints = newHitPoints;
}

int Elf::GetDamage() const
{
	int damage = Creature::GetDamage();
	return (1 + (rand() % 100) <= 10) ? damage * 2 : damage;
}


//Demon class functions
Demon::Demon(int newStrength, int newHitPoints)
{
	mStrength = newStrength;
	mHitPoints = newHitPoints;
}

int Demon::GetDamage() const
{
	int damage = Creature::GetDamage();
	return (1 + (rand() % 100) <= 5) ? damage + 50 : damage;
}

//Cyberdemon class functions
Cyberdemon::Cyberdemon()
{
	mType = Species_Cyberdemon;
}

int Cyberdemon::GetDamage() const
{
	return Demon::GetDamage();
}

//Balrog class functions
Balrog::Balrog()
{
	mType = Species_Balrog;
}

int Balrog::GetDamage() const
{
	return Demon::GetDamage() + Demon::GetDamage();
}