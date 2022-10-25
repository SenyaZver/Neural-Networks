#pragma once
#pragma once
#include <vector>


using std::vector;

typedef std::vector<std::vector<double>> matrix;

class Brain
{
public:

    virtual void generate(vector<size_t> params) = 0;
    virtual void mutate(vector<double> params) = 0;
    virtual Brain* copy() = 0;
    virtual vector<double> feedForward(
        matrix& const redInput,
        matrix& const greenInput,
        matrix& const blueInput
    ) = 0;
    virtual ~Brain() = default;

    int parentNum;

};