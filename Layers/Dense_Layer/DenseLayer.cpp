#include "DenseLayer.h"
#include "LoadingDenseData.h"
#include <sstream>






void DenseLayer::randomInit() {
	for (size_t i = 0; i < outputSize; i++) {
		for (size_t j = 0; j < hiddenLayerSize; j++) {
			hiddenLayer[i][j] = Utils::getRandomNumber(-1, 1);
		}
		bias[i] = Utils::getRandomNumber(-1, 1);
	}
}



DenseLayer::DenseLayer()
{
}

DenseLayer::DenseLayer(size_t inputSize, size_t hiddenLayerSize, size_t outputSize) {
	this->hiddenLayerSize = hiddenLayerSize;
	this->inputSize = inputSize;
	this->outputSize = outputSize;

	this->hiddenLayer = Utils::createMatrix(hiddenLayerSize, outputSize);


	this->bias = std::vector<double>(outputSize);

	randomInit();
}

DenseLayer::DenseLayer(size_t inputSize, Utils::matrix hiddenLayer, std::vector<double> bias)
{
	this->inputSize = inputSize;
	this->hiddenLayerSize = hiddenLayer[0].size();
	this->outputSize = bias.size();

	this->bias = bias;
	this->hiddenLayer = hiddenLayer;
}

std::vector<double> DenseLayer::propagate(std::vector<double>& input) {
	std::vector<double> result(outputSize);

	for (size_t i = 0; i < outputSize; i++)
	{
		for (size_t j = 0; j < hiddenLayerSize; j++)
		{
			result[i] = 0;
			for (size_t k = 0; k < outputSize; k++)
			{
				result[i] += hiddenLayer[i][k] * input[k] + bias[k];
			}
		}
	}
	return result;
}

void DenseLayer::mutate(double weighChangeLimit, double chance) {
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < hiddenLayerSize; j++)
		{
			if (Utils::getRandomNumber(0, 100) < chance) {
				auto change = Utils::getRandomNumber(-weighChangeLimit, weighChangeLimit);
				hiddenLayer[i][j] += change;
			}
		}
		if (Utils::getRandomNumber(0, 100) < chance) {
			auto change = Utils::getRandomNumber(-weighChangeLimit, weighChangeLimit);
			bias[i] += change;
		}
	}
}

void DenseLayer::save(std::ofstream& file) {

	file << "denseBiasSize" << std::endl;
	file << this->bias.size() << std::endl;

	file << "denseInputSize" << std::endl;
	file << this->inputSize << std::endl;

	file << "denseBias" << std::endl;
	Utils::printVectorToFile(file, this->bias);

	file << "hiddenLayerSize" << std::endl;
	file << this->hiddenLayerSize << std::endl;

	file << "outputSize" << std::endl;
	file << this->outputSize << std::endl;

	file << "hiddenLayer" << std::endl;
	Utils::printMatrixToFile(file, this->hiddenLayer);
}

DenseLayer DenseLayer::load(std::string filename)
{

	std::ifstream file;
	file.open(filename);

	if (file.good() == false) {
		throw "File Loading Failed";
	}
	std::string currentLine;
	LoadingDenseData data;


	while (getline(file, currentLine)) {
		std::istringstream iss(currentLine);

		std::string temp;
		iss >> temp;


		if (temp == "denseBiasSize") {
			data.denseBiasSize = Utils::readNumber(file);
		}

		else if (temp == "denseInputSize") {
			data.denseInputSize = Utils::readNumber(file);
		}

		else if (temp == "denseBias") {
			data.denseBias = Utils::readVector(file, data.denseBiasSize);
		}

		else if (temp == "hiddenLayerSize") {
			data.hiddenLayerSize = Utils::readNumber(file);
		}

		else if (temp == "outputSize") {
			data.outputSize = Utils::readNumber(file);
		}

		else if (temp == "hiddenLayer") {
			data.hiddenLayer = Utils::readMatrix(file, data.hiddenLayerSize, data.outputSize);
		}

	}



	DenseLayer denseLayer = DenseLayer
	(
		data.denseInputSize,
		data.hiddenLayer,
		data.denseBias
	);

	file.close();

	return denseLayer;
}
