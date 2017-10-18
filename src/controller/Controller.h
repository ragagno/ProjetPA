#ifndef PROXIMACENTAURI_CONTROLLER_H
#define PROXIMACENTAURI_CONTROLLER_H

#include "../model/Model.h"
#include "../view/View.h"

class Controller
{
public:
    Controller() = default;
    virtual void init() = 0;
    virtual ~Controller() = default;
    virtual Model *getModel() = 0;
    virtual View *getView() = 0;
    virtual void tick(long double ticks) = 0;
};

#endif //PROXIMACENTAURI_CONTROLLER_H
