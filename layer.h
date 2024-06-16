#pragma once

#include <vector>

#include "neuron.h"

class Layer
{
public:
    int inputsPerNeuron;
    int numNeuronsInLayer;
    vector<Neuron> neuronLayer;

    Layer(unsigned int inputsPerNeuron, unsigned int numNeuronsInLayer);
    vector<Value> operator()(vector<float> layerInput);
};