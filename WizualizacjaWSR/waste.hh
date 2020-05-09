#ifndef WASTE_HH
#define WASTE_HH

#include <QRect>
#include <vector>
#include <QColor>

enum MaterialTypes { PET, Karton, HDPE, Alum, Nieznany };

class Waste: public QRect {
//    Q_OBJECT
public:
    Waste(std::vector<MaterialTypes> CurrentMaterials);
    // Ten konstruktor źle?
    Waste(const Waste& WasteCopy);
    ~Waste();

    MaterialTypes getMaterial() const {return Material;}
    QColor getColour() const{return Colour;}

private:
    MaterialTypes Material;
    QColor Colour;
    bool isHeavy;
};

#endif // WASTE_HH
