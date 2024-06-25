#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "neuron.h"
#include "utility.h"
#include "value.h"

using namespace std;

Neuron::Neuron(unsigned int numInputsToNeuron)
{
    // neuron will generally get fed output from every neuron in prev layer
    this->numInputs = numInputsToNeuron;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);
    this->weights.resize(numInputsToNeuron); // Resize the weights vector to match the number of inputs
    for (unsigned int i = 0; i < numInputsToNeuron; i++)
    {
        // will need one for every input we have
        this->weights[i] = Value(distribution(generator), "w");
    }
    // single bias for the neuron
    this->bias = Value(distribution(generator), "b");
}

std::shared_ptr<Value> Neuron::operator()(std::vector<Value> neuronInput)
{
    ASSERT_FMT(neuronInput.size() == this->numInputs, "Input size to neuron != # of inputs neuron accepts");

    auto sumVal = std::make_shared<Value>(this->bias);
    std::shared_ptr<Value> holdVal;
    std::shared_ptr<Value> sumHold;

    for (unsigned int i = 0; i < this->numInputs; i++)
    {
        holdVal = std::make_shared<Value>(neuronInput[i] * this->weights[i]);
        sumHold = std::make_shared<Value>(*sumVal + *holdVal);
        sumVal = sumHold;
    }

    // TODO: I DONT NEED to push sumVal as a prevValues on tanHVal right????
    // That is being handled in tanh isnt it???
    auto tanHVal = std::make_shared<Value>(sumVal->tanh());

    return tanHVal;
}

std::shared_ptr<Value> Neuron::operator()(std::vector<shared_ptr<Value>> neuronInput)
{
    ASSERT_FMT(neuronInput.size() == this->numInputs, "Input size to neuron != # of inputs neuron accepts");

    auto sumVal = std::make_shared<Value>(this->bias);
    std::shared_ptr<Value> holdVal;
    std::shared_ptr<Value> sumHold;

    for (unsigned int i = 0; i < this->numInputs; i++)
    {
        holdVal = std::make_shared<Value>(*neuronInput[i] * this->weights[i]);
        sumHold = std::make_shared<Value>(*sumVal + *holdVal);
        sumVal = sumHold;
    }

    // TODO: I DONT NEED to push sumVal as a prevValues on tanHVal right????
    // That is being handled in tanh isnt it???
    auto tanHVal = std::make_shared<Value>(sumVal->tanh());

    return tanHVal;
}
