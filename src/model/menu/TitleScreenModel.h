#ifndef PROXIMACENTAURI_TITLESCREENMODEL_H
#define PROXIMACENTAURI_TITLESCREENMODEL_H

#include "../Model.h"

class TitleScreenModel : public Model
{
private:
    unsigned int selectedIndex;
public:
    TitleScreenModel();
    ~TitleScreenModel() override = default;
    unsigned int getSelectedIndex() const;
    void up();
    void down();
    void reset() override;
    void update(long double tick) override;
    void init() override;
};

#endif //PROXIMACENTAURI_TITLESCREENMODEL_H
