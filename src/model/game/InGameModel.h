#ifndef PROXIMACENTAURI_INGAMEMODEL_H
#define PROXIMACENTAURI_INGAMEMODEL_H

#include "../Model.h"
#include "data/Level.h"

class InGameModel : public Model
{
private:
    uint_fast32_t selectedIndex;
    bool paused;
    uint_fast32_t *inGameLevel;
    Level **maps;
public:
    explicit InGameModel(Level **maps, uint_fast32_t *inGameLevel);
    void init() override;
    ~InGameModel() override = default;
    uint_fast32_t getSelectedIndex() const;
    bool isPaused() const;
    void pauseUp();
    void pauseDown();
    void flipPause();
    void reset() override;
    void update(long double tick) override;
};

#endif //PROXIMACENTAURI_INGAMEMODEL_H