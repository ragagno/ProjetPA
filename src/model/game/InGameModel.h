#ifndef PROXIMACENTAURI_INGAMEMODEL_H
#define PROXIMACENTAURI_INGAMEMODEL_H

#include "../Model.h"
#include "data/Level.h"

class InGameModel : public Model
{
private:
    unsigned int selectedIndex;
    bool paused;
    unsigned int *inGameLevel;
    Level **maps;
public:
    explicit InGameModel(Level **maps, unsigned int *inGameLevel);
    void init() override;
    ~InGameModel() override = default;
    unsigned int getSelectedIndex() const;
    bool isPaused() const;
    void pauseUp();
    void pauseDown();
    void flipPause();
    void reset() override;
    void update(long double tick) override;
};

#endif //PROXIMACENTAURI_INGAMEMODEL_H