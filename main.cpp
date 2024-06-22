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

void testValue()
{
    Value testValA(-1, "A");
    Value testValB(2, "B");
    Value testValC = testValA + testValB;
    Value testValD(-1, "D");
    Value testValE = testValC * testValD;
    shared_ptr<Value> testShared = make_shared<Value>(testValA);
    testValE = testValC * testShared;
    Value testValF = testValE.tanh();
    testValF.grad = .55;
    testValF.backward();
    return;
}

void testNeuron()
{
    Value testValA(-1, "A");
    Value testValB(2, "B");
    Value testValC = testValA + testValB;
    Value testValD(-1, "D");
    int testNeuronInputs = 2;
    Neuron testNeuron(testNeuronInputs);
    shared_ptr<Value> testNeuronOut = testNeuron({testValA, testValB});
    testNeuronOut->backward();
    testNeuronOut->grad = .33;
    testNeuronOut->prevValues[0]->data = (testNeuronOut->prevValues[0]->data + testNeuronOut->prevValues[0]->grad);
    testNeuronOut->prevValues[1]->data = (testNeuronOut->prevValues[1]->data + testNeuronOut->prevValues[1]->grad);
    testNeuronOut = testNeuron({testValA, testValB});
    std::vector<shared_ptr<Value>> testNeuronInput = {make_shared<Value>(testValA), make_shared<Value>(testValB)};
    std::shared_ptr<Value> testNeuronOut2 = testNeuron(testNeuronInput);
    testNeuronOut2->grad = 0.55;
    testNeuronOut2->backward();
    return;
}

void testLayer()
{
    int inputsPerNeuron = 2;
    int neuronsInLayer = 2;
    Value testValA(-1, "A");
    Value testValB(2, "B");
    Layer testLayer(inputsPerNeuron, neuronsInLayer);
    std::vector<std::shared_ptr<Value>> testLayerOutput = testLayer({testValA, testValB});
    testLayerOutput[0]->grad = .33;
    testLayerOutput[1]->grad = .33;

    testLayerOutput[0]->prevValues[0]->backward();
    testLayerOutput[0]->prevValues[1]->backward();

    testLayerOutput[1]->prevValues[0]->backward();
    testLayerOutput[1]->prevValues[1]->backward();

    return;
}

void testDummyModel()
{
    int inputsPerNeuron = 2;
    int neuronsInLayer = 2;
    Value testValA(-1, "A");
    Value testValB(2, "B");
    Layer testLayer(inputsPerNeuron, neuronsInLayer);
    std::vector<std::shared_ptr<Value>> testLayerOutput = testLayer({testValA, testValB});

    int inputsInOutputLayer = 2;
    int numNeuronsInOutputLayer = 1;
    Layer outputLayer(inputsInOutputLayer, numNeuronsInOutputLayer);
    vector<Value> hold = {*testLayerOutput[0], *testLayerOutput[1]};
    std::vector<std::shared_ptr<Value>> output = outputLayer(hold);
    output[0]->grad = .33;
    return;
}

int main()
{
    testValue();
    testNeuron();
    testLayer();
}