#ifndef PROXIMACENTAURI_GAMEMODEL_H
#define PROXIMACENTAURI_GAMEMODEL_H

#include <vector>
#include "entity/Player.h"
#include "entity/Entity.h"
#include "projectile/Plasmaball.h"

class GameModel
{
private:
    bool initialized;
    bool paused;
    bool defeat;
    bool victory;
    uint_fast32_t selectedPauseIndex;
    uint_fast32_t currentLine;
    uint_fast32_t last_fire;
    std::vector<Entity *> entities;
    std::vector<Plasmaball> plasma;
    Player player;
public:
    GameModel();
    void init();
    ~GameModel();
    bool isPaused() const;
    bool isDefeat() const;
    bool isVictory() const;
    void setDefeat();
    void setVictory();
    uint_fast32_t getSelectedIndex() const;
    uint_fast32_t getCurrentLine() const;
    Player &getPlayer();
    std::vector<Entity *> getEntities();
    const std::vector<Plasmaball> &getPlasma() const;
    bool nextLine();
    void flipPause();
    void tickEntities(long double lag);
    void up();
    void down();
    void move(bool up, bool down, bool left, bool right, long double lag);
    void reset();
};

#endif //PROXIMACENTAURI_GAMEMODEL_H