#ifndef PROXIMACENTAURI_GAMEMODEL_H
#define PROXIMACENTAURI_GAMEMODEL_H

class GameModel
{
private:
    bool initialized;
    bool paused;
    uint_fast32_t selectedPauseIndex;
public:
    GameModel();
    void init();
    ~GameModel();
    bool isPaused() const;
    uint_fast32_t getSelectedIndex() const;
    void flipPause();
    void up();
    void down();
    void reset();
};

#endif //PROXIMACENTAURI_GAMEMODEL_H