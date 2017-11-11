#ifndef PROXIMACENTAURI_MAP_H
#define PROXIMACENTAURI_MAP_H

#include <string>

class Map
{
private:
    std::string fileName;
    std::string mapName;
    uint_fast32_t patternSize;
    std::string *pattern;
public:
    Map();
    void loadName(std::string mapName);
    ~Map();
    const std::string &getMapName() const;
    uint_fast32_t getPatternSize() const;
    std::string *getPattern() const;
    bool loadPattern();
};

#endif //PROXIMACENTAURI_MAP_H