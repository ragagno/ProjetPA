#ifndef PROXIMACENTAURI_TITLESCREENMODEL_H
#define PROXIMACENTAURI_TITLESCREENMODEL_H

#include "../Model.h"

class TitleScreenModel : public Model
{
private:
    unsigned int selectedIndex;
public:
    TitleScreenModel();
    unsigned int getSelectedIndex() const;
    void reset() override;
    void update(SDL_Event *event) override;
};

#endif //PROXIMACENTAURI_TITLESCREENMODEL_H
