#ifndef PROXIMACENTAURI_STARTGAMECONTROLLER_H
#define PROXIMACENTAURI_STARTGAMECONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/menu/StartGameModel.h"
#include "../../view/menu/StartGameView.h"

class StartGameController : public Controller
{
private:
    GameController::State *state;
    StartGameModel model;
    StartGameView view;
public:
    explicit StartGameController(GameController::State *state);
    Model *getModel() override;
    View *getView() override;
    void init() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_STARTGAMECONTROLLER_H