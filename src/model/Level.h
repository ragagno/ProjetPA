#ifndef PROXIMACENTAURI_LEVEL_H
#define PROXIMACENTAURI_LEVEL_H

#include <string>

class Level
{
private:
    uint32_t repeatPattern;
    uint32_t patternSize;
    std::string name;
    std::string fileName;
    std::string *pattern;
public:
    Level();
    ~Level();
    void init();
    void setFileName(const std::string &fileName);
    void loadLevel();
};

#endif //PROXIMACENTAURI_LEVEL_H