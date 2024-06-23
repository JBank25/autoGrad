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
Value::Value(float input_data, string valLabel) : data(input_data), label(valLabel), grad(0.0) {}

Value::Value(float input_data) : data(input_data), grad(0.0) {}

Value::Value(float input_data, string op, string valLabel) : data(input_data), op(op), label(valLabel), grad(0.0) {}

Value Value::operator*(Value &other)
{
    Value result(this->data * other.data, "*");
    result.prevValues.push_back(std::make_shared<Value>(*this));
    result.prevValues.push_back(std::make_shared<Value>(other));
    result._backward = [&]()
    {
        this->grad += other.data * result.grad;
        other.grad += this->data * result.grad;
    };
    return result;
}

Value Value::operator*(shared_ptr<Value> &other)
{
    Value result(this->data * other->data, "*");
    result.prevValues.push_back(std::make_shared<Value>(*this));
    result.prevValues.push_back(other);
    result._backward = [&]()
    {
        this->grad += other->data * result.grad;
        other->grad += this->data * result.grad;
    };
    return result;
}

Value Value::operator+(Value &other)
{
    Value result(this->data + other.data, "+");
    result.prevValues.push_back(std::make_shared<Value>(*this));
    result.prevValues.push_back(std::make_shared<Value>(other));
    result._backward = [&]()
    {
        this->grad += result.grad;
        other.grad += result.grad;
    };
    return result;
}

Value Value::operator-(Value &other)
{
    Value result(this->data - other.data, "-");
    result.prevValues.push_back(std::make_shared<Value>(*this));
    result.prevValues.push_back(std::make_shared<Value>(other));
    result._backward = [&]()
    {
        this->grad += result.grad;
        other.grad -= result.grad;
    };
    return result;
}

Value Value::tanh()
{
    float x = this->data;
    float tanh_output = std::tanh(x);
    Value tanh_val_node = Value(tanh_output, "tanh");
    tanh_val_node.prevValues.push_back(std::make_shared<Value>(*this));
    tanh_val_node._backward = [this, tanh_output, &tanh_val_node]()
    {
        this->grad += (1 - tanh_output * tanh_output) * tanh_val_node.grad;
    };
    return tanh_val_node;
}

Value Value::power(int power)
{
    Value out = Value(std::pow(this->data, power), "pow");
    out.prevValues.push_back(std::make_shared<Value>(*this));
    out._backward = [this, power, &out]()
    {
        this->grad += power * std::pow(this->data, power - 1) * out.grad;
    };
    return out;
}

void Value::backward()
{
    std::vector<std::shared_ptr<Value>> visited;
    std::vector<std::shared_ptr<Value>> topoSort;

    std::function<void(std::shared_ptr<Value>)> dfs = [&](std::shared_ptr<Value> v)
    {
        if (!v)
            return;
        if (std::find(visited.begin(), visited.end(), v) != visited.end())
            return;
        visited.push_back(v);
        for (std::shared_ptr<Value> child : v->prevValues)
        {
            dfs(child);
        }
        topoSort.push_back(v);
    };

    dfs(std::make_shared<Value>(*this));

    for (int i = topoSort.size() - 1; i >= 0; i--)
    {
        if (topoSort[i]->_backward)
        {
            topoSort[i]->_backward();
        }
    }
}
