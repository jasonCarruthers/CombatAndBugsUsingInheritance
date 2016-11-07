class World;


#ifndef PREDATORPREY_HFILE
#define PREDATORPREY_HFILE



class Organism
{
public:
	Organism(int x = 0, int y = 0);

	int GetX() const;
	int GetY() const;
	CellType GetType() const;
	void SetMoveState(bool hasMoved);
	void SetNumTimeSteps(int numTimeSteps);
	int GetNumStarvedTimeSteps() const;
	void SetNumStarvedTimeSteps(int numStarvedTimeSteps);

	virtual void Move(World &world);
	void Reproduce(World &world);
	virtual void ReproductionPhase(World &world);

	virtual void Update(World &world);
	virtual void Draw() const = 0;	//should be pure virtual
	
	bool operator==(const Organism &right) const;

protected:
	int mX;
	int mY;
	int mNumTimeSteps;
	int mNumStarvedTimeSteps;
	bool mHasMovedThisTurn;
	CellType mType;
};


class Prey : public Organism
{
public:
	Prey(int x = 0, int y = 0);
	void Move(World &world);
	void ReproductionPhase(World &world);
	void Draw() const;
};

class Predator : public Organism
{
public:
	Predator(int x = 0, int y = 0);
	void ReproductionPhase(World &world);
	void Move(World &world);
	void Update(World &world);
	void Draw() const;
};





#endif