#ifndef PROXIMACENTAURI_ENTITY_H
#define PROXIMACENTAURI_ENTITY_H

#include <stdint-gcc.h>

class Entity
{
public:
    enum FireType
    {
        LASER_BEAM,
        PLASMA_BALL,
        _LENGTH
    };
private:
    static uint_fast32_t entityNumber;
    static Entity *entities;
    long double x;
    long double y;
    long double speed;
    uint_fast32_t hp;
    uint_fast32_t damageHit;
    uint_fast32_t damageFire;
    uint_fast32_t spriteNumber;
    uint_fast32_t attackFrequency;
    FireType damageType;
public:
    Entity(const Entity &initial);
    void setX(uint_fast32_t x);
    static Entity getEntity(char c);
    int_fast32_t getX() const;
    int_fast32_t getY() const;
    uint_fast32_t getSprite() const;
    uint_fast32_t getDamageHit() const;
    void move(long double lag);
    static void init();
    static bool exists(char c);
    ~Entity();
private:
    Entity();
    void loadEntity(const std::string &filename);
};

#endif //PROXIMACENTAURI_ENTITY_H