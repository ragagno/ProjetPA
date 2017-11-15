#ifndef PROXIMACENTAURI_GAMEMODEL_H
#define PROXIMACENTAURI_GAMEMODEL_H

#include "entity/Player.h"

class GameModel
{
private:
    bool initialized;
    bool paused;
    uint_fast32_t selectedPauseIndex;
    Player player;
public:
    GameModel();
    void init();
    ~GameModel();
    bool isPaused() const;
    uint_fast32_t getSelectedIndex() const;
    Player &getPlayer();
    void flipPause();
    void up();
    void down();
    void move(bool up, bool down, bool left, bool right, long double lag);
    void reset();
};

#endif //PROXIMACENTAURI_GAMEMODEL_H