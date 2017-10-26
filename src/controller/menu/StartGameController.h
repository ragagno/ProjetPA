#ifndef PROXIMACENTAURI_STARTGAMECONTROLLER_H
#define PROXIMACENTAURI_STARTGAMECONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/menu/StartGameModel.h"
#include "../../view/menu/StartGameView.h"
#include "../../model/game/InGameModel.h"

class StartGameController : public Controller
{
private:
    StartGameModel model;
    StartGameView view;
    unsigned int *inGameLevel;
    GameController::State *state;
    Level **maps;
public:
    StartGameController(GameController::State *state, unsigned int mapNumber, Level **maps, unsigned int  *inGameLevel);
    void init() override;
    ~StartGameController() override = default;
    Model *getModel() override;
    View *getView() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_STARTGAMECONTROLLER_H