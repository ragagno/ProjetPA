#ifndef PROXIMACENTAURI_VIEW_H
#define PROXIMACENTAURI_VIEW_H

#include <SDL2/SDL_video.h>

const auto WINDOW_WIDTH = 720;
const auto WINDOW_HEIGHT = 960;
const auto WINDOW_TITLE = "Proxima Centauri";

class View
{
public:
    View() = default;
    virtual ~View() = default;
    virtual void init() = 0;
    virtual void render(SDL_Window *window) = 0;
};

#endif //PROXIMACENTAURI_VIEW_H