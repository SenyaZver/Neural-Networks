#pragma once
#include <vector>
#include "../Common.h"
#include "../Brain.h"
#include "../Utils.h"
/*
* For small image
#define M1 30
#define N1 10
#define N2 10
#define M2 5
*/

#define M1 2700
#define N1 30
#define N2 30
#define M2 5

using std::vector;

class PerceptronBrain: public Brain
{
public:
    PerceptronBrain();
    ~PerceptronBrain();
    void generate(vector<size_t> params);
    void mutate(vector<double> params);
    PerceptronBrain* copy();
    vector<double> feedForward(
        matrix& const redInput,
        matrix& const greenInput,
        matrix& const blueInput
    );

    int n1 = N1, m1 = M1, n2 = N2, m2 = M2;
    size_t imgSquareSize = 30;

    matrix firstLayer;
    std::vector<double> firstBias;
    matrix secondLayer;
    std::vector<double> secondBias;


};

