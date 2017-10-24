#ifndef PROXIMACENTAURI_MODEL_H
#define PROXIMACENTAURI_MODEL_H

class Model
{
protected:
    bool resetable = true;
public:
    Model() = default;
    virtual void init() = 0;
    virtual ~Model() = default;
    void setResetable(bool resetable)
    {
        this->resetable = resetable;
    }
    virtual void reset() = 0;
    virtual void update(long double tick) = 0;
};

#endif //PROXIMACENTAURI_MODEL_H
