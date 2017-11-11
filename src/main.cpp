#include <iostream>
#include <fstream>
#include "ProximaCentauri.h"

int main(int argc, char *argv[])
{
    for (int_fast32_t i = 1; i < argc; i++)
    {
        std::cerr << "Unknown parameter " << argv[i] << std::endl;
    }

    ProximaCentauri::getInstance()->init();
    ProximaCentauri::getInstance()->start();
    ProximaCentauri::getInstance()->shutdown();

    return EXIT_SUCCESS;
}