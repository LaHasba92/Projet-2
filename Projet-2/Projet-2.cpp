#include "Map.h"

#include <iostream>

int main()
{
    Map map(20, 10);

    if (!map.loadFromFile("levels/level01.txt"))
    {
        std::cout << "Impossible de charger le niveau.\n";
        return 1;
    }

    map.display();
    return 0;
}