#ifndef PROXIMACENTAURI_STARTGAMEMODEL_H
#define PROXIMACENTAURI_STARTGAMEMODEL_H

#include "../Model.h"

class StartGameModel : public Model
{
private:
    uint_fast32_t selectedIndex;
    uint_fast32_t mapNumber;
public:
    explicit StartGameModel(uint_fast32_t mapNumber);
    void init() override;
    ~StartGameModel() override = default;
    uint_fast32_t getSelectedIndex() const;
    void reset() override;
    void update(long double) override;
    void up();
    void down();
};

#endif //PROXIMACENTAURI_STARTGAMEMODEL_H