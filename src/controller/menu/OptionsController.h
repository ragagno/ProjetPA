#ifndef PROXIMACENTAURI_OPTIONSCONTROLLER_H
#define PROXIMACENTAURI_OPTIONSCONTROLLER_H

#include "../Controller.h"
#include "../GameController.h"
#include "../../model/menu/OptionsModel.h"
#include "../../view/menu/OptionsView.h"

class OptionsController : public Controller
{
private:
    OptionsModel model;
    OptionsView view;
    GameController::State *state;
public:
    explicit OptionsController(GameController::State *state);
    void init() override;
    ~OptionsController() override = default;
    Model *getModel() override;
    View *getView() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_OPTIONSCONTROLLER_H