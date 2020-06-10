#include "waste.hh"
#include <cstdlib>

using namespace std;

Waste::Waste(vector<MaterialTypes> CurrentMaterials){

    Material = CurrentMaterials[rand() % CurrentMaterials.size()];
    Colour = MaterialsColours[Material];

    if(rand() % 2){
        isHeavy = true;
    } else {
        isHeavy = false;
    }
}

Waste::Waste(const Waste & WasteCopy) {
    (*this) = WasteCopy;
}

Waste::~Waste()
{

}

