#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "neuron.h"
#include "value.h"

using namespace std;

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

Neuron::Neuron(int numInputsToNeuron)
{
    // neuron will generally get fed output from every neuron in prev layer
    this->numInputs = numInputsToNeuron;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);
    this->weights.resize(numInputsToNeuron); // Resize the weights vector to match the number of inputs
    for (unsigned int i = 0; i < numInputsToNeuron; i++)
    {
        // will need one for every input we have
        this->weights[i] = Value(distribution(generator));
    }
    // single bias for the neuron
    this->bias = Value(distribution(generator));
}

// Type Neuron::functionName(PARAMETERS)
Value Neuron::operator()(vector<float> neuronInput)
{
    assert(neuronInput.size() == this->numInputs);
    float runningSum = this->bias.data;
    float activation = 0;
    for (unsigned int i = 0; i < this->numInputs; i++)
    {
        runningSum += (neuronInput[i] * this->weights[i].data);
    }
    Value sumNeuron = Value(runningSum);
    Value activationNeuron = sumNeuron.tanh();
    return activationNeuron;
}

Value Neuron::operator()(vector<Value> neuronInput)
{
    assert(neuronInput.size() == this->numInputs);
    float runningSum = this->bias.data;
    float activation = 0;
    vector<std::shared_ptr<Value>> allOperationsInNeuron(neuronInput.size() + 1);
    std::shared_ptr<Value> sumVal = std::make_shared<Value>(0);
    std::shared_ptr<Value> holdVal;

    for (unsigned int i = 0; i < this->numInputs; i++)
    {
        holdVal = std::make_shared<Value>(neuronInput[i] * this->weights[i]);
        allOperationsInNeuron[i] = holdVal;
        *sumVal = *holdVal + *sumVal;
    }

    std::shared_ptr<Value> tanHVal = std::make_shared<Value>(sumVal->tanh());

    // Add sumVal to prevValues of tanHVal
    tanHVal->prevValues.push_back(sumVal.get());

    return *tanHVal;
}