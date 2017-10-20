#ifndef PROXIMACENTAURI_STARTGAMEMODEL_H
#define PROXIMACENTAURI_STARTGAMEMODEL_H

#include "../Model.h"

class StartGameModel : public Model
{
private:
    unsigned int selectedIndex;
    unsigned int mapNumber;
public:
    explicit StartGameModel(unsigned int mapNumber);
    void init() override;
    ~StartGameModel() override = default;
    unsigned int getSelectedIndex() const;
    void reset() override;
    void update(long double) override;
    void up();
    void down();
};

#endif //PROXIMACENTAURI_STARTGAMEMODEL_H