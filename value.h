#pragma once

#include <functional>
#include <vector>
#include <string>

using namespace std;

class Value
{
public:
    float data;
    std::vector<std::shared_ptr<Value>> prevValues;
    string op;
    string label = "";
    float grad = 0.0;
    bool _backward = false;

    // TODO: constructor cleanup
    Value(float input_data, const vector<Value *> &children, string op);
    Value(float input_data, string valLabel);
    Value(float input_data);
    Value(float input_data, string op, string valLabel);
    Value(){}; // Default constructor

    Value operator*(Value &other);
    Value operator*(shared_ptr<Value> &other);
    Value operator+(Value &other);
    Value operator-(Value &other);
    Value power(int power);
    Value tanh();
    void backwards();
    void backward();
};