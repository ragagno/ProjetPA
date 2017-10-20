#ifndef PROXIMACENTAURI_OPTIONSMODEL_H
#define PROXIMACENTAURI_OPTIONSMODEL_H

#include "../Model.h"

class OptionsModel : public Model
{
private:
    bool music;
    bool sound;
    unsigned int selectedIndex;
    unsigned int selectedLayout;
public:
    OptionsModel();
    void init() override;
    ~OptionsModel() override = default;
    unsigned int getSelectedIndex() const;
    unsigned int getSelecedLayout() const;
    bool isMusicOn();
    bool isSoundOn();
    void reset() override;
    void update(long double) override;
    void up();
    void down();
    void flipMusic();
    void flipSound();
    void nextLayout();
    void previousLayout();
};

#endif //PROXIMACENTAURI_OPTIONSMODEL_H