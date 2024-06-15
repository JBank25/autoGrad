#include <iostream>
#include <random>
#include <vector>

#include "neuron.h"
#include "value.h"

using namespace std;

Neuron::Neuron(int numInputs)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);
    weights.resize(numInputs); // Resize the weights vector to match the number of inputs
    for (unsigned int i = 0; i < numInputs; i++)
    {
        weights[i] = Value(distribution(generator));
    }
    bias = Value(distribution(generator));
}
int main()
{
    // Value testVal = Value(1.0);
    Neuron testNeuron = Neuron(10);
    for (int i = 0; i < 10; i++)
    {
        std::cout << testNeuron.weights[i].data << std::endl;
    }
}