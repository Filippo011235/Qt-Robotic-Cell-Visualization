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
}

Waste::Waste(const Waste & WasteCopy) {
    (*this) = WasteCopy;
}

Waste::~Waste()
{

}

