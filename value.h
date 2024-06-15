#ifndef VALUE_H
#define VALUE_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

class Value
{
public:
    float data;
    vector<Value *> prevValues;
    string op;
    string label;
    float grad = 0.0;
    std::function<void()> _backward = nullptr; // Lambda to update gradients

    Value(float input_data, const vector<Value *> &children, string op);
    Value(float input_data, string valLabel);
    Value(float input_data);
    Value(float input_data, string op, string valLabel);

    Value operator*(Value &other);
    Value operator+(Value &other);
    Value tanh();
    void backward();
};

#endif // VALUE_H
