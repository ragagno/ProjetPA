#ifndef PROXIMACENTAURI_MAPSELECTIONVIEW_H
#define PROXIMACENTAURI_MAPSELECTIONVIEW_H

#include <SDL2/SDL_render.h>
#include "MenuView.h"
#include "../../model/game/map/Map.h"

class MapSelectionView : private MenuView
{
private:
    bool initialized;
    uint_fast32_t mapCount;
    SDL_Rect upDstRect;
    SDL_Rect downDstRect;
    SDL_Rect *mapSrcRect;
    SDL_Texture **maps;
public:
    MapSelectionView();
    void init(SDL_Renderer *renderer) override;
    ~MapSelectionView() override;
    void render(uint_fast32_t selectedIndex, uint_fast32_t startIndex) const;
    void reset() const override;
};

#endif //PROXIMACENTAURI_MAPSELECTIONVIEW_H