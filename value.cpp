#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Value
{
    float data;
    vector<Value *> prevValues;
    string op;
    float grad = 0.0;

public:
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

    // Define equality operator for unordered_set
    bool operator==(const Value &other) const
    {
        return data == other.data;
    }

    Value mult(const Value &other)
    {
        Value result(this->data * other.data, "*"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);
        return result;
    }

    Value add(const Value &other)
    {
        Value result(this->data + other.data, "+"); // is creating this locally here problematic for its persistence??
        result.prevValues.push_back(const_cast<Value *>(&other));
        result.prevValues.push_back(this);
        return result;
    }

    Value tanh()
    {
        float x = this->data;
        float tanh_output = ((exp(2 * x) - 1) / ((exp(2 * x)) + 1));
        Value tanh_val_node = Value(tanh_output, "tanh");
        tanh_val_node.prevValues.push_back(this);
        return tanh_val_node;
    }
};

int main()
{
    Value valA(2.0);
    Value valB(-3.0);
    Value valC(10.0);
    Value valE = (valA.mult(valB));
    Value valD = valE.add(valC);
    Value valF(-2.0);
    Value valL = valD.mult(valF);
    valL.printValue();
}