#include <iostream>
#include <random>
#include "value.h"
#include <vector>

// using namespace std;

// class Neuron
// {
// public:
//     int numInputs;
//     vector<Value> weights;
//     Value bias = NULL;
//     Neuron(int numInputs)
//     {
//         std::default_random_engine generator;
//         std::uniform_real_distribution<double> distribution(-1, 1);
//         for (unsigned int i = 0; i < numInputs; i++)
//         {
//             weights[i] = Value(1);
//         }
//         bias = Value(1);
//     }
// };

int main()
{
    Value valA(2.0);
    // Value valB(-3.0, "b");
    // Value valC(0.0, "c");
    // Value valD(1.0, "d");
    // Value valE = valA * valB;
    // valE.label = "e";
    // Value valF = valD * valC;
    // valF.label = "f";
    // Value valG = valF + valE;
    // valG.label = "g";

    // Value valH(6.8815, "h");
    // Value valI = valH + valG;
    // valI.label = "i";
    // Value valJ = valI.tanh();
    // valJ.label = "j";
    // valJ.grad = 1;
    // valJ.backward();
    // // valE._backward();
    // // std::cout << valA.grad << std::endl;
    // // std::cout << valB.grad << std::endl;

    // Neuron testNeuron = Neuron(10);
    // if (testNeuron.bias.data == 1)
    // {
    //     testNeuron.bias.data = 0;
    // }
}