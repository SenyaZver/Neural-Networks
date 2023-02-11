#pragma once
#include "../BrainLoader.h"
#include "../Utils.h"


void convTest() {
	size_t inputSize = 30;
	size_t filterSize = 5;
	size_t hiddenLayerSize = 20;
	size_t outputSize = 5;

	//init input
	auto input = Utils::createSquareMatrix(inputSize);
	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			input[i][j] = 1;
		}
	}

	std::vector<size_t> initParams = std::vector<size_t>{ inputSize, filterSize, hiddenLayerSize, outputSize };
	ConvolutionBrain test;
	test.generate(initParams);


	auto result = test.feedForward(input, input, input);
	Utils::printVector(result);

	std::cout << std::endl;


	std::vector<double> mutationParams{ 0.1, 70 };
	test.mutate(mutationParams);

	result = test.feedForward(input, input, input);
	Utils::printVector(result);

	std::cout << std::endl;

	test.save("D:\\screenshots\\test.txt");

	auto loaded = ConvolutionBrain();
	loaded.load("D:\\screenshots\\test.txt");


	result = loaded.feedForward(input, input, input);
	Utils::printVector(result);
}