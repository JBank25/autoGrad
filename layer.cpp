#include "layer.h"

// input params to contructor will be number of inputs per node and number
// of nodes in the layer

Layer::Layer(unsigned int inputsPerNeuron, unsigned int numNeuronsInLayer)
{
    // resize our vector holding the neurons in this layer
    neuronLayer.resize(numNeuronsInLayer);
    for (unsigned int i = 0; i < numNeuronsInLayer; i++)
    {
        // create new neuron with given num of inputs
        Neuron newNeuron(inputsPerNeuron);
        neuronLayer[i] = newNeuron;
    }
}
