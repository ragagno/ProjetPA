#ifndef PROXIMACENTAURI_LEVEL_H
#define PROXIMACENTAURI_LEVEL_H

#include <string>

class Level
{
private:
    int repeatPattern;
    int patternSize;
    std::string name;
    std::string fileName;
    std::string *pattern;
public:
    Level();
    ~Level();
    void setFileName(const std::string &fileName);
    void loadLevel();
};

#endif //PROXIMACENTAURI_LEVEL_H