#include "waste.hh"
#include <random>

#include <cstdlib>
#include <ctime>

#include <QtDebug>
using namespace std;

Waste::Waste(vector<MaterialTypes> CurrentMaterials){
    default_random_engine generator;

    srand(time(nullptr));

    Material = CurrentMaterials[rand() % CurrentMaterials.size()];
//    random_device rd; // obtain a random number from hardware
//    mt19937 eng(rd()); // seed the generator
//    uniform_int_distribution<> distr(0, 5); // define the range
////    int DrugiInd = distr(eng);
//    qDebug() << DrugiInd;
//    for(auto i : CurrentMaterials){
//        qDebug() << i;
//    }
    // Waste Material

//    uniform_int_distribution<int> MaterialIndices(0,CurrentMaterials.size());
//    Material = HDPE;
//    qDebug() << Material;

    // Waste heaviness
//    uniform_int_distribution<int> IsOrIsnt(0,1);
//    isHeavy = IsOrIsnt(generator);

    // Waste Colour
    switch (Material) {
    case PET:
        Colour = Qt::green;
        break;
    case Karton:
        Colour = Qt::blue;
        break;
    case HDPE:
        Colour = Qt::yellow;
        break;
    case Alum:
        Colour = Qt::magenta;
        break;
    case Nieznany:
        Colour = Qt::red;
        break;
    default:
        Colour = Qt::darkCyan;
        break;
    }
}

Waste::Waste(const Waste & WasteCopy) {
    (*this) = WasteCopy;
}

Waste::~Waste()
{

}

