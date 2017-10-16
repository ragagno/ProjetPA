#ifndef PROXIMACENTAURI_OPTIONSMODEL_H
#define PROXIMACENTAURI_OPTIONSMODEL_H

#include "../Model.h"

class OptionsModel : public Model
{
private:
    bool music;
    bool sound;
    unsigned int selectedIndex;
public:
    void init() override;
    void reset() override;
    void update(long double tick) override;
    void up();
    void down();
    void flipMusic();
    void flipSound();
    unsigned int getSelectedIndex() const;
    bool isMusicOn();
    bool isSoundOn();
};

#endif //PROXIMACENTAURI_OPTIONSMODEL_H