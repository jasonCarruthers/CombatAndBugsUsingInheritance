#include <iostream>
#include "windows.h"
#include "GeneralUse.h"
#include "PredatorPrey.h"
#include "Map.h"
using namespace std;






//Organism class functions
Organism::Organism(int x, int y)
{
	mX = x;
	mY = y;
	mNumTimeSteps = 0;
	mNumStarvedTimeSteps = 0;
	mHasMovedThisTurn = true;
	mType = CellType_Empty;
}

int Organism::GetX() const
{
	return mX;
}

int Organism::GetY() const
{
	return mY;
}

CellType Organism::GetType() const
{
	return mType;
}

void Organism::SetMoveState(bool hasMoved)
{
	mHasMovedThisTurn = hasMoved;
}

void Organism::SetNumTimeSteps(int numTimeSteps)
{
	mNumTimeSteps = numTimeSteps;
}

int Organism::GetNumStarvedTimeSteps() const
{
	return mNumStarvedTimeSteps;
}

void Organism::SetNumStarvedTimeSteps(int numStarvedTimeSteps)
{
	mNumStarvedTimeSteps = numStarvedTimeSteps;
}

void Organism::Move(World &world)
{
/*
all organisms move randomly, but
the predators move to an adjacent cell containing prey if one exists
*/
	mNumTimeSteps++;

	Coordinates newLoc = world.GetAdjacentRand(mX, mY, CellType_Empty);
	if( world.GetCellType(newLoc.GetX(), newLoc.GetY()) == CellType_Empty )
	{
		if( !world.IsInBounds(newLoc.GetX(), newLoc.GetY()) )
			assert(false);

		world.FillCell(newLoc.GetX(), newLoc.GetY(), mType);
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->mHasMovedThisTurn = mHasMovedThisTurn;
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->mNumTimeSteps = mNumTimeSteps;

		world.FillCell(mX, mY, CellType_Empty);	
	}
}

void Organism::Reproduce(World &world)
{
/*
choose a random adjacent cell until an empty one is found,
then create a new Organism of like-type in that cell
then SetTimeSteps( 0 );
*/
	mNumTimeSteps = 0;

	Coordinates spawnLoc = world.GetAdjacentRand( mX, mY, CellType_Empty );
	if( world.GetCellType(spawnLoc.GetX(), spawnLoc.GetY()) == CellType_Empty )
		/*if successful reproduction, do this block of code*/
	{
		world.FillCell(spawnLoc.GetX(), spawnLoc.GetY(), mType);
	}
}

void Organism::ReproductionPhase(World &world)
{
	if(mNumTimeSteps == 20)
		Reproduce(world);
}

void Organism::Update(World &world)
{
	mHasMovedThisTurn = false;
	ReproductionPhase(world);
	Move(world);
	mHasMovedThisTurn = true;
}

void Organism::Draw() const
{
	Cursor cursor;
	cursor.SetLocation( mX, mY );
	cout << "#";
}

bool Organism::operator==(const Organism &right) const
{
	return ( mX == right.mX && mY == right.mY );
}


//Prey class functions
Prey::Prey(int x, int y)
{
	mX = x;
	mY = y;
	mType = CellType_Prey;
}

void Prey::Move(World &world)
{
	Organism::Move(world);
}

void Prey::ReproductionPhase(World &world)
{
	if( mNumTimeSteps > 3 )
		assert(false);

	if( mNumTimeSteps == 3 )
		Reproduce(world);
}
//
//void Prey::Update(World &world)
//{
//	Organism::Update(world);
//}

void Prey::Draw() const
{
	Cursor cursor;
	cursor.SetLocation( mX, mY );
					
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << "a";
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}



//Predator class functions
Predator::Predator(int x, int y)
{
	mX = x;
	mY = y;
	mType = CellType_Predator;
}

void Predator::Move(World &world)
{
/*
check for adjacent prey, if any exists eat that prey
if not, call the base class's Move() function
*/
	mNumStarvedTimeSteps++;

	int numStarvedTimeSteps = mNumStarvedTimeSteps;
	Coordinates newLoc = world.GetAdjacentRand(mX, mY, CellType_Prey);

	if( world.GetCellType(newLoc.GetX(), newLoc.GetY()) == CellType_Prey )
	{
		assert( world.IsInBounds(newLoc.GetX(), newLoc.GetY()) );

		mNumTimeSteps++;
		mNumStarvedTimeSteps = 0;
		world.FillCell(newLoc.GetX(), newLoc.GetY(), CellType_Predator);
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->SetMoveState( mHasMovedThisTurn );
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->SetNumTimeSteps( mNumTimeSteps );
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->SetNumStarvedTimeSteps( mNumStarvedTimeSteps );

		world.FillCell(mX, mY, CellType_Empty);
	}
	else
	{
		Organism::Move(world);
		newLoc = world.GetAdjacentRand(mX, mY, CellType_Predator);
		world.mArr[newLoc.GetY()*World::WIDTH + newLoc.GetX()]->SetNumStarvedTimeSteps( numStarvedTimeSteps );
	}
}

void Predator::ReproductionPhase(World &world)
{
	if( mNumTimeSteps == 8 )
		Reproduce(world);
}

void Predator::Update(World &world)
{
	Organism::Update(world);

	Coordinates actualLoc = world.GetAdjacentRand(mX, mY, CellType_Predator);
	if( world.mArr[actualLoc.GetY()*World::WIDTH + actualLoc.GetX()]->GetNumStarvedTimeSteps() > 3 )
		world.FillCell(actualLoc.GetX(), actualLoc.GetY(), CellType_Empty);
}

void Predator::Draw() const
{
	Cursor cursor;
	cursor.SetLocation( mX, mY );

	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY );
	cout << "X";
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}