#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "PercepetronBrain/LoadingPerceptronData.h"
#include "Layers/Convolutional_Layer/LoadingConvData.h"
#include "Utils.h"


class BrainLoader {
private:
	std::string filePath;
	
	size_t readNumber(std::ifstream& file) {
		size_t number;
		std::string currentLine;

		getline(file, currentLine);
		std::istringstream lineStream(currentLine);

		lineStream >> number;
		return number;
	}

	std::vector<double> readVector(std::ifstream& file, size_t size) {
		std::string currentLine;
		std::vector<double> vector = std::vector<double>(size);

		getline(file, currentLine);
		std::istringstream lineStream(currentLine);

		for (int i = 0; i < size; i++) {
			lineStream >> vector[i];
		}


		return vector;
	}

	matrix readMatrix(std::ifstream& file, size_t verticalSize, size_t horizontalSize) {
		std::string currentLine;
		matrix mat = Utils::createMatrix(verticalSize, horizontalSize);

		for (int i = 0; i < horizontalSize; i++) {
			getline(file, currentLine);
			std::istringstream lineStream(currentLine);

			for (int j = 0; j < verticalSize; j++) {
				lineStream >> mat[i][j];
			}
		}
		return mat;
	}


	LoadingPerceptronData readPerceptronDataFromFile(std::ifstream& file) {
		std::string currentLine;
		LoadingPerceptronData data;

		while (getline(file, currentLine)) {
			std::istringstream iss(currentLine);

			std::string temp;
			iss >> temp;

			if (temp == "hiddenLayerHorizontalSize1") {
				data.hiddenLayer1_horizontal = readNumber(file);


			} 
			else if (temp == "hiddenLayerVerticalSize1") {
				data.hiddenLayer1_vertical = readNumber(file);

			}
			else if (temp == "hiddenLayer1") {
				data.hiddenLayer1 = readMatrix(file, data.hiddenLayer1_vertical, data.hiddenLayer1_horizontal);
			}
			else if (temp == "bias1Size") {
				data.bias1_size = readNumber(file);
			}
			else if (temp == "bias1") {
				data.bias1 = readVector(file, data.bias1_size);
			}



			if (temp == "hiddenLayerHorizontalSize2") {
				data.hiddenLayer2_horizontal = readNumber(file);
			}
			else if (temp == "hiddenLayerVerticalSize2") {
				data.hiddenLayer2_vertical = readNumber(file);
			}
			else if (temp == "hiddenLayer2") {
				data.hiddenLayer2 = readMatrix(file, data.hiddenLayer1_vertical, data.hiddenLayer1_horizontal);
			}
			else if (temp == "bias2Size") {
				data.bias2_size = readNumber(file);
			}
			else if (temp == "bias2") {
				data.bias2 = readVector(file, data.bias1_size);
			}



		}

		return data;
	}

	
	LoadingConvData readConvDataFromFile(std::ifstream& file) {

		std::string currentLine;
		LoadingConvData data;


		while (getline(file, currentLine)) {
			std::istringstream iss(currentLine);

			std::string temp;
			iss >> temp;


			if (temp == "filterSize") {
				data.filterSize = readNumber(file);
			}

			else if (temp == "filter1") {
				data.filter1 = readMatrix(file, data.filterSize, data.filterSize);
			}

			else if (temp == "filter2") {
				data.filter2 = readMatrix(file, data.filterSize, data.filterSize);
			}

			else if (temp == "filter3") {
				data.filter3 = readMatrix(file, data.filterSize, data.filterSize);
			}

			else if (temp == "convBiasSize") {
				data.convBiasSize = readNumber(file);
			}

			else if (temp == "convBias") {
				data.convBias = readMatrix(file, data.convBiasSize, data.convBiasSize);
			}

			else if (temp == "denseInputSize") {
				data.denseInputSize= readNumber(file);
			}

			else if (temp == "denseBiasSize") {
				data.denseBiasSize = readNumber(file);
			}

			else if (temp == "denseBias") {
				data.denseBias = readVector(file, data.denseBiasSize);
			}
			else if (temp == "denseInputSize") {
				data.denseInputSize = readNumber(file);
			}


			else if (temp == "hiddenLayerSize") {
				data.hiddenLayerSize = readNumber(file);
			}

			else if (temp == "outputSize") {
				data.outputSize = readNumber(file);
			}

			else if (temp == "hiddenLayer") {
				data.hiddenLayer = readMatrix(file, data.hiddenLayerSize, data.outputSize);
			}

		}

		return data;
	}


public:
	BrainLoader(const std::string const filePath) {
		this->filePath = filePath;
	}


	void setPath(const std::string const path) {
		this->filePath = path;
	}

	ConvolutionBrain loadConvBrain(std::string filename) {
		std::string fullpath = this->filePath + filename;

		std::ifstream file;
		file.open(fullpath);

		if (file.good() == false) {
			throw "File Loading Failed";
		}

		LoadingConvData dataHolder = readConvDataFromFile(file);

		ConvolutionalLayer convLayer = ConvolutionalLayer
		(
			dataHolder.convInputSize,
			dataHolder.filter1,
			dataHolder.filter2,
			dataHolder.filter3,
			dataHolder.convBias
		);
		
		ReshapeLayer reshapeLayer = ReshapeLayer(dataHolder.denseInputSize);

		DenseLayer denseLayer = DenseLayer
		(
			dataHolder.denseInputSize,
			dataHolder.hiddenLayer,
			dataHolder.denseBias
		);

		ConvolutionBrain brain = ConvolutionBrain(convLayer, reshapeLayer, denseLayer);

		file.close();
		return brain;
	}


	PerceptronBrain loadPerceptronBrain(std::string filename) {
		std::string fullpath = this->filePath + filename;

		std::ifstream file;
		file.open(fullpath);

		if (file.good() == false) {
			throw "File Loading Failed";
	 }

		LoadingPerceptronData dataHolder = readPerceptronDataFromFile(file);


		PerceptronBrain brain = PerceptronBrain();
		
		brain.firstBias = dataHolder.bias1;
		brain.firstLayer = dataHolder.hiddenLayer1;

		brain.secondBias = dataHolder.bias2;
		brain.secondLayer = dataHolder.hiddenLayer2;

		return brain;
	}




	


};