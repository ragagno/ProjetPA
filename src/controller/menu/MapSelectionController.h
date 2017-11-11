#ifndef PROXIMACENTAURI_MAPSELECTIONCONTROLLER_H
#define PROXIMACENTAURI_MAPSELECTIONCONTROLLER_H

#include "../Controller.h"
#include "../../model/menu/MapSelectionModel.h"
#include "../../view/menu/MapSelectionView.h"
#include "../../ProximaCentauri.h"

class MapSelectionController : public Controller
{
private:
    ProximaCentauri::GameState nextState;
    bool initialized;
    MapSelectionModel *model;
    MapSelectionView *view;
public:
    MapSelectionController();
    void init(SDL_Renderer *renderer) override;
    ~MapSelectionController() override;
    void tick(long double) override;
    void render() override;
};

#endif //PROXIMACENTAURI_MAPSELECTIONCONTROLLER_H