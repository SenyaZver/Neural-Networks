#include "PerceptronBrain.h"
#include "../Utils.h"

PerceptronBrain::PerceptronBrain()
{
}
PerceptronBrain::~PerceptronBrain()
{
}


PerceptronBrain* PerceptronBrain::copy()
{
    // std::vector<int> v;
    PerceptronBrain* copyBrain = new PerceptronBrain();

    for (int i = 0; i < this->n1; i++)
    {
        for (int j = 0; j < this->m1; j++)
        {
            copyBrain->firstLayer[i][j] = this->firstLayer[i][j];
        }
        copyBrain->firstBias[i] = this->firstBias[i];
    }
    for (int i = 0; i < this->n2; i++)
    {
        for (int j = 0; j < this->m2; j++)
        {
            copyBrain->secondLayer[i][j] = this->secondLayer[i][j];
        }
        copyBrain->secondBias[i] = this->secondBias[i];
    }
    copyBrain->parentNum = this->parentNum;
    return copyBrain;
}

void PerceptronBrain::generate(vector<size_t> params)
{
    this->firstLayer = Utils::createMatrix(M1, N1);
    this->firstBias = std::vector<double>(N1);
    this->secondLayer = Utils::createMatrix(M2, N2);
    this->secondBias = std::vector<double>(N2);

    this->parentNum = int(Utils::getRandomNumber(0, 10000000));

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            this->firstLayer[i][j] = Utils::getRandomNumber(-1, 1);
        }
        this->firstBias[i] = Utils::getRandomNumber(-1, 1);
    }



    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            this->secondLayer[i][j] = Utils::getRandomNumber(-1, 1);
        }
        this->secondBias[i] = Utils::getRandomNumber(-1, 1);
    }
   
   
}

void PerceptronBrain::mutate(vector<double> params)
{
    float mut_num;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            mut_num = Utils::getRandomNumber(-0.05, 0.05);
            this->firstLayer[i][j] += mut_num;
            if (this->firstLayer[i][j] > 1) this->firstLayer[i][j] = 1;
            if (this->firstLayer[i][j] < -1) this->firstLayer[i][j] = -1;
        }
        mut_num = Utils::getRandomNumber(-0.05, 0.05);
        this->firstBias[i] += mut_num;
        if (this->firstBias[i] > 1) this->firstBias[i] = 1;
        if (this->firstBias[i] < -1) this->firstBias[i] = -1;
    }
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            mut_num = Utils::getRandomNumber(-0.05, 0.05);
            this->secondLayer[i][j] += mut_num;
            if (this->secondLayer[i][j] > 1) this->secondLayer[i][j] = 1;
            if (this->secondLayer[i][j] < -1) this->secondLayer[i][j] = -1;
        }
        mut_num = Utils::getRandomNumber(-0.05, 0.05);
        this->secondBias[i] += mut_num;
        if (this->secondBias[i] > 1) this->secondBias[i] = 1;
        if (this->secondBias[i] < -1) this->secondBias[i] = -1;
    }
}
vector<double> PerceptronBrain::feedForward(matrix& const redInput,
    matrix& const greenInput,
    matrix& const blueInput)
{
    vector<int> img(M1);
    for (int i = 0; i < imgSquareSize; ++i)
        for (int j = 0; j < imgSquareSize; ++j) img.push_back(redInput[i][j]);
    for (int i = 0; i < imgSquareSize; ++i)
        for (int j = 0; j < imgSquareSize; ++j) img.push_back(greenInput[i][j]);
    for (int i = 0; i < imgSquareSize; ++i)
        for (int j = 0; j < imgSquareSize; ++j) img.push_back(blueInput[i][j]);

    vector<float> firstRes(n1);
    vector<float> secondRes(n2);
    vector<double> direction(2);

    for (int i = 0; i < n1; i++)
    {
        firstRes[i] = 0;
        for (int j = 0; j < m1; j++)
        {
            firstRes[i] = firstRes[i] + this->firstLayer[i][j] * img[j];
        }
        firstRes[i] += this->firstBias[i];


    }
    firstRes = Utils::normalize(firstRes);
    firstRes = Utils::setSigmoid(firstRes);

    for (int i = 0; i < n2; i++)
    {
        secondRes[i] = 0;
        for (int j = 0; j < m2; j++)
        {
            secondRes[i] = secondRes[i] + this->secondLayer[i][j] * firstRes[j];

        }
        secondRes[i] += this->secondBias[i];
    }
    firstRes = Utils::setSigmoid(secondRes);

    if (secondRes[0] > secondRes[1])
    {
        direction[0] = 0;
    }
    else
    {
        direction[0] = 1;
    }
    if (secondRes[2] > secondRes[3])
    {
        if (secondRes[2] > secondRes[4])
            direction[1] = 1;
        else
            direction[1] = 0;
    }
    else
    {
        if (secondRes[3] > secondRes[4])
            direction[1] = -1;
        else
            direction[1] = 0;
    }
    return direction;
}