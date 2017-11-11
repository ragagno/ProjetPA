#ifndef PROXIMACENTAURI_MAPSELECTIONMODEL_H
#define PROXIMACENTAURI_MAPSELECTIONMODEL_H

class MapSelectionModel
{
private:
    bool initialized;
    uint_fast32_t startIndex;
    uint_fast32_t selectedIndex;
    uint_fast32_t mapCount;
public:
    MapSelectionModel();
    void init();
    ~MapSelectionModel();
    uint_fast32_t getStartIndex() const;
    uint_fast32_t getSelectedIndex() const;
    void up();
    void down();
    void reset();
};

#endif //PROXIMACENTAURI_MAPSELECTIONMODEL_H