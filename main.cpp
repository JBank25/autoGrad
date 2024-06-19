#include <iostream>
#include <cmath>
#include <vector>

#include "layer.h"
#include "neuron.h"
#include "value.h"

vector<int *> testFunc()
{
    int a = 20;
    int *aptr = &a;
    vector<int *> test({aptr});
    return test;
}

int main()
{

    int numNeurons = 2;
    Value testValA(-1, "A");
    Value testValB(1, "B");
    // Value testValC(4, "C");
    // Value testValC = testValA * testValB;
    // testValC.label = "C";
    // Value testValTan = testValC.tanh();
    // testValTan.label;
    // testValTan.grad = 1;
    // testValTan.backward();
    // Value test = *testValC.prevValues[0];
    Neuron testNeuron(numNeurons);
    Value testValue = testNeuron({testValA, testValB});
    testValue.backward();
}