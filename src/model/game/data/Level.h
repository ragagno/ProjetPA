#ifndef PROXIMACENTAURI_LEVEL_H
#define PROXIMACENTAURI_LEVEL_H

#include <string>

class Level
{
private:
    uint_fast32_t patternRepeat;
    uint_fast32_t patternSize;
    std::string name;
    std::string fileName;
    std::string *pattern;
public:
    Level();
    void init();
    ~Level();
    std::string getName() const;
    uint_fast32_t getPatternRepeat() const;
    uint_fast32_t getPatternSize() const;
    std::string *getPattern() const;
    void setFileName(const std::string &fileName);
    void loadLevel();
};

#endif //PROXIMACENTAURI_LEVEL_H