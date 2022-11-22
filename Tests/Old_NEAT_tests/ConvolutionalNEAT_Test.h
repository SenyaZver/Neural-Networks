#pragma once
#include <vector>
#include "../../ConvolutionalNEAT_Brain/NEAT_layer.h"
#include <iostream>
#include "../../ConvolutionalNEAT_Brain/ConvNEAT_Brain.h"



void convNEAT_test() {

	size_t inputSize = 30;
	size_t filterSize = 5;
	size_t hiddenLayerSize = 20;
	size_t outputSize = 5;

	//init input
	auto input = createSquareMatrix(inputSize);
	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			input[i][j] = 1;
		}
	}

	std::vector<size_t> initParams = std::vector<size_t>{ inputSize, filterSize, hiddenLayerSize, outputSize };
	ConvNEAT_Brain test;
	test.generate(initParams);
	auto result = test.feedForward(input, input, input);
	printVector(result);
}