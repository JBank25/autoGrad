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
    
    Neuron() = default; // Default constructor
    Neuron(int numInputs);
    Value operator()(vector<float> neuronInput);
};
