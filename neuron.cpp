#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "neuron.h"
#include "value.h"

using namespace std;

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

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

// Type Neuron::functionName(PARAMETERS)
Value Neuron::operator()(vector<float> neuronInput)
{
    assert(neuronInput.size() == weights.size());
    float runningSum = bias.data;
    float activation = 0;
    for (unsigned int i = 0; i < neuronInput.size(); i++)
    {
        runningSum += (neuronInput[i] * weights[i].data);
    }
    Value sumNeuron = Value(runningSum);
    Value activationNeuron = sumNeuron.tanh();
    return activationNeuron;
}