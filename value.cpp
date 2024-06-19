#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "value.h"

using namespace std;

// Value::Value(float input_data, const vector<Value *> &children, string op)
//     : data(input_data), prevValues(children), op(op) {}

Value::Value(float input_data, string valLabel) : data(input_data), label(valLabel) {}

Value::Value(float input_data) : data(input_data) {}

Value::Value(float input_data, string op, string valLabel) : data(input_data), op(op), label(valLabel) {}

Value Value::operator*(Value &other)
{
    if (typeid(other) != typeid(Value))
    {
        other = Value(other);
    }
    Value result(this->data * other.data, "*");
    result.prevValues.push_back((other));
    result.prevValues.push_back(*this);
    result._backward = [&other, this, &result]()
    {
        this->grad += (other.data) * (result.grad);
        other.grad += (this->data) * (result.grad);
    };
    return result;
}

Value Value::operator+(Value &other)
{
    if (typeid(other) != typeid(Value))
    {
        other = Value(other);
    }
    Value result(this->data + other.data, "+"); // create new Value using operands to '+'
    result.prevValues.push_back((other));
    result.prevValues.push_back(*this);

    // set our backwards function now
    result._backward = [&other, this, &result]()
    {
        // for addition, grad just flows backwards
        this->grad += 1.0 * result.grad;
        other.grad += 1.0 * result.grad;
    };
    return result;
}

Value Value::tanh()
{
    float x = this->data;
    float tanh_output = ((exp(2 * x) - 1) / ((exp(2 * x)) + 1));
    Value tanh_val_node = Value(tanh_output, "tanh");
    tanh_val_node.prevValues.push_back(*this);
    tanh_val_node._backward = [&tanh_val_node, this, tanh_output]()
    {
        this->grad += (1 - (tanh_output) * (tanh_output)) * tanh_val_node.grad;
    };

    return tanh_val_node;
}

void Value::backward()
{
    vector<Value> visited;
    std::vector<Value> topoSort;
    topoSort.clear();

    std::function<void(Value)> dfs = [&](Value v)
    {
        if (v.prevValues.size() == 0)
            return;
        for (int i = 0; i < visited.size(); i++)
        {
            if (visited[i].label == v.label && visited[i].grad == v.grad && visited[i].data == v.data && visited[i].prevValues.size() == v.prevValues.size())
                return;
            // Do something with *it
        }
        visited.push_back(v);
        for (Value child : v.prevValues) // Corrected type and dereferencing
        {
            dfs(child); // Passing the pointer correctly
        }
        topoSort.push_back(v);
    };

    dfs(*this);

    for (int i = topoSort.size() - 1; i >= 0; i--)
    {
        if (topoSort[i]._backward != nullptr)
        {
            topoSort[i]._backward();
        }
    }
    // for (int i = topoSort.size() - 1; i >= 0; i--)
    // {
    //     std::cout << topoSort[i]->label << " grad: " << topoSort[i]->grad << std::endl;
    // }
}
