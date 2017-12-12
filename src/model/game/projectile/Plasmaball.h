#ifndef PROXIMACENTAURI_PLASMABALL_H
#define PROXIMACENTAURI_PLASMABALL_H

#include <cstdint>

class Plasmaball
{
private:
    bool player;
    uint_fast32_t damages;
    int_fast32_t xVelocity;
    int_fast32_t yVelocity;
    long double x;
    long double y;
public:
    Plasmaball(bool isPlayer, uint_fast32_t damages, int_fast32_t xVelocity, int_fast32_t yVelocity, long double x, long double y);
    void move(long double lag);
    bool isPlayer() const;
    uint_fast32_t getDamages() const;
    int_fast32_t getX() const;
    int_fast32_t getY() const;
};

#endif //PROXIMACENTAURI_PLASMABALL_H