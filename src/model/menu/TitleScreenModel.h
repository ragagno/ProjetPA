#ifndef PROXIMACENTAURI_TITLESCREENMODEL_H
#define PROXIMACENTAURI_TITLESCREENMODEL_H

#include "../Model.h"

class TitleScreenModel : public Model
{
private:
    unsigned int selectedIndex;
public:
    TitleScreenModel();
    void init() override;
    ~TitleScreenModel() override = default;
    unsigned int getSelectedIndex() const;
    void up();
    void down();
    void reset() override;
    void update(long double) override;
};

#endif //PROXIMACENTAURI_TITLESCREENMODEL_H
