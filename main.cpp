#include <iostream>
#include <cmath>

#include "neuron.h"
#include "value.h"

int main()
{

    Neuron testNeuron(10);
    for (int i = 0; i < 10; i++)
    {
        std::cout << testNeuron.weights[i].data << std::endl;
    }
}