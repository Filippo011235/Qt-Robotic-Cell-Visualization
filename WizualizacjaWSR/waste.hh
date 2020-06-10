#ifndef WASTE_HH
#define WASTE_HH

#include <QRect>
#include <vector>
#include <QColor>

enum MaterialTypes { PET, Karton, HDPE, Alum, Nieznany };

class Waste{
    MaterialTypes Material;
    QColor Colour;
    QColor MaterialsColours[5] = {Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::red};
    bool isHeavy;

    float ZLocation;
    float XLocation;
    int _2DLocation;

public:
    Waste(std::vector<MaterialTypes> CurrentMaterials);
    Waste(const Waste& WasteCopy);
    ~Waste();

    // General parameters
    MaterialTypes getMaterial() const {return Material;}
    QColor getColour() const{return Colour;}
    bool getHeaviness() const{return isHeavy;}

    // Z Location
    float getZLocation() const {return ZLocation;}
    void setZLocation(float NewLocation) {ZLocation = NewLocation;}
    void ZAdvance(float Step){ZLocation -= Step;}

    // X Location
    float getXLocation() const {return XLocation;}
    void setXLocation(float NewLocation) {XLocation = NewLocation;}
    void XAdvance(float Step){XLocation -= Step;}

    // _2D Location
    int get_2DLocation() const {return _2DLocation;}
    void set_2DLocation(int NewLocation) {_2DLocation = NewLocation;}
    void Advance_2D(int Step) {_2DLocation -= Step;}
};

#endif // WASTE_HH
