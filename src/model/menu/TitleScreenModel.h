#ifndef PROXIMACENTAURI_TITLESCREENMODEL_H
#define PROXIMACENTAURI_TITLESCREENMODEL_H

class TitleScreenModel
{
private:
    bool initialized;
    uint_fast32_t selectedIndex;
public:
    TitleScreenModel();
    void init();
    ~TitleScreenModel();
    uint_fast32_t getSelectedIndex() const;
    void up();
    void down();
    void reset();
};

#endif //PROXIMACENTAURI_TITLESCREENMODEL_H