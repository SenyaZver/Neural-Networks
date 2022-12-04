#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "../../Common.h"


class DenseLayer {
private:
	size_t inputSize;
	size_t hiddenLayerSize;
	size_t outputSize;

	matrix hiddenLayer;
	std::vector<double> bias;


private:
	void randomInit();


public:
	DenseLayer();
	DenseLayer(size_t inputSize, size_t hiddenLayerSize, size_t outputSize);
	DenseLayer(size_t inputSize, matrix hiddenLayer, std::vector<double> bias);
	

	std::vector<double> propagate(std::vector<double>& input);

	void mutate(double weighChangeLimit, double chance);


	size_t getBiasSize() {
		return this->bias.size();
	}
	
	size_t getHiddenLayerSize() {
		return this->hiddenLayerSize;
	}

	matrix getHiddenLayer() {
		return this->hiddenLayer;
	}

	std::vector<double> getBias() {
		return this->bias;
	}
	
	size_t getOutputSize() {
		return this->outputSize;
	}
};
