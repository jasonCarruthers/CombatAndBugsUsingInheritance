#include <iostream>
#include <cassert>
#include "windows.h"
#include "GeneralUse.h"
using namespace std;


//Const arrays
const Coordinates directionChange[ Num__CardinalDirections ] =
{
	Coordinates(0, -1),	//north
	Coordinates(1, 0),	//east
	Coordinates(0, 1),	//south
	Coordinates(-1, 0),	//west
};


//Cursor class functions
Cursor::Cursor()
{
	//set mLocation to the current cursor postion
}

COORD Cursor::GetLocation() const
{
	return mLocation;
}

void Cursor::SetLocation(int x, int y)
{
	mLocation.X = static_cast<short>(x);
	mLocation.Y = static_cast<short>(y);
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), mLocation );
}