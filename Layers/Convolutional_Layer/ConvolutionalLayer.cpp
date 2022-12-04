#include "ConvolutionalLayer.h"



double ConvolutionalLayer::cross(matrix& const first, matrix& const second)
{
	double result = 0;
	size_t size = first.size();

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			result += first[i][j] * second[i][j];
		}
	}
	return result;
}

matrix ConvolutionalLayer::getSubMatrix(matrix& inputLayer, size_t verticalOffset, size_t horizontalOffset)
{
	size_t size = filter1.size();
	auto result = createSquareMatrix(size);


	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			result[i][j] = inputLayer[i + verticalOffset][j + horizontalOffset];
		}
	}
	return result;
}



ConvolutionalLayer::ConvolutionalLayer(){}



void ConvolutionalLayer::activate(matrix& const layer)
{
	size_t size = layer.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			layer[i][j] = sigmoid(layer[i][j]);
		}
	}
}

void ConvolutionalLayer::randomInit()
{
	for (size_t i = 0; i < filterSize; i++) {
		for (size_t j = 0; j < filterSize; j++) {
			filter1[i][j] = getRandomNumber(-1, 1);
			filter2[i][j] = getRandomNumber(-1, 1);
			filter3[i][j] = getRandomNumber(-1, 1);
		}
	}

	for (size_t i = 0; i < resultSize; i++) {
		for (size_t j = 0; j < resultSize; j++) {
			bias[i][j] = getRandomNumber(-1, 1);
		}
	}

}

std::vector<std::vector<double>> ConvolutionalLayer::cross_correlate(matrix& inputLayer, matrix& filter)
{
	size_t size = inputLayer.size() - filter.size() + 1;



	auto result = createSquareMatrix(size);
	auto temp = createSquareMatrix(size);

	size_t verticalOffset = 0;
	size_t horizontalOffset = 0;


	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			temp = getSubMatrix(inputLayer, i, j);
			result[i][j] = cross(temp, filter);
		}
	}

	return result;
}


ConvolutionalLayer::ConvolutionalLayer(size_t inputSize, matrix filter1, matrix filter2, matrix filter3, matrix bias)
{
	this->filter1 = filter1;
	this->filter2 = filter2;
	this->filter3 = filter3;

	this->bias = bias;

	this->inputSize = inputSize;
	this->filterSize = filter1.size();
	this->resultSize = inputSize - this->filterSize + 1;

}

ConvolutionalLayer::ConvolutionalLayer(size_t filterSize, size_t inputSize)
{
	this->inputSize = inputSize;
	this->filterSize = filterSize;
	this->resultSize = inputSize - this->filterSize + 1;

	this->filter1 = createSquareMatrix(filterSize);
	this->filter2 = createSquareMatrix(filterSize);
	this->filter3 = createSquareMatrix(filterSize);


	bias = createSquareMatrix(resultSize);

	randomInit();
}

std::vector<std::vector<double>> ConvolutionalLayer::propagate(matrix& input1, matrix& input2, matrix& input3)
{
	if (input1.size() < filter1.size()) {
		throw "input size is larger than filter size";
	}


	auto result1 = cross_correlate(input1, filter1);
	auto result2 = cross_correlate(input2, filter2);
	auto result3 = cross_correlate(input3, filter3);


	auto result = createSquareMatrix(input1.size() - filter1.size() + 1);

	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result.size(); j++) {
			result[i][j] = (result1[i][j] + result2[i][j] + result3[i][j]) + bias[i][j];
		}
	}
	activate(result);
	return result;
}

void ConvolutionalLayer::mutate(double weighChangeLimit, double chance)
{
	for (size_t i = 0; i < filter1.size(); i++) {
		for (size_t j = 0; j < filter1.size(); j++) {
			if (getRandomNumber(0, 100) < chance) {
				double change = getRandomNumber(-weighChangeLimit, weighChangeLimit);
				filter1[i][j] += change;
				change = getRandomNumber(-weighChangeLimit, weighChangeLimit);
				filter2[i][j] += change;
				change = getRandomNumber(-weighChangeLimit, weighChangeLimit);
				filter3[i][j] += change;
			}
		}
	}

	for (size_t i = 0; i < bias.size(); i++) {
		for (size_t j = 0; j < bias.size(); j++) {
			double change = getRandomNumber(-weighChangeLimit, weighChangeLimit);
			bias[i][j] += change;
		}
	}
}
