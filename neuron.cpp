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
