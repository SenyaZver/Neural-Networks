#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "ConvolutionalBrain/ConvolutionBrain.h"
#include "ConvolutionalBrain/ConvolutionalLayer.h"
#include "PercepetronBrain/PerceptronBrain.h"
#include "Common.h"

class BrainSaver
{
private:

	std::string filePath;

	void printMatrixToFile(std::ofstream& file, matrix& matrix) {
		size_t horizontalSize = matrix.size();
		size_t verticalSize = matrix[0].size();


		for (size_t i = 0; i < horizontalSize; i++) {
			for (size_t j = 0; j < verticalSize; j++) {
				file << matrix[i][j] << " ";
			}
			file << std::endl;
		}
	}

	void printVectorToFile(std::ofstream& file, std::vector<double>& vector) {
		size_t size = vector.size();
		for (size_t i = 0; i < size; i++) {
			file << vector[i] << " ";
		}
		file << std::endl;
	}


	void saveConvLayer(std::ofstream& file, ConvolutionalLayer& layer) {
		auto filterSize = layer.getFilterSize();
		auto filters = layer.getFilters();
		auto bias = layer.getBias();

		file << "filterSize" << std::endl;
		file << filterSize << std::endl;

		file << "filter1" << std::endl;
		printMatrixToFile(file, filters[0]);

		file << "filter2" << std::endl;
		printMatrixToFile(file, filters[1]);

		file << "filter3" << std::endl;
		printMatrixToFile(file, filters[2]);

		file << "convBiasSize" << std::endl;
		file << bias.size() << std::endl;

		file << "convBias" << std::endl;
		printMatrixToFile(file, bias);

		file << std::endl << std::endl;
	}

	void saveReshapeLayer(std::ofstream& file, ReshapeLayer& layer) {
		size_t reshapeSize = layer.getSize();
		file << "denseInputSize" << std::endl;
		file << reshapeSize << std::endl << std::endl;
	}

	void saveDenseLayer(std::ofstream& file, DenseLayer& layer) {
		auto biasSize = layer.getBiasSize();
		auto bias = layer.getBias();
		auto hiddenLayerSize = layer.getHiddenLayerSize();
		auto outputSize = layer.getOutputSize();
		auto hiddenLayer = layer.getHiddenLayer();

		file << "denseBiasSize" << std::endl;
		file << biasSize << std::endl;

		file << "denseBias" << std::endl;
		printVectorToFile(file, bias);

		file << "hiddenLayerSize" << std::endl;
		file << hiddenLayerSize << std::endl;

		file << "outputSize" << std::endl;
		file << outputSize << std::endl;

		file << "hiddenLayer" << std::endl;
		printMatrixToFile(file, hiddenLayer);
	}


	void savePerceptronLayer(std::ofstream& file, size_t horizontalSize, size_t verticalSize, matrix& layer, size_t layerNumber) {
		file << "hiddenLayerHorizontalSize"<< layerNumber << std::endl << horizontalSize << std::endl;
		file << "hiddenLayerVerticalSize"<< layerNumber << std::endl << verticalSize << std::endl;


		file << "hiddenLayer" << layerNumber << std::endl;
		for (size_t i = 0; i < horizontalSize; i++) {
			for (size_t j = 0; j < verticalSize; j++) {
				file << layer[i][j] << " ";
			}
			file << std::endl;
		}
	}

	void savePerceptronBias(std::ofstream& file, size_t size, std::vector<double>& bias, size_t biasNumber) {
		file << "bias" << biasNumber <<"Size" << std::endl << size << std::endl;

		file << "bias" << biasNumber << std::endl;
		for (size_t i = 0; i < size; i++) {
			file << bias[i] << " ";
		}
		file << std::endl;
	}

public:
	BrainSaver(std::string path) {
		filePath = path;
	}

	bool save(PerceptronBrain& const brain, const std::string filename) {
		std::string fullpath = this->filePath + filename;

		std::ofstream file;
		file.precision(10);
		file.open(fullpath);

		if (file.good() == false) {
			return false;
		}

		auto layer1 = brain.firstLayer;
		auto layer2 = brain.secondLayer;

		auto bias1 = brain.firstBias;
		auto bias2 = brain.secondBias;


		savePerceptronLayer(file, brain.n1, brain.m1, layer1, 1);
		savePerceptronBias(file, brain.n1, bias1, 1);

		savePerceptronLayer(file, brain.n2, brain.m2, layer2, 2);
		savePerceptronBias(file, brain.n2, bias2, 2);

		file.close();
		return true;
	}


	bool save(ConvolutionBrain& const brain, const std::string filename) {
		std::string fullpath = this->filePath + filename;

		std::ofstream file;
		file.precision(10);
		file.open(fullpath);
		
		if (file.good() == false) {
			return false;
		}

		auto convLayer = brain.getConvLayer();
		auto reshapeLayer = brain.getReshapeLayer();
		auto denseLayer = brain.getDenseLayer();



		saveConvLayer(file, convLayer);
		saveReshapeLayer(file, reshapeLayer);
		saveDenseLayer(file, denseLayer);


		file.close();
		return true;
	}

	void setPath(std::string path) {
		this->filePath = path;
	}




};

