#pragma once

#include <iostream>
#include <random>
#include "value.h"
#include <vector>

class Neuron
{
public:
    int numInputs;
    vector<Value> weights;
    Value bias = NULL;
    Value sumValue;

    Neuron() = default; // Default constructor
    Neuron(int numInputs);
    std::shared_ptr<Value> operator()(std::vector<Value> neuronInput);
    void backward();
};
