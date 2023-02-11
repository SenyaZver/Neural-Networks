#pragma once

#include "../BrainLoader.h"
#include "../Utils.h"
#include "../PercepetronBrain/PerceptronBrain.h"

void PerceptronTest() {
	size_t inputSize = 30;


	auto input = Utils::createSquareMatrix(inputSize);
	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			input[i][j] = 1;
		}
	}

	PerceptronBrain brain = PerceptronBrain();
	brain.generate(std::vector<size_t>());


	auto result = brain.feedForward(input, input, input);
	Utils::printVector(result);


	brain.save("D:\\screenshots\\perceptron.txt");

	PerceptronBrain brainCopy = PerceptronBrain();
	brainCopy.load("D:\\screenshots\\perceptron.txt");

	result = brainCopy.feedForward(input, input, input);
	Utils::printVector(result);

}