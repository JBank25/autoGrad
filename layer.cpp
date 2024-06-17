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
vector<Value> Layer::operator()(vector<float> layerInput)
{
    vector<Value> layerOut(layerInput.size());
    for (unsigned int i = 0; i < layerInput.size(); i++)
    {
        // layerOut[i] = neuronLayer[i]({layerInput[i]});
    }
    return layerOut;
}