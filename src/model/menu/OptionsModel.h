#ifndef PROXIMACENTAURI_OPTIONSMODEL_H
#define PROXIMACENTAURI_OPTIONSMODEL_H

class OptionsModel
{
public:
    enum KeyboardLayout
    {
        WASD,
        ZQSD,
        ARROWS,
        _LENGTH
    };
private:
    uint_fast32_t selectedIndex;
    bool initialized;
    bool music;
    bool sound;
    KeyboardLayout layout;
public:
    OptionsModel();
    void init();
    ~OptionsModel();
    bool isMusicOn() const;
    bool isSoundon() const;
    KeyboardLayout getLayout() const;
    uint_fast32_t getSelectedIndex() const;
    void flipSound();
    void flipMusic();
    void nextLayout();
    void previousLayout();
    void up();
    void down();
    void reset();
    void saveOptions() const;
};

#endif //PROXIMACENTAURI_OPTIONSMODEL_H