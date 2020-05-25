#ifndef WASTE_HH
#define WASTE_HH

#include <QRect>
#include <vector>
#include <QColor>

enum MaterialTypes { PET, Karton, HDPE, Alum, Nieznany };

class Waste{
public:
    Waste(std::vector<MaterialTypes> CurrentMaterials);
    Waste(const Waste& WasteCopy);
    ~Waste();

    MaterialTypes getMaterial() const {return Material;}
    QColor getColour() const{return Colour;}
    bool getHeaviness() const{return isHeavy;}
    float getZLocation() const {return ZLocation;}
    void setZLocation(float NewLocation) {ZLocation = NewLocation;}
    void ZAdvance(float Step){ZLocation -= Step;} // Reversed direction on both Views
    void XAdvance(float Step){XLocation -= Step;} // Reversed direction on both Views
    float getXLocation() const {return XLocation;}
    void setXLocation(float NewLocation) {XLocation = NewLocation;}

    int getCameraLocation() const {return CameraLocation;}
    void setCameraLocation(int NewLocation) {CameraLocation = NewLocation;}
    void AdvanceCamera(int Step) {CameraLocation -= Step;}


    // Material-Colour relation is also used in the CellContent
    /*static */QColor MaterialsColours[5] = {Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::red};

private:
    MaterialTypes Material;
    QColor Colour;
    float ZLocation;
    float XLocation;
    int CameraLocation;
    int Heaviness_Coefficient; // For decreasing number of Heavy Waste
    bool isHeavy;
};

#endif // WASTE_HH
