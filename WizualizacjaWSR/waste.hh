#ifndef WASTE_HH
#define WASTE_HH

#include <QRect>
#include <vector>
#include <QColor>

enum MaterialTypes { PET, Karton, HDPE, Alum, Nieznany };


// QRECT NA QPOINT CZY COS


class Waste: public QRect {
public:
    Waste(std::vector<MaterialTypes> CurrentMaterials);
    Waste(const Waste& WasteCopy);
    ~Waste();

    MaterialTypes getMaterial() const {return Material;}
    QColor getColour() const{return Colour;}
    bool getHeaviness() const{return isHeavy;}
    float getLocation() const {return Location;}
    void setLocation(float NewLocation) {Location = NewLocation;}

    float getXLocation() const {return XLocation;}
    void setXLocation(float NewLocation) {XLocation = NewLocation;}

    // Material-Colour relation is also used in the CellContent
    /*static */QColor MaterialsColours[5] = {Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::red};

private:
    MaterialTypes Material;
    QColor Colour;
    float Location;
    float XLocation;
    int Heaviness_Coefficient; // For decreasing number of Heavy Waste
    bool isHeavy;
};

#endif // WASTE_HH
