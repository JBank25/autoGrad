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
    std::vector<std::shared_ptr<Value>> operator()(vector<Value> layerInput);
};
