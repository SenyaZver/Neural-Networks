#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "../../Common.h"


//rushed code, fix handling different amount of filters


class ConvolutionalLayer
{

private:
	size_t inputSize;
	size_t filterSize;
	size_t resultSize;

	matrix filter1;
	matrix filter2;
	matrix filter3;

	matrix bias;


private:
	void randomInit();

	void activate(matrix& const layer);


	double cross(matrix& const first, matrix& const second);
	matrix getSubMatrix(matrix& inputLayer, size_t verticalOffset, size_t horizontalOffset);


	matrix cross_correlate(matrix& inputLayer, matrix& filter);


public:
	ConvolutionalLayer(size_t newFilterSize, size_t newInputSize);
	ConvolutionalLayer(size_t inputSize, matrix filter1, matrix filter2, matrix filter3, matrix bias);
	ConvolutionalLayer();

	matrix propagate(matrix& input1, matrix& input2, matrix& input3);

	void mutate(double weightChangeLimit, double chance);


	size_t getFilterSize() {
		return this->filterSize;
	}

	size_t getBiasSize() {
		return this->resultSize;
	}

	std::vector<matrix> getFilters() {
		std::vector<matrix> filters =  std::vector<matrix>(3);
		filters[0] = filter1;
		filters[1] = filter2;
		filters[2] = filter3;

		return filters;
	}

	matrix getBias() {
		return bias;
	}


};