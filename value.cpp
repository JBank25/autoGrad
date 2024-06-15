#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

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

    /**
     * @brief Construct a new Value object with children AND input_data
     *
     * @param input_data - initialize Value object with input_data
     */
    Value(float input_data, const vector<Value *> &children, string op)
        : data(input_data), prevValues(children), op(op) {}

    /**
     * @brief Construct a new Value object with input_data
     *
     * @param input_data - initialize Value object with input_data
     */
    Value(float input_data, string valLabel) : data(input_data), label(valLabel) {}

    /**
     * @brief Construct a new Value object with input_data
     *
     * @param input_data - initialize Value object with input_data
     */
    Value(float input_data) : data(input_data) {}

    /**
     * @brief Construct a new Value object with input_data
     *
     * @param input_data - initialize Value object with input_data
     */
    Value(float input_data, string op, string valLabel) : data(input_data), op(op), label(valLabel) {}

    Value operator*(Value &other)
    {
        // TODO: Add support for something like valObj * 2
        Value result(this->data * other.data, "*"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);
        // Define the lambda function
        result._backward = [&other, this, &result]()
        {
            this->grad += (other.data) * (result.grad);
            other.grad += (this->data) * (result.grad);
            // std::cout << "Label: " << result.label << " Mul grad" << std::endl;
        };
        return result;
    }

    Value operator+(Value &other)
    {
        // TODO: Add support for something like valObj * 2
        Value result(this->data + other.data, "+"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);

        // Define the lambda function
        result._backward = [&other, this, &result]()
        {
            this->grad += 1.0 * result.grad;
            other.grad += 1.0 * result.grad;
            // std::cout << "Label: " << this->label << "Add grad" << std::endl;
        };
        return result;
    }

    /**
     * @brief Creates a new node whose value is tanh(x) where x is the data member
     * of the node which tanh is being called on
     *
     * @return Value new node whose data member is tanh(x) and child is the node in which
     * tanh was called on.
     */
    Value tanh()
    {
        float x = this->data;                                        // grab data from this node to be tanh'd
        float tanh_output = ((exp(2 * x) - 1) / ((exp(2 * x)) + 1)); // tanh the data
        Value tanh_val_node = Value(tanh_output, "tanh");            // create new node
        tanh_val_node.prevValues.push_back(this);                    // 'this' node should be its only prevValue
                                                                     // Define the lambda function
        tanh_val_node._backward = [&tanh_val_node, this, tanh_output]()
        {
            // gradient for 'this' is deriv of tanh, CHAIN RULE STILL HERE!
            this->grad += (1 - (tanh_output) * (tanh_output)) * tanh_val_node.grad;
            // std::cout << "Tanh grad label: " << this->label << std::endl;
        };
        this->_backward();
        return tanh_val_node;
    }

    void backward()
    {
        std::unordered_set<Value *> visited;
        vector<Value *> topoSort;
        topoSort.clear(); // Clear the vector before each call to the function

        std::function<void(Value *)> dfs = [&](Value *v)
        {
            if (visited.find(v) != visited.end())
                return;
            visited.insert(v);
            for (Value *child : v->prevValues)
            {
                dfs(child);
            }
            topoSort.push_back(v);
        };

        dfs(this);

        for (int i = topoSort.size() - 1; i >= 0; i--)
        {
            // std::cout << topoSort[i]->label << " Data:" << topoSort[i]->data << std::endl;
            if (topoSort[i]->_backward != nullptr)
            {
                topoSort[i]->_backward();
            }
        }
        for (int i = topoSort.size() - 1; i >= 0; i--)
        {
            std::cout << topoSort[i]->label << " grad: " << topoSort[i]->grad << std::endl;
        }
    }
};

int main()
{
    Value valA(2.0, "a");
    Value valB(-3.0, "b");
    Value valC(0.0, "c");
    Value valD(1.0, "d");
    Value valE = valA * valB;
    valE.label = "e";
    Value valF = valD * valC;
    valF.label = "f";
    Value valG = valF + valE;
    valG.label = "g";

    Value valH(6.8815, "h");
    Value valI = valH + valG;
    valI.label = "i";
    Value valJ = valI.tanh();
    valJ.label = "j";
    valJ.grad = 1;
    valJ.backward();
    // valE._backward();
    // std::cout << valA.grad << std::endl;
    // std::cout << valB.grad << std::endl;
}