#pragma once
#include <vector>
#include <iostream>


#include "../Brain.h"
#include "../Layers/Convolutional_Layer/ConvolutionalLayer.h"
#include "../Layers/Reshape_Layer/ReshapeLayer.h"
#include "../Layers/Dense_Layer/DenseLayer.h"

//TODO fix fixed sizes
class ConvolutionBrain: public Brain {
private:
	ConvolutionalLayer conv;
	ReshapeLayer reshape;
	DenseLayer dense;


public:
	ConvolutionBrain(size_t inputSize, size_t filterSize, size_t hiddenLayerSize, size_t outputSize) : conv(filterSize, inputSize),
		reshape((inputSize + 1 - filterSize)* (inputSize + 1 - filterSize)),
		dense((inputSize + 1 - filterSize)* (inputSize + 1 - filterSize), hiddenLayerSize, outputSize) {}

	ConvolutionBrain(ConvolutionalLayer conv, ReshapeLayer reshape, DenseLayer dense) {
		this->conv = conv;
		this->reshape = reshape;
		this->dense = dense;
	}

	ConvolutionBrain() {}

	void generate(std::vector<size_t> params) {
		this->conv = ConvolutionalLayer(params[1], params[0]);
		size_t denseInputSize = (params[0] + 1 - params[1]) * (params[0] + 1 - params[1]);
		this->reshape = ReshapeLayer(denseInputSize);
		this->dense = DenseLayer(denseInputSize, params[2], params[3]);
	}


	ConvolutionBrain* copy() {
		ConvolutionBrain* newBrain = new ConvolutionBrain();
		newBrain->conv = this->getConvLayer();
		newBrain->reshape = this->getReshapeLayer();
		newBrain->dense = this->getDenseLayer();
		
		return newBrain;
	}



	std::vector<double> feedForward(matrix& const input1,
									 matrix& const input2, 
									 matrix& const input3)
	{
		auto convResult = conv.propagate(input1, input2, input3);
		auto reshapeResult = reshape.propagate(convResult);
		auto denseResult = dense.propagate(reshapeResult);

		return Utils::convertBrainResult(denseResult);
	}

	void mutate(double weightChangeLimit, int chance) {
		this->conv.mutate(weightChangeLimit, chance);
		this->dense.mutate(weightChangeLimit, chance);
	}

	//params[0] = weightChangeLimit, params[1] = chance
	void mutate(std::vector<double> params) {
		this->conv.mutate(params[0], params[1]);
		this->dense.mutate(params[0], params[1]);
	}

public:

	DenseLayer getDenseLayer() {
		return this->dense;
	}

	ConvolutionalLayer getConvLayer() {
		return this->conv;
	}

	ReshapeLayer getReshapeLayer() {
		return this->reshape;
	}

	bool save(const std::string filePath, const std::string fileName) {
		std::string fullpath = filePath + fileName;

		std::ofstream file;
		file.precision(10);
		file.open(fullpath);

		if (file.good() == false) {
			return false;
		}


		this->conv.save(file);
		this->reshape.save(file);
		this->dense.save(file);

		file.close();
		return true;
	}

	virtual void save(std::string filename) {
		std::ofstream file;
		file.precision(10);
		file.open(filename);


		this->conv.save(file);
		this->reshape.save(file);
		this->dense.save(file);

		file.close();
	}

	virtual void load(std::string filename) {
		DenseLayer dense = DenseLayer::load(filename);
		ReshapeLayer reshape = ReshapeLayer::load(filename);
		ConvolutionalLayer conv = ConvolutionalLayer::load(filename);

		this->conv = conv;
		this->reshape = reshape;
		this->dense = dense;
	}



};

