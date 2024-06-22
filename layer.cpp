#include "layer.h"

// input params to contructor will be number of inputs per node and number
// of nodes in the layer

Layer::Layer(unsigned int inputsPerNeuron, unsigned int numNeuronsInLayer)
{
    this->inputsPerNeuron = inputsPerNeuron;
    this->numNeuronsInLayer = numNeuronsInLayer;
    // resize our vector holding the neurons in this layer
    this->neuronLayer.resize(numNeuronsInLayer);
    for (unsigned int i = 0; i < numNeuronsInLayer; i++)
    {
        // create new neuron with given num of inputs
        Neuron newNeuron(inputsPerNeuron);
        this->neuronLayer[i] = newNeuron;
    }
}

// Type Neuron::functionName(PARAMETERS)
std::vector<std::shared_ptr<Value>> Layer::operator()(vector<Value> layerInput)
{
    std::vector<std::shared_ptr<Value>> layerOut(this->numNeuronsInLayer);
    // Input vector should be called on every neuron
    for (int i = 0; i < this->numNeuronsInLayer; i++)
    {
        Neuron thisNeuron = this->neuronLayer[i];

        layerOut[i] = thisNeuron(layerInput);
    }
    return layerOut;
}