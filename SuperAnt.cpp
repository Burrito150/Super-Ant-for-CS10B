#include "SuperAnt.h"
#include "Organism.h"
#include <conio.h>
using namespace std;


SuperAnt::SuperAnt(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
	death_tik = 0;
}

void SuperAnt::move()
{
	//breedTicks++;
	death_tik++;
	
	// modify to + 2
	if (world->getAt(x, y + 2) != NULL)
	{
		if (world->getAt(x, y + 2)->getType() == BUG) // Checks if the space that is occupied is
			//a bug if so the bug is killed and the breedTrick is increased and deathTick is set to zero
		{
			death_tik = 0;
			delete world->getAt(x, y + 1);
			movesTo(x, y + 2);
			breedTicks++;
			return;
		}
	}

	if (world->getAt(x, y - 2) != NULL)
	{
		if (world->getAt(x, y - 2)->getType() == BUG)
		{
			death_tik = 0;
			delete world->getAt(x, y - 2);
			movesTo(x, y - 2);
			breedTicks++;
			return;
		}
	}

	if (world->getAt(x - 2, y) != NULL)
	{
		if (world->getAt(x - 2, y)->getType() == BUG)
		{
			death_tik = 0;
			delete world->getAt(x - 2, y);
			movesTo(x - 2, y);
			breedTicks++;
			return;
		}
	}
	if (world->getAt(x + 2, y) != NULL)
	{
		if (world->getAt(x + 2, y)->getType() == BUG)
		{
			death_tik = 0;
			delete world->getAt(x + 2, y);
			movesTo(x + 2, y);
			breedTicks++;
			return;
		}
	}

	Move mover = world->randomMove();
	switch (mover) {
	case UP:
		if (world->getAt(x, y + 2) == NULL && in_range(x, y + 2))
		{
			movesTo(x, y + 2);
		}
		break;
	case DOWN:
		if (world->getAt(x, y - 2) == NULL && in_range(x, y - 2))
		{
			movesTo(x, y - 2);
		}
		break;
	case LEFT:
		if (world->getAt(x - 2, y) == NULL && in_range(x - 2, y))
		{
			movesTo(x - 2, y);
		}
		break;
	case RIGHT:
		if (world->getAt(x + 2, y) == NULL && in_range(x + 2, y))
		{
			movesTo(x + 2, y);
		}
		break;
	default:
		break;
	}
}

void SuperAnt::generateOffspring(int whereX, int whereY)
{
	new SuperAnt(this->world, whereX, whereY);
	breedTicks = 0;
}

void SuperAnt::breed() // Must be changed to have the super bug only breed when it has eaten x amount of bugs
{
	if (breedTicks >= BREED_SUPERANT)
	{
		breedAtAdjacentCell();
	}

}

bool SuperAnt::isDead() const
{
	if (death_tik >= STARVE_SUPERANT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

OrganismType SuperAnt::getType() const
{
	return SUPERANT;
}


char SuperAnt::representation()const
{
	//textcolor(RED);
	return 'S';
}

int SuperAnt::size() const
{
	return 30;
}

bool SuperAnt::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
