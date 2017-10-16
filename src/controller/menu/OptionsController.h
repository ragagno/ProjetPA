#ifndef PROXIMACENTAURI_OPTIONSCONTROLLER_H
#define PROXIMACENTAURI_OPTIONSCONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/menu/OptionsModel.h"
#include "../../view/menu/OptionsView.h"

class OptionsController : public Controller
{
private:
    GameController::State *state;
    OptionsModel model;
    OptionsView view;
public:
    explicit OptionsController(GameController::State *state);
    Model *getModel() override;
    View *getView() override;
    void init() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_OPTIONSCONTROLLER_H