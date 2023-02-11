#pragma once
#include <vector>
#include "../Brain.h"
#include "../Utils.h"
#include "LoadingPerceptronData.h"
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

class PerceptronBrain : public Brain
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

private:
    void savePerceptronLayer(std::ofstream& file, size_t horizontalSize, size_t verticalSize, matrix& layer, size_t layerNumber);
    void savePerceptronBias(std::ofstream& file, size_t size, std::vector<double>& bias, size_t biasNumber);

    LoadingPerceptronData readPerceptronDataFromFile(std::ifstream& file);

public:

    virtual void save(std::string filename);
    virtual void load(std::string filename);
};

