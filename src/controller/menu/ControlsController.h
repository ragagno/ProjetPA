#ifndef PROXIMACENTAURI_CONTROLSCONTROLLER_H
#define PROXIMACENTAURI_CONTROLSCONTROLLER_H

#include "../GameController.h"
#include "../../model/menu/ControlsModel.h"
#include "../../view/menu/ControlsView.h"

class ControlsController : public Controller
{
private:
    GameController::State *state;
    ControlsModel model;
    ControlsView view;
public:
    explicit ControlsController(GameController::State *state);
    Model *getModel() override;
    View *getView() override;
    void init() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_CONTROLSCONTROLLER_H