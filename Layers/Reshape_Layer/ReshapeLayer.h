#pragma once
#include <vector>
#include <iostream>
#include "../../Common.h"



class ReshapeLayer {
private:
	size_t size;


	std::vector<double> reshape(matrix inputLayer) {
		auto result = std::vector<double>(size);

		size_t index = 0;

		for (size_t i = 0; i < inputLayer.size(); i++) {
			for (size_t j = 0; j < inputLayer.size(); j++) {
				result[index] = inputLayer[i][j];
				index++;
			}
		}

		return result;
	}

public:
	ReshapeLayer() {}

	ReshapeLayer(size_t size) {
		this->size = size;
	}

	



	std::vector<double> propagate(matrix& const input) {
		return this->reshape(input);
	}


	size_t getSize() {
		return size;
	}







};