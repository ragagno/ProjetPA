#ifndef PROXIMACENTAURI_MENUVIEW_H
#define PROXIMACENTAURI_MENUVIEW_H

#include "../View.h"

const auto VERSION = "0.0.1";
const auto AUTHOR = "RAGAGNO";

class MenuView : public View
{
private:
    SDL_Surface *proxima;
    SDL_Surface *cent;
    SDL_Surface *spaceship;
    SDL_Surface *uri;
    SDL_Surface *version;
    SDL_Surface *author;
public:
    MenuView();
    void init() override;
    ~MenuView() override;
    void reset() override;
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_MENUVIEW_H