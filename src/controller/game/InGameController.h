#ifndef PROXIMACENTAURI_INGAMECONTROLLER_H
#define PROXIMACENTAURI_INGAMECONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/game/InGameModel.h"
#include "../../view/game/InGameView.h"

class InGameController : public Controller
{
private:
    InGameModel model;
    InGameView view;
    GameController::State *state;
public:
    InGameController(GameController::State *state, Level **maps, unsigned int *inGameLevel);
    void init() override;
    ~InGameController() override = default;
    Model *getModel() override;
    View *getView() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_INGAMECONTROLLER_H