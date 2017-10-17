#ifndef PROXIMACENTAURI_MODEL_H
#define PROXIMACENTAURI_MODEL_H

class Model
{
private:
    bool resetable = true;
public:
    Model() = default;
    virtual ~Model() = default;
    virtual void init() = 0;
    virtual void reset() = 0;
    void setResetable(bool resetable)
    {
        this->resetable = resetable;
    }
    bool isResetable()
    {
        return resetable;
    }
    virtual void update(long double tick) = 0;
};

#endif //PROXIMACENTAURI_MODEL_H
