#include <iostream>
#include <ctime>    // for time
#include "World.h"
#include<windows.h>
using namespace std;

int main()
{
    World myWorld(time(0));

    myWorld.display();

    char ch;

    while (1) {   // q for quit
        myWorld.simulateOneStep();
        myWorld.display();
		Sleep(300);
		system("cls");
    }

    return 0;
}
