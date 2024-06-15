#include <iostream>
#include <random>

class Neuron:
{
public:
    int numInputs;
    vector<Value> weights;
    Neuron(int numInputs)
    {
        for (unsigned int i = 0; i < numInputs; i++)
        {
            weights[i] = Value()
        }
    }
}