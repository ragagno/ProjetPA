#ifndef PROXIMACENTAURI_CONTROLSMODEL_H
#define PROXIMACENTAURI_CONTROLSMODEL_H

#include "../Model.h"

class ControlsModel : public Model
{
public:
    void init() override;
    void reset() override;
    void update(long double tick) override;
};

#endif //PROXIMACENTAURI_CONTROLSMODEL_H