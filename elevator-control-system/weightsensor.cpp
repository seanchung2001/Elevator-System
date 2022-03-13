#include "weightsensor.h"

weightsensor::weightsensor(float w) {
    maxWeight = w;
    currWeight = 0.0;
}

void weightsensor::setCurrWeight(float nWeight){
    currWeight = nWeight;
}
//Check if max weight is exceeded
bool weightsensor::isOverload(){
    if (currWeight >= maxWeight) {
        return true;
    }
    return false;
}

int weightsensor::getMaxWeight() { return maxWeight; }
float weightsensor:: getCurrWeight() { return currWeight; }

