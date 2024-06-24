#pragma once

#include <iostream>
#include <random>
#include "value.h"
#include <vector>

class Neuron
{
public:
    unsigned int numInputs;
    vector<Value> weights;
    Value bias = NULL;
    Value sumValue;

    Neuron() = default; // Default constructor
    Neuron(unsigned int numInputs);
    std::shared_ptr<Value> operator()(std::vector<Value> neuronInput);
    std::shared_ptr<Value> operator()(std::vector<shared_ptr<Value>> neuronInput);
};
