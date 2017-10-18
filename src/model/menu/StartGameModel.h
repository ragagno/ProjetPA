#ifndef PROXIMACENTAURI_STARTGAMEMODEL_H
#define PROXIMACENTAURI_STARTGAMEMODEL_H

#include "../Model.h"

class StartGameModel : public Model
{
public:
    StartGameModel() = default;
    void init() override;
    ~StartGameModel() override = default;
    void reset() override;
    void update(long double tick) override;
};

#endif //PROXIMACENTAURI_STARTGAMEMODEL_H