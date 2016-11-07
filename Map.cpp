#include <iostream>
#include <cassert>
#include "windows.h"
#include "GeneralUse.h"
#include "PredatorPrey.h"
#include "Map.h"
using namespace std;




World::World()
{
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			mArr[y*WIDTH + x] = NULL;
}

CellType World::GetCellType(int x, int y) const
{
	return (mArr[ (y*WIDTH) + x ] == NULL) ? CellType_Empty : mArr[ (y*WIDTH) + x ]->GetType();
}

void World::FillCell(int x, int y, CellType organismType)
{
	switch( organismType )
	{
	case CellType_Empty:	mArr[y*WIDTH + x] = NULL;
							break;

	case CellType_Prey:		if(mArr[y*WIDTH + x] != NULL)
								delete mArr[y*WIDTH + x];
							mArr[y*WIDTH + x] = new Prey(x, y);
							break;

	case CellType_Predator:	if(mArr[y*WIDTH + x] != NULL)
								delete mArr[y*WIDTH + x];
							mArr[y*WIDTH + x] = new Predator(x, y);
							break;
	default:
		assert(false);
	}
}

void World::Populate(CellType organismType, int num)
{
	Coordinates spawnLoc;

	int i = 0;
	while( i < num )
	{
		spawnLoc = Coordinates(rand() % WIDTH, rand() % HEIGHT);
		if( GetCellType(spawnLoc.GetX(), spawnLoc.GetY()) == CellType_Empty )
		{
			FillCell(spawnLoc.GetX(), spawnLoc.GetY(), organismType);
			i++;
		}
	}
}

bool World::IsInBounds(int x, int y) const
{
	return ( x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT );
}

Coordinates World::GetAdjacentRand(int originX, int originY, CellType seekType) const
{
	Coordinates searchLoc;

	bool isDirChecked[Num__CardinalDirections] = {false, false, false, false};

	while(	isDirChecked[ CardinalDirection_North ] == false ||
			isDirChecked[ CardinalDirection_East ] == false ||
			isDirChecked[ CardinalDirection_South ] == false ||
			isDirChecked[ CardinalDirection_West ] == false )
	{
		int dir = rand() % Num__CardinalDirections;
		if( !isDirChecked[dir] )
		{
			isDirChecked[ dir ] = true;

			searchLoc = Coordinates(originX + directionChange[ dir ].GetX(),
							originY + directionChange[ dir ].GetY());
			if( IsInBounds(searchLoc.GetX(), searchLoc.GetY()) &&
				GetCellType(searchLoc.GetX(), searchLoc.GetY()) == seekType )
				return searchLoc;
		}
	}

	searchLoc = Coordinates(originX, originY);
	return searchLoc;
}


void World::Draw(int x, int y)
{
	if( GetCellType(x, y) == CellType_Empty )
	{
		Cursor cursor;
		cursor.SetLocation(x, y);
		cout << ".";
	}
	else if( GetCellType(x, y) == CellType_Prey )
		mArr[y*WIDTH + x]->Draw();
	else if( GetCellType(x, y) == CellType_Predator )
		mArr[y*WIDTH + x]->Draw();
}

////these functions may be causing bugs: They return Organism, not Organism*
//Organism& World::operator[](int index)
//{
//	assert(index < WIDTH * HEIGHT);
//	return *mArr[index];
//}
//
//Organism World::operator[](int index) const
//{
//	assert(index < WIDTH * HEIGHT);
//	return *mArr[index];
//}