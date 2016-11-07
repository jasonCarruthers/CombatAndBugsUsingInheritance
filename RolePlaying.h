#ifndef ROLEPLAYING_HFILE
#define ROLEPLAYING_HFILE


//class Creature (base class; abstract)
//class Human, class Elf, class Demon are derived from Creature
//class Cyberdemon, class Balrog derived from Demon


enum SpeciesTypes
{
	Species_Human,
	Species_Elf,
	Species_Cyberdemon,
	Species_Balrog,

	Num__SpeciesTypes,
};


class Creature
{
public:
	Creature(int newType = Species_Human, int newStrength = 10, int newHitPoints = 10);

	int GetStrength() const;
	int GetHitPoints() const;
	void SetHitPoints(int newHitPoints);
	std::string GetSpecies() const;

	virtual int GetDamage() const = 0;

protected:
	int mType;	//the creature's species
	int mStrength;
	int mHitPoints;
};



class Human : public Creature
{
public:
	Human(int newStrength = 30, int newHitPoints = 60);
	virtual int GetDamage() const;
};

class Elf : public Creature
{
public:
	Elf(int newStrength = 20, int newHitPoints = 85);
	virtual int GetDamage() const;
};

class Demon : public Creature
{
public:
	Demon(int newStrength = 10, int newHitPoints = 100);
	virtual int GetDamage() const;
};



class Cyberdemon : public Demon
{
public:
	Cyberdemon();
	virtual int GetDamage() const;
};

class Balrog : public Demon
{
public:
	Balrog();
	virtual int GetDamage() const;
};

extern std::string SpeciesName[ Num__SpeciesTypes ];

#endif