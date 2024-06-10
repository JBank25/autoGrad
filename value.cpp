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
    float grad = 0.0;
    std::function<void()> backward; // Lambda to update gradients

    /**
     * @brief Construct a new Value object with children AND input_data
     *
     * @param input_data - initialize Value object with input_data
     */
    Value(float input_data, const vector<Value *> &children, string op)
        : data(input_data), prevValues(children), op(op) {}

    /**
     * @brief Get the data field
     *
     * @return float
     */
    float getData(void)
    {
        return data;
    }

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
    Value(float input_data, string op) : data(input_data), op(op) {}

    /**
     * @brief Print the data member of Value obj. I miss python
     *
     */
    void printValue(void)
    {
        std::cout << "**Value Obj***\n"
                  << data << std::endl;
        std::cout << "Value data: " << data << std::endl;
        std::cout << "Value op: " << op << std::endl;
        std::cout << "Num Input Value Nodes: " << prevValues.size() << std::endl;
        for (unsigned int i = 0; i < prevValues.size(); i++)
        {
            prevValues[i]->printValue();
        }
    }

    Value operator*(Value &other)
    {
        Value result(this->data * other.data, "*"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);
        // Define the lambda function
        result.backward = [&other, this, &result]()
        {
            this->grad = (other.data) * (result.grad);
            other.grad = (this->data) * (result.grad);
        };
        return result;
    }

    Value operator+(Value &other)
    {
        Value result(this->data + other.data, "+"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);
        // Define the lambda function
        result.backward = [&other, this, &result]()
        {
            this->grad = 1.0 * result.grad;
            other.grad = 1.0 * result.grad;
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
        this->backward = [&tanh_val_node, this, tanh_output]()
        {
            // gradient for 'this' is deriv of tanh, CHAIN RULE STILL HERE!
            this->grad = (1 - exp2(tanh_output)) * tanh_val_node.grad;
        };
        return tanh_val_node;
    }
};

int main()
{
    Value valA(2.0);
}