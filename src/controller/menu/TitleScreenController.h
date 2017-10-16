#ifndef PROXIMACENTAURI_TITLESCREENCONTROLLER_H
#define PROXIMACENTAURI_TITLESCREENCONTROLLER_H

#include "../Controller.h"
#include "../../view/menu/TitleScreenView.h"
#include "../../model/menu/TitleScreenModel.h"
#include "../GameController.h"

class TitleScreenController : public Controller
{
private:
    bool *looping;
    GameController::State *state;
    TitleScreenModel model;
    TitleScreenView view;
public:
    TitleScreenController(bool *looping, GameController::State *state);
    ~TitleScreenController() override;
    Model *getModel() override;
    View *getView() override;
    void init() override;
    void tick(long double ticks) override;
};

#endif //PROXIMACENTAURI_TITLESCREENCONTROLLER_H