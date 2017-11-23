#ifndef PROXIMACENTAURI_PLAYER_H
#define PROXIMACENTAURI_PLAYER_H

#include <cstdint>

const long double SQRT2 = 1.41421356;

class Player
{
private:
    uint_fast32_t hp;
    long double x;
    long double y;
    long double speed;
public:
    Player();
    ~Player();
    int_fast32_t getX() const;
    int_fast32_t getY() const;
    long double getSpeed() const;
    void u(long double lag);
    void d(long double lag);
    void l(long double lag);
    void r(long double lag);
    void ul(long double lag);
    void ur(long double lag);
    void dl(long double lag);
    void dr(long double lag);
    void accelerate();
    void deccelerate();
    void normalize();
    void damage(uint_fast32_t damage);
    bool isAlive();
};

#endif //PROXIMACENTAURI_PLAYER_H