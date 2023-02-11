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
	


	
	//LoadingConvData readConvDataFromFile(std::ifstream& file) {

	//	std::string currentLine;
	//	LoadingConvData data;


	//	while (getline(file, currentLine)) {
	//		std::istringstream iss(currentLine);

	//		std::string temp;
	//		iss >> temp;


	//		if (temp == "filterSize") {
	//			data.filterSize = readNumber(file);
	//		}

	//		else if (temp == "filter1") {
	//			data.filter1 = readMatrix(file, data.filterSize, data.filterSize);
	//		}

	//		else if (temp == "filter2") {
	//			data.filter2 = readMatrix(file, data.filterSize, data.filterSize);
	//		}

	//		else if (temp == "filter3") {
	//			data.filter3 = readMatrix(file, data.filterSize, data.filterSize);
	//		}
	
	//		else if (temp == "convBiasSize") {
	//			data.convBiasSize = readNumber(file);
	//		}

	//		else if (temp == "convBias") {
	//			data.convBias = readMatrix(file, data.convBiasSize, data.convBiasSize);
	//		}

	//		else if (temp == "denseInputSize") {
	//			data.denseInputSize= readNumber(file);
	//		}

	//		else if (temp == "denseBiasSize") {
	//			data.denseBiasSize = readNumber(file);
	//		}

	//		else if (temp == "denseBias") {
	//			data.denseBias = readVector(file, data.denseBiasSize);
	//		}
	//		else if (temp == "denseInputSize") {
	//			data.denseInputSize = readNumber(file);
	//		}


	//		else if (temp == "hiddenLayerSize") {
	//			data.hiddenLayerSize = readNumber(file);
	//		}

	//		else if (temp == "outputSize") {
	//			data.outputSize = readNumber(file);
	//		}

	//		else if (temp == "hiddenLayer") {
	//			data.hiddenLayer = readMatrix(file, data.hiddenLayerSize, data.outputSize);
	//		}

	//	}

	//	return data;
	//}


public:
	BrainLoader(const std::string const filePath) {
		this->filePath = filePath;
	}


	void setPath(const std::string const path) {
		this->filePath = path;
	}

	//ConvolutionBrain loadConvBrain(std::string filename) {
	//	std::string fullpath = this->filePath + filename;

	//	std::ifstream file;
	//	file.open(fullpath);

	//	if (file.good() == false) {
	//		throw "File Loading Failed";
	//	}

	//	LoadingConvData dataHolder = readConvDataFromFile(file);

	//	ConvolutionalLayer convLayer = ConvolutionalLayer
	//	(
	//		dataHolder.convInputSize,
	//		dataHolder.filter1,
	//		dataHolder.filter2,
	//		dataHolder.filter3,
	//		dataHolder.convBias
	//	);
	//	
	//	ReshapeLayer reshapeLayer = ReshapeLayer(dataHolder.denseInputSize);

	//	DenseLayer denseLayer = DenseLayer
	//	(
	//		dataHolder.denseInputSize,
	//		dataHolder.hiddenLayer,
	//		dataHolder.denseBias
	//	);

	//	ConvolutionBrain brain = ConvolutionBrain(convLayer, reshapeLayer, denseLayer);

	//	file.close();
	//	return brain;
	//}





	


};