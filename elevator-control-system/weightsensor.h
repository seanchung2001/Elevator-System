#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H


class weightsensor
{
public:
    weightsensor(float);

    int getMaxWeight();
    float getCurrWeight();
    void setCurrWeight(float);
    bool isOverload();

private:
    float maxWeight;
    float currWeight;
};

#endif // WEIGHTSENSOR_H
