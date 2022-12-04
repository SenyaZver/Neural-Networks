#include "Utils.h"
#include <random>
#include <iostream>

namespace Utils {

	float calcYPos(int i, float basePos) {
		if (i % 2) return -1 * basePos;
		else return basePos;
	}

	float sigmoid(float x)
	{
		return 1 / (abs(x) + 1);
	}

	vector<float>& setSigmoid(vector<float>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			v[i] = sigmoid(v[i]);
		}
		return v;
	}

	vector<float>& normalize(vector<float>& v)
	{
		float norm = 0;
		float sq_sum = 0;
		for (int i = 0; i < v.size(); ++i)
		{
			sq_sum += v[i] * v[i];;
		}
		norm = sqrt(sq_sum);
		for (int i = 0; i < v.size(); i++)
		{
			v[i] /= norm;
		}
		return v;
	}

	template <typename T>
	size_t getMaxVectorIndex(vector<T> v, size_t from, size_t to)
	{
		size_t maxIndex = 0;
		T maxElem = v[from];
		for (size_t i = from; i < to; i++) {
			if (maxElem < v[i]) {
				maxElem = v[i];
				maxIndex = i;
			}
		}
		return maxIndex;
	}

	// Standart brain result conderter from 5-element float vector to 2-elements int vector.
	vector<int> convertBrainResult(vector<double>& brainResult) {
		vector<int> res(2);
		if (brainResult[0] > brainResult[1])
			res[0] = 0;
		else
			res[0] = 1;

		if (brainResult[2] > brainResult[3])
			if (brainResult[2] > brainResult[4])
				res[1] = 1;
			else
				res[1] = 0;
		else
			if (brainResult[3] > brainResult[4])
				res[1] = -1;
			else
				res[1] = 0;

		return res;

	}


	//common 

	void printVector(std::vector<double>& vec) {
		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}

	void printSquareMatrix(matrix& const matrix) {
		size_t size = matrix.size();
		for (size_t i = 0; i < size; i++) {
			for (size_t j = 0; j < size; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;;
		}
	}

	void printMatrix(matrix& const matrix) {
		size_t horizontalSize = matrix.size();
		size_t verticalSize = matrix[0].size();

		for (size_t i = 0; i < horizontalSize; i++) {
			for (size_t j = 0; j < verticalSize; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;;
		}

	}


	matrix createSquareMatrix(size_t size) {
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



	matrix createMatrix(size_t verticalSize, size_t horizontalSize) {
		std::vector<std::vector<double>> result(horizontalSize);
		for (size_t i = 0; i < horizontalSize; i++) {
			result[i].resize(verticalSize);
		}
		return result;
	}


	double getRandomNumber(double begin, double end) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(begin, end);

		return dis(gen);
	}

	double sigmoid(double const x) {
		return 1 / (1 + exp(-x));
	}
}