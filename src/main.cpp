#include <iostream>
#include "Controller/Game.h"

// TODO: Graphics

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << "Unknown argument " << argv[i] << std::endl;
    }

    Game g;

    g.init();
    g.start();
    g.shutdown();

    return EXIT_SUCCESS;
}