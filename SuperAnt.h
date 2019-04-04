#ifndef INHERITANCE_AND_POLYMORPHISM_SuperAnt
#define INHERITANCE_AND_POLYMORPHISM_SuperAnt

#include<iostream>
#include <conio.h>
//#include "Bug.h"
#include "World.h"
#include "Organism.h"

class SuperAnt : public Organism
{
public:
	SuperAnt(World* aWorld, int xcoord, int ycoord); // Create the SuperBug at the selected xy cord
	
	void move();

	// Makes this organism breed.
	void breed();

	// Returns the type of this organism.
	OrganismType getType() const;

	// The character representation of this organism.
	char representation() const;

	// The size of this organism.
	int size() const;
	// Returns true if organism is dead, false otherwise.
	bool isDead() const;

	bool in_range(int xx, int yy);
	

private:

	void generateOffspring(int whereX, int whereY);
	int death_tik;
};
#endif
