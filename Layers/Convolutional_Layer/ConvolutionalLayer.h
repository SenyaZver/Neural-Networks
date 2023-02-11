#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "../../Utils.h"
#include "LoadingConvData.h"


//rushed code, fix handling different amount of filters


class ConvolutionalLayer
{

private:
	size_t inputSize;
	size_t filterSize;
	size_t resultSize;

	Utils::matrix filter1;
	Utils::matrix filter2;
	Utils::matrix filter3;

	Utils::matrix bias;


private:
	void randomInit();

	void activate(Utils::matrix& const layer);


	double cross(Utils::matrix& const first, Utils::matrix& const second);
	Utils::matrix getSubMatrix(Utils::matrix& inputLayer, size_t verticalOffset, size_t horizontalOffset);


	Utils::matrix cross_correlate(Utils::matrix& inputLayer, Utils::matrix& filter);


public:
	ConvolutionalLayer(size_t newFilterSize, size_t newInputSize);
	ConvolutionalLayer(size_t inputSize, Utils::matrix& filter1, Utils::matrix& filter2, Utils::matrix& filter3, Utils::matrix& bias);
	ConvolutionalLayer();

	Utils::matrix propagate(Utils::matrix& input1, Utils::matrix& input2, Utils::matrix& input3);

	void mutate(double weightChangeLimit, double chance);

	void save(std::ofstream& file);
	static ConvolutionalLayer load(std::string filename);

	size_t getFilterSize() {
		return this->filterSize;
	}

	size_t getBiasSize() {
		return this->resultSize;
	}

	std::vector<Utils::matrix> getFilters() {
		std::vector<Utils::matrix> filters =  std::vector<Utils::matrix>(3);
		filters[0] = filter1;
		filters[1] = filter2;
		filters[2] = filter3;

		return filters;
	}

	Utils::matrix getBias() {
		return bias;
	}

private:
	static LoadingConvData readConvDataFromFile(std::ifstream& file);


};