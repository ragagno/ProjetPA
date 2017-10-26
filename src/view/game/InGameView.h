#ifndef PROXIMACENTAURI_INGAMEVIEW_H
#define PROXIMACENTAURI_INGAMEVIEW_H

#include "../View.h"

class InGameView : public View
{
private:
    bool paused;
    SDL_Rect pauseBackgroundRect;
    SDL_Rect resumeRect;
    SDL_Rect quitRect;
    SDL_Rect underlineRect;
    SDL_Surface *pauseBackground;
    SDL_Surface *resume;
    SDL_Surface *quit;
public:
    InGameView();
    void init() override;
    ~InGameView() override;
    void reset() override;
    void preRender(bool paused, unsigned int selectedIndex);
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_INGAMEVIEW_H