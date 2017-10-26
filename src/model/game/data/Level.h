#ifndef PROXIMACENTAURI_LEVEL_H
#define PROXIMACENTAURI_LEVEL_H

#include <string>

class Level
{
private:
    unsigned int patternRepeat;
    unsigned int patternSize;
    std::string name;
    std::string fileName;
    std::string *pattern;
public:
    Level();
    void init();
    ~Level();
    std::string getName() const;
    unsigned int getPatternRepeat() const;
    unsigned int getPatternSize() const;
    std::string *getPattern() const;
    void setFileName(const std::string &fileName);
    void loadLevel();
};

#endif //PROXIMACENTAURI_LEVEL_H