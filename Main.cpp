//Programmer: Jason Carruthers

//Ch. 14: problem 9
//Ch. 15: problems 3, 4


#include <iostream>
#include <ctime>
#include <string>
#include "windows.h"
#include "GeneralUse.h"
#include "PredatorPrey.h"
#include "Map.h"
#include "RolePlaying.h"
using namespace std;


void TestCreatureInitialization();
Creature* GetRandSpecies();
void TestCreatureCombat();
void TestPredatorPreySimulation();


int main()
{
	srand(static_cast<int>(time(0)));

	TestCreatureInitialization();
	for(int i = 0; i < 5; i++)
		TestCreatureCombat();

	TestPredatorPreySimulation();

	system("pause");
	return 0;
}

void TestCreatureInitialization()
{
	Human human;
	Elf elf;
	Cyberdemon cyberdemon;
	Balrog balrog;

	cout << "Species' stats:\n\n";
	cout << human.GetSpecies() << ":\t\t" << "hit points " << human.GetHitPoints() << "\t" << " strength: " << human.GetStrength() << "\n";
	cout << elf.GetSpecies() << ":\t\t" << "hit points " << elf.GetHitPoints() << "\t" << " strength: " << elf.GetStrength() << "\n";
	cout << cyberdemon.GetSpecies() << ":\t" << "hit points " << cyberdemon.GetHitPoints() << "\t" << " strength: " << cyberdemon.GetStrength() << "\n";
	cout << balrog.GetSpecies() << ":\t\t" << "hit points " << balrog.GetHitPoints() << "\t" << " strength: " << balrog.GetStrength() << "\n";
	system("pause");
	cout << "\n\n";

	for(int i = 0; i < 10; i++)
	{
		cout << human.GetSpecies() << " has " << human.GetStrength() << " strength, does " << human.GetDamage() << " damage." << "\n";
		cout << elf.GetSpecies() << " has " << elf.GetStrength() << " strength, does " << elf.GetDamage() << " damage." << "\n";
		cout << cyberdemon.GetSpecies() << " has " << cyberdemon.GetStrength() << " strength, does " << cyberdemon.GetDamage() << " damage." << "\n";
		cout << balrog.GetSpecies() << " has " << balrog.GetStrength() << " strength, does " << balrog.GetDamage() << " damage." << "\n";
		system("pause");
		cout << "\n\n";
	}
}

Creature* GetRandSpecies()
{
	int species = rand() % Num__SpeciesTypes;

	switch( species )
	{
	case Species_Human:			return new Human();
	case Species_Elf:			return new Elf();
	case Species_Cyberdemon:	return new Cyberdemon();
	case Species_Balrog:		return new Balrog();
	default:					break;
	}

	assert(false);
	return new Human();
}

void TestCreatureCombat()
{
	//create two different creatures
	Creature* creatureArr[2];
	creatureArr[0] = GetRandSpecies();
	creatureArr[1] = GetRandSpecies();
	cout << creatureArr[0]->GetSpecies() << " (creature[0]) has " << creatureArr[0]->GetHitPoints() <<
			" hit points and has " << creatureArr[0]->GetStrength() << " strength!" << "\n";
	cout << creatureArr[1]->GetSpecies() << " (creature[1]) has " << creatureArr[1]->GetHitPoints() <<
			" hit points and has " << creatureArr[1]->GetStrength() << " strength!" << "\n\n";

	//combat
	int i = 0;
	int damage = 0;
	while( creatureArr[0]->GetHitPoints() > 0 && creatureArr[1]->GetHitPoints() > 0 )
	{
		cout << creatureArr[i]->GetSpecies() << "'s turn! (creatureArr[" << i << "])" << "\n";

		damage = creatureArr[i]->GetDamage();
		creatureArr[(i + 1) % 2]->SetHitPoints( creatureArr[(i + 1) % 2]->GetHitPoints() - damage );

		cout << creatureArr[i]->GetSpecies() << " does " << damage << " damage to " <<
				creatureArr[(i + 1) % 2]->GetSpecies() << "!" << "\n";
		cout << creatureArr[(i + 1) % 2]->GetSpecies() << " now has " <<
				creatureArr[(i + 1) % 2]->GetHitPoints() << " hit points left!" << "\n\n";
		
		i = (i + 1) % 2;
	}

	cout << creatureArr[(i + 1) % 2]->GetSpecies() << " is the victor with " <<
			creatureArr[(i + 1) % 2]->GetHitPoints() << " hit points remaining." << "\n";
	cout << creatureArr[i]->GetSpecies() << " is the loser with " <<
			creatureArr[i]->GetHitPoints() << " hit points remaining." << "\n";

	system("pause");
	system("cls");
}

void TestPredatorPreySimulation()
{
	//starting amount of predators and prey
	const int NUM_STARTING_PREY = 100;
	const int NUM_STARTING_PREDATORS = 10;

	//init world
	World world;
	world.Populate(CellType_Prey, NUM_STARTING_PREY);
	world.Populate(CellType_Predator, NUM_STARTING_PREDATORS);

	//-----------------
	//THE GAME
	//-----------------
	Cursor cursor;
	while( true )
	{
		for(int x = 0; x < World::WIDTH; x++)
		{
			for(int y = 0; y < World::HEIGHT; y++)
			{
				//draw world and world object
				world.Draw(x, y);

				//update objects in world
				if( world.GetCellType(x, y) != CellType_Empty )
					world.mArr[y*World::WIDTH + x]->Update(world);
			}
		}
		//cursor.SetLocation(0, World::WIDTH);
		//system("pause");
	}
}