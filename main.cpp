#include <iostream>
#include <cmath>

#include "layer.h"
#include "neuron.h"
#include "value.h"

int main()
{
    int numNeurons = 2;
    Neuron testNeuron(numNeurons);
    for (int i = 0; i < numNeurons; i++)
    {
        std::cout << testNeuron.weights[i].data << std::endl;
    }

    std::cout << testNeuron.bias.data << std::endl;
    vector<float> testData = {1.0, 50.0};
    Value outNeuron = testNeuron(testData);
    std::cout << outNeuron.data << std::endl;
}