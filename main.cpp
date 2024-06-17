#include <iostream>
#include <cmath>
#include <vector>

#include "layer.h"
#include "neuron.h"
#include "value.h"

int main()
{
    int numNeurons = 2;
    Neuron testNeuron(numNeurons);
    Value testValue(2.0);
    Value returnNode = testNeuron({testValue, testValue});
    returnNode.grad = 1.0;
    returnNode.backward();
}