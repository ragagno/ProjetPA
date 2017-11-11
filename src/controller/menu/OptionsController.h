#ifndef PROXIMACENTAURI_OPTIONSCONTROLLER_H
#define PROXIMACENTAURI_OPTIONSCONTROLLER_H

#include "../Controller.h"
#include "../../model/menu/OptionsModel.h"
#include "../../view/menu/OptionsView.h"
#include "../../ProximaCentauri.h"

class OptionsController : public Controller
{
private:
    ProximaCentauri::GameState nextState;
    bool initialized;
    OptionsModel *model;
    OptionsView *view;
public:
    OptionsController();
    void init(SDL_Renderer *renderer) override;
    ~OptionsController() override;
    void tick(long double) override;
    void render() override;
};

#endif //PROXIMACENTAURI_OPTIONSCONTROLLER_H