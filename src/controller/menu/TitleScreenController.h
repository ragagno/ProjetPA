#ifndef PROXIMACENTAURI_TITLESCREENCONTROLLER_H
#define PROXIMACENTAURI_TITLESCREENCONTROLLER_H

#include "../Controller.h"
#include "../../view/menu/TitleScreenView.h"
#include "../../model/menu/TitleScreenModel.h"
#include "../GameController.h"

class TitleScreenController : public Controller
{
private:
    TitleScreenModel model;
    TitleScreenView view;
    bool *looping;
    GameController::State *state;
public:
    TitleScreenController(bool *looping, GameController::State *state);
    void init() override;
    ~TitleScreenController() override = default;
    Model *getModel() override;
    View *getView() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_TITLESCREENCONTROLLER_H