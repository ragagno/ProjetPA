#ifndef PROXIMACENTAURI_OPTIONSMODEL_H
#define PROXIMACENTAURI_OPTIONSMODEL_H

#include "../Model.h"

class OptionsModel : public Model
{
private:
    uint_fast32_t selectedIndex;
    uint_fast32_t selectedLayout;
    bool music;
    bool sound;
public:
    OptionsModel();
    void init() override;
    ~OptionsModel() override = default;
    uint_fast32_t getSelectedIndex() const;
    uint_fast32_t getSelectedLayout() const;
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