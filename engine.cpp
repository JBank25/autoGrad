#include <iostream>
#include <random>
#include <vector>

#include "engine.h"
#include "value.h"

// using namespace std;

Neuron::Neuron(int numInputs)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);
    for (unsigned int i = 0; i < numInputs; i++)
    {
        weights[i] = Value(1);
    }
    bias = Value(1);
}
int main()
{
    Value valA(2.0);
    Neuron testNeuron = Neuron(10);
    if (testNeuron.bias.data == 1)
    {
        testNeuron.bias.data = 0;
    }
}