#pragma once

#include "../BrainSaver.h"
#include "../BrainLoader.h"
#include "../Utils.h"

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


	BrainSaver saver = BrainSaver("D:\\screenshots\\");

	saver.save(brain, "perceptron.txt");
	
	BrainLoader loader = BrainLoader("D:\\screenshots\\");
	auto brainCopy = loader.loadPerceptronBrain("perceptron.txt");


	result = brainCopy.feedForward(input, input, input);
	Utils::printVector(result);
}