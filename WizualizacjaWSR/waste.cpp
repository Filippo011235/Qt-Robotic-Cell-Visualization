#include "waste.hh"

#include <cstdlib>

#include <QtDebug>

using namespace std;

Waste::Waste(vector<MaterialTypes> CurrentMaterials){

    Material = CurrentMaterials[rand() % CurrentMaterials.size()];

    Heaviness_Coefficient = rand() % 10;
    if(Heaviness_Coefficient < 6){
        isHeavy = false;
    } else {
        isHeavy = true;
    }

    Colour = MaterialsColours[Material];
//    switch (Material) {
//    case PET:
//        Colour = Qt::green;
//        break;
//    case Karton:
//        Colour = Qt::blue;
//        break;
//    case HDPE:
//        Colour = Qt::yellow;
//        break;
//    case Alum:
//        Colour = Qt::magenta;
//        break;
//    case Nieznany:
//        Colour = Qt::red;
//        break;
//    default: // just in case
//        Colour = Qt::darkCyan;
//        qDebug("Something went wrong declaring Material!");
//        break;
//    }
}

Waste::Waste(const Waste & WasteCopy) {
    (*this) = WasteCopy;
}

Waste::~Waste()
{

}

