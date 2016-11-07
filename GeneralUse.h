#ifndef GENERALUSE_HFILE
#define GENERALUSE_HFILE

#include <cassert>


enum CellType
{
	//CellType_Nonexistant,
	CellType_Empty,
	CellType_Prey,
	CellType_Predator,
};

enum CardinalDirection
{
	CardinalDirection_North,
	CardinalDirection_East,
	CardinalDirection_South,
	CardinalDirection_West,

	Num__CardinalDirections,
};

class Coordinates
{
public:
	Coordinates(int x = 0, int y = 0) { mX = x; mY = y; }
	
	int GetX() const { return mX; }
	void SetX(int newX) { mX = newX; }
	int GetY() const { return mY; }
	void SetY(int newY) { mY = newY; }

private:
	int mX;
	int mY;
};


class Cursor
{
public:
	Cursor();
	
	COORD GetLocation() const;
	void SetLocation(int x, int y);

private:
	COORD mLocation;
};


extern const Coordinates directionChange[ Num__CardinalDirections ];

#endif