#ifndef PROXIMACENTAURI_GAMEVIEW_H
#define PROXIMACENTAURI_GAMEVIEW_H

#include <SDL2/SDL_render.h>
#include <vector>
#include "../../model/game/entity/Player.h"
#include "../../model/game/entity/Entity.h"

class GameView
{
private:
    bool initialized;
    SDL_Rect resumeSrcRect;
    SDL_Rect quitSrcRect;
    SDL_Texture *resume;
    SDL_Texture *quit;
    SDL_Renderer *renderer;
public:
    GameView();
    void init(SDL_Renderer *renderer);
    ~GameView();
    void render(const Player &player, std::vector<Entity *> entities) const;
    void renderPause(uint_fast32_t selectedIndex) const;
    void reset() const;
};

#endif //PROXIMACENTAURI_GAMEVIEW_H