#ifndef PROXIMACENTAURI_TITLESCREENMODEL_H
#define PROXIMACENTAURI_TITLESCREENMODEL_H

#include "../Model.h"

class TitleScreenModel : public Model
{
private:
    uint_fast32_t selectedIndex;
public:
    TitleScreenModel();
    void init() override;
    ~TitleScreenModel() override = default;
    uint_fast32_t getSelectedIndex() const;
    void up();
    void down();
    void reset() override;
    void update(long double) override;
};

#endif //PROXIMACENTAURI_TITLESCREENMODEL_H
