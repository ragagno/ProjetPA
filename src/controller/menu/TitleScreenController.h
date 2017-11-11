#ifndef PROXIMACENTAURI_TITLESCREENCONTROLLER_H
#define PROXIMACENTAURI_TITLESCREENCONTROLLER_H

#include "../Controller.h"
#include "../../model/menu/TitleScreenModel.h"
#include "../../view/menu/TitleScreenView.h"
#include "../../ProximaCentauri.h"

class TitleScreenController : public Controller
{
private:
    ProximaCentauri::GameState nextState;
    bool initialized;
    TitleScreenModel *model;
    TitleScreenView *view;
public:
    TitleScreenController();
    void init(SDL_Renderer *renderer) override;
    ~TitleScreenController() override;
    void tick(long double) override;
    void render() override;
};

#endif //PROXIMACENTAURI_TITLESCREENCONTROLLER_H