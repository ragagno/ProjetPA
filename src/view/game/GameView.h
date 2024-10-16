#ifndef PROXIMACENTAURI_GAMEVIEW_H
#define PROXIMACENTAURI_GAMEVIEW_H

#include <SDL2/SDL_render.h>
#include <vector>
#include "../../model/game/entity/Player.h"
#include "../../model/game/entity/Entity.h"
#include "../../model/game/projectile/Plasmaball.h"

class GameView
{
private:
    bool initialized;
    SDL_Rect replaySrcRect;
    SDL_Rect resumeSrcRect;
    SDL_Rect victorySrcRect;
    SDL_Rect defeatSrcRect;
    SDL_Rect quitSrcRect;
    SDL_Texture *victory;
    SDL_Texture *defeat;
    SDL_Texture *replay;
    SDL_Texture *resume;
    SDL_Texture *quit;
    SDL_Renderer *renderer;
public:
    GameView();
    void init(SDL_Renderer *renderer);
    ~GameView();
    void render(const Player &player, std::vector<Entity *> entities, std::vector<Plasmaball>, std::vector<Laserbeam>) const;
    void renderPause(uint_fast32_t selectedIndex) const;
    void renderDefeat(uint_fast32_t selectedIndex) const;
    void renderVictory(uint_fast32_t selectedIndex) const;
    void reset() const;
};

#endif //PROXIMACENTAURI_GAMEVIEW_H