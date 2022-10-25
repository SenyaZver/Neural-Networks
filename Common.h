#pragma once
#include <vector>
#include <iostream>
#include "Common.h"
#include <random>


//Conv Brain Common
typedef std::vector<std::vector<double>> matrix;

inline void log(std::string message) {
	std::cout << std::endl << "debug" << std::endl << message << std::endl << std::endl;
}

inline void printVector(std::vector<double>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

inline void printSquareMatrix(matrix& const matrix) {
	size_t size = matrix.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;;
	}
}

inline void printMatrix(matrix& const matrix) {
	size_t horizontalSize = matrix.size();
	size_t verticalSize = matrix[0].size();

	for (size_t i = 0; i < horizontalSize; i++) {
		for (size_t j = 0; j < verticalSize; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;;
	}

}


inline matrix createSquareMatrix(size_t size) {
	matrix result(size);
	for (size_t i = 0; i < size; i++) {
		result[i].resize(size);
	}

	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result.size(); j++) {
			result[i][j] = 0;
		}
	}
	return result;
}


inline std::vector<double> createVector(size_t size) {

}

inline matrix createMatrix(size_t verticalSize, size_t horizontalSize) {
	std::vector<std::vector<double>> result(horizontalSize);
	for (size_t i = 0; i < horizontalSize; i++) {
		result[i].resize(verticalSize);
	}
	return result;
}


inline double getRandomNumber(double begin, double end) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(begin, end);

	return dis(gen);
}

inline double sigmoid(double const x) {
	return 1 / (1 + exp(-x));
}
//



