#pragma once
#include <vector>
#include <fstream>

using std::vector;

namespace Utils {
	float calcYPos(int i, float basePos);
	float sigmoid(float x);
	vector<float>& setSigmoid(vector<float>& v);
	vector<float>& normalize(vector<float>& v);

	template <typename T>
	size_t getMaxVectorIndex(vector<T> v, size_t from, size_t to);

	vector<double> convertBrainResult(vector<double>& brainResult);

	typedef std::vector<std::vector<double>> matrix;
	typedef std::vector<std::vector<size_t>> intMatrix;


	void printVector(std::vector<double>& vec);

	void printSquareMatrix(matrix& const matrix);

	void printMatrix(matrix& const matrix);


	matrix createSquareMatrix(size_t size);


	matrix createMatrix(size_t verticalSize, size_t horizontalSize);


	double getRandomNumber(double begin, double end);

	double sigmoid(double const x);
	
	void printMatrixToFile(std::ofstream& file, matrix& matrix);
	void printVectorToFile(std::ofstream& file, std::vector<double>& vector);

	size_t readNumber(std::ifstream& file);
	std::vector<double> readVector(std::ifstream& file, size_t size);
	matrix readMatrix(std::ifstream& file, size_t verticalSize, size_t horizontalSize);
}