#include <iostream>
#include "Controller/GameController.h"

// TODO: game interface

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << "Unknown parameter " << argv[i] << std::endl;
    }

    GameController g;
    g.init();
    g.start();
    g.shutdown();

    return EXIT_SUCCESS;
}