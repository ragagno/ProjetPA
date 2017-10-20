#ifndef PROXIMACENTAURI_STARTGAMECONTROLLER_H
#define PROXIMACENTAURI_STARTGAMECONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/menu/StartGameModel.h"
#include "../../view/menu/StartGameView.h"

class StartGameController : public Controller
{
private:
    StartGameModel model;
    StartGameView view;
    GameController::State *state;
public:
    explicit StartGameController(GameController::State *state, unsigned int mapNumber, Level **mapsLevel);
    void init() override;
    ~StartGameController() override = default;
    Model *getModel() override;
    View *getView() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_STARTGAMECONTROLLER_H