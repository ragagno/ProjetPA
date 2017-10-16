#ifndef PROXIMACENTAURI_STARTGAMEMODEL_H
#define PROXIMACENTAURI_STARTGAMEMODEL_H

#include "../Model.h"

class StartGameModel : public Model
{
public:
    void init() override;
    void reset() override;
    void update(long double tick) override;
};

#endif //PROXIMACENTAURI_STARTGAMEMODEL_H