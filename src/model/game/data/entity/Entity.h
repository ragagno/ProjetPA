#ifndef PROXIMACENTAURI_ENTITY_H
#define PROXIMACENTAURI_ENTITY_H

#include <cstdint>

class Entity
{
public:
    enum EntityID
    {
        PLAYER,
        _LENGTH
    };
protected:
    uint_fast32_t HP;
    uint_fast32_t maxHP;
    long double x;
    long double y;
    uint_fast32_t xSpeed;
    uint_fast32_t ySpeed;
    EntityID id;
public:
    long double getX() const
    {
        return x;
    }

    long double getY() const
    {
        return y;
    }
};

#endif //PROXIMACENTAURI_ENTITY_H