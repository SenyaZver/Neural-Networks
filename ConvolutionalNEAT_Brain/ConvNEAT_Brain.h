#pragma once
#include "../Brain.h"
#include <vector>
#include <iostream>
#include "../Layers/Convolutional_Layer/ConvolutionalLayer.h"
#include "../Layers/Reshape_Layer/ReshapeLayer.h"
#include "../Layers/NEAT_Layer/NEAT.h"



class ConvNEAT_Brain : public Brain {
private:
	ConvolutionalLayer conv;
	ReshapeLayer reshape;
	NEAT neat;

public:
	ConvNEAT_Brain() {

	}

	ConvNEAT_Brain(size_t inputSize, size_t filterSize, size_t outputSize, size_t hiddenLayerSize) :conv(filterSize, inputSize),reshape((inputSize + 1 - filterSize)* (inputSize + 1 - filterSize)) {
		neat.createSingleLayerPerceptron((inputSize + 1 - filterSize) * (inputSize + 1 - filterSize), hiddenLayerSize, outputSize);
	}


	//[0] = inputSize
	//[1] = filterSize,
	//[2] = hiddenLayerSize
	//[3] = outputSize
	void generate(std::vector<size_t> params) {
		this->conv = ConvolutionalLayer(params[1], params[0]);

		size_t denseInputSize = (params[0] + 1 - params[1]) * (params[0] + 1 - params[1]);
		this->reshape = ReshapeLayer(denseInputSize);
		this->neat.createSingleLayerPerceptron(denseInputSize, params[2], params[3]);
	}


	//[0] = weightChangeLimit
	//[1] = weightChange chance
	//[2] = addConnection chance
	//[3] = addHiddenGene chance
	void mutate(std::vector<double> params) {
		this->conv.mutate(params[0], params[1]);
		this->neat.mutate(params[2], params[3], params[1], params[0]);
	}

	//fix doesn't do anything
	ConvNEAT_Brain* copy() {
		ConvNEAT_Brain* newBrain = new ConvNEAT_Brain();

		ConvolutionalLayer newConv = this->conv;
		ReshapeLayer newReshape = this->reshape;
		NEAT newNeat = this->neat;

		
		newBrain->conv = newConv;
		newBrain->reshape = newReshape;
		newBrain->neat = newNeat;


		return newBrain;
	}


	std::vector<double> feedForward(
		matrix& const input1,
		matrix& const input2,
		matrix& const input3
	) {
		auto convResult = conv.propagate(input1, input2, input3);
		auto reshapeResult = reshape.propagate(convResult);
		auto neatResult = neat.propogate(reshapeResult);

		return Utils::convertBrainResult(neatResult);
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
		this->neat.save(file);

		file.close();
		return true;
	}


	virtual void save(std::string filename) {

		std::ofstream file;
		file.precision(10);
		file.open(filename);




		this->conv.save(file);
		this->reshape.save(file);
		this->neat.save(file);

		file.close();
	}

	virtual void load(std::string filename) {
		ReshapeLayer reshape = ReshapeLayer::load(filename);
		ConvolutionalLayer conv = ConvolutionalLayer::load(filename);
		NEAT neat = NEAT::load(filename);

		this->conv = conv;
		this->reshape = reshape;
		this->neat = neat;
	}
	




};