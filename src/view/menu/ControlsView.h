#ifndef PROXIMACENTAURI_CONTROLSVIEW_H
#define PROXIMACENTAURI_CONTROLSVIEW_H

#include "MenuView.h"

class ControlsView : public MenuView
{
public:
    ControlsView() = default;
    ~ControlsView() override = default;
    void init() override;
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_CONTROLSVIEW_H