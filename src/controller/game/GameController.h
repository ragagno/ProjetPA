#ifndef PROXIMACENTAURI_GAMECONTROLLER_H
#define PROXIMACENTAURI_GAMECONTROLLER_H

#include "../Controller.h"
#include "../../ProximaCentauri.h"
#include "../../model/game/GameModel.h"
#include "../../view/game/GameView.h"

class GameController : public Controller
{
private:
    ProximaCentauri::GameState nextState;
    bool initialized;
    bool lastUp;
    bool lastDown;
    bool lastLeft;
    bool lastRight;
    GameModel *model;
    GameView *view;
public:
    GameController();
    void init(SDL_Renderer *renderer) override;
    ~GameController() override;
    void tick(long double lag) override;
    void render() override;
};

#endif //PROXIMACENTAURI_GAMECONTROLLER_H