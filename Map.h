#ifndef MAP_HFILE
#define MAP_HFILE


class World
{
public:
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
public:
	World();

	CellType GetCellType(int x, int y) const;
	void FillCell(int x, int y, CellType organismType);
	void Populate(CellType organismType, int num);
	bool IsInBounds(int x, int y) const;
	Coordinates GetAdjacentRand(int originX, int originY,
								CellType seekType = CellType_Empty) const;

	void Draw(int x, int y);

	//Organism& operator[](int index);
	//Organism operator[](int index) const;

//private:
	Organism* mArr[ WIDTH * HEIGHT ];
};



#endif