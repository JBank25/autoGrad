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
    Value testValA(2, "A");
    Value testValB(2, "B");
    Value testValC = testValA + testValB;
    testValC.label = "C";
    Value testValTan = testValC.tanh();
    Value test = *testValC.prevValues[0];
}