#include <iostream>
//#include<string> // added to allow the add function to change names
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "SuperAnt.h"
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
	char spawn;
	int amt, amtA = 0, amtB = 0, amtSA = 0;
	char check ;
	
	cout << " Would You Like to add aditional insects? [Y/N]" << endl;
	cin >> check;
	if(check == 'Y' || check == 'y')
	{
		cout << " How many additional Ants would you like to spawn? (Default 5)";
		cin >> amt;
		amtA = amt;
		//createOrganisms(ANT, amtA);
		cout << " How many additional Bugs would you like to spawn? (Default 5)";
		cin >> amt;
		amtB = amt;
		//createOrganisms(BUG, amtB);
		cout << " How many additional SUper Ants would you like to spawn? (Default 2)";
		cin >> amt;
		amtSA = amt;
		//createOrganisms(SUPERANT, amtSA);
	}
	else 
	{
		for (int i = 0; i < WORLDSIZE; i++) {
			for (int j = 0; j < WORLDSIZE; j++) {
				grid[i][j] = NULL;
			}
		}
		// creates the ants = 3
		createOrganisms(ANT, INITIAL_ANTS + amtA);
		// adds a amount to the  initial amount of insects
		createOrganisms(BUG, INITIAL_BUGS + amtB);
		//creates the SuperBug = x
		createOrganisms(SUPERANT, INITIAL_SUPERANTS + amtSA);
	}
	for (int i = 0; i < WORLDSIZE; i++) {
		for (int j = 0; j < WORLDSIZE; j++) {
			grid[i][j] = NULL;
		}
	}
	// creates the ants = 3
	createOrganisms(ANT, INITIAL_ANTS + amtA);
	// creates the bugs = 8
	createOrganisms(BUG, INITIAL_BUGS + amtB);
	//creates the SuperBug = x
	createOrganisms(SUPERANT, INITIAL_SUPERANTS + amtSA);
	
	

   
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const {
    int numAnts = 0;
    int numBugs = 0;
	int numSuperAnts = 0;
	char spawn; // takes user inpout to see what they want to spawn
    cout << endl << endl;
    for (int j = 0; j < WORLDSIZE; j++) {
        for (int i = 0; i < WORLDSIZE; i++) {
            if (grid[i][j] == NULL) {
                cout << ".";
            } else {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                }
				else if (grid[i][j]->getType() == SUPERANT) {
					numSuperAnts++;
				}
				cout << grid[i][j]->representation();
            }
        }
        cout << endl;
    }
    cout << "Ants: " << numAnts << " Bugs: " << numBugs << " SuperAnts: " << numSuperAnts <<  endl;
	/*cout << "WOuld You Like to spawn a Insect? [Y/N]" << endl;
	if()
	{
		cout << "Would You Like to Add a Insect? A for ant, B for Bug, S for Super Ant " << endl;
		cin >> spawn;
		if (spawn == 'a' || spawn == 'A')
		{

		}
		else if (spawn == 'b' || spawn == 'B')
		{

		}
		else if (spawn == 's' || spawn == 'S')
		{

		}
	}
	*/
	

}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    // Make the bugs starve

	moveOrganism(SUPERANT);
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
			else if (orgType == SUPERANT)
			{
				new SuperAnt(this, p.x, p.y);

			}
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
