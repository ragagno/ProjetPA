#ifndef PROXIMACENTAURI_INGAMEVIEW_H
#define PROXIMACENTAURI_INGAMEVIEW_H

#include "../View.h"
#include "../../model/game/data/Level.h"
#include "../../model/game/data/entity/Player.h"

class InGameView : public View
{
private:
    bool paused;
    SDL_Rect pauseBackgroundRect;
    SDL_Rect resumeRect;
    SDL_Rect quitRect;
    SDL_Rect underlineRect;
    Player *player;
    SDL_Surface *resume;
    SDL_Surface *quit;
public:
    InGameView();
    void init() override;
    ~InGameView() override;
    void reset() override;
    void preRenderPause(uint_fast32_t selectedIndex);
    void preRenderPlaying(Player *player);
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_INGAMEVIEW_H