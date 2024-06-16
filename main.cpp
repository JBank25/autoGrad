#include <iostream>
#include <cmath>

#include "layer.h"
#include "neuron.h"
#include "value.h"

int main()
{
    int numNeurons = 2;
    Neuron testNeuron(numNeurons);
    for (int i = 0; i < numNeurons; i++)
    {
        std::cout << testNeuron.weights[i].data << std::endl;
    }

    std::cout << testNeuron.bias.data << std::endl;
    vector<float> testData = {1.0, 50.0};
    Layer testLayer(2, 3);
    vector<Value> layerOutNeurons = testLayer({1.0, 1.0});
    std::cout << "Test Layer Neurons: " << testLayer.neuronLayer[0].bias.data << testLayer.neuronLayer[0].weights[0].data << std::endl;
    // std::cout << testLayer.neuronLayer[0].<< std::endl;
}