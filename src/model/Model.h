#ifndef PROXIMACENTAURI_MODEL_H
#define PROXIMACENTAURI_MODEL_H

class Model
{
public:
    Model() = default;
    virtual ~Model() = default;
    virtual void init() = 0;
    virtual void reset() = 0;
    virtual void update(long double tick) = 0;
};

#endif //PROXIMACENTAURI_MODEL_H
