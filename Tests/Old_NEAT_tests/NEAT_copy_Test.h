#pragma once
#include "../../ConvolutionalNEAT_Brain/ConvNEAT_Brain.h"
#include "../../Common.h"

void NEAT_copyTest() {
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
	

	//node genes copy correctly, but connection genes don't
	ConvNEAT_Brain* copy = test.copy();
	auto result2 = copy->feedForward(input, input, input);
	printVector(result2);

	
}
