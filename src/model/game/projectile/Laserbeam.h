#ifndef PROXIMACENTAURI_LASERBEAM_H
#define PROXIMACENTAURI_LASERBEAM_H

#include "../entity/Entity.h"
#include "../entity/Player.h"

class Entity;

class Laserbeam
{
private:
    bool alive;
    Entity *origin;
    Player *player;
    uint_fast32_t ticksFromBirth;
public:
    Laserbeam(Entity *origin, Player *player);
    uint_fast32_t getX() const;
    uint_fast32_t getY() const;
    uint_fast32_t getL() const;
    uint_fast32_t getDamages() const;
    void kill();
    bool tick(long double lag);
    void unsetOrigin();
};

#endif //PROXIMACENTAURI_LASERBEAM_H