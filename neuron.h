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

    Neuron(int numInputs);
};
