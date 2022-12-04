#pragma once
#include "../Brain.h"
#include "../Common.h"
#include <vector>
#include <iostream>
#include "../Layers/Convolutional_Layer/ConvolutionalLayer.h"
#include "../Layers/Reshape_Layer/ReshapeLayer.h"
#include "../Layers/Old_NEAT_Layer/NEAT_layer.h"



class ConvNEAT_Brain : public Brain {
private:
	ConvolutionalLayer conv;
	ReshapeLayer reshape;
	NEAT_layer neat;

public:
	ConvNEAT_Brain() {

	}

	ConvNEAT_Brain(size_t inputSize, size_t filterSize, size_t outputSize, size_t hiddenLayerSize) :conv(filterSize, inputSize),reshape((inputSize + 1 - filterSize)* (inputSize + 1 - filterSize)) {
		neat.createDefault((inputSize + 1 - filterSize) * (inputSize + 1 - filterSize), hiddenLayerSize, outputSize);
	}


	//[0] = inputSize
	//[1] = filterSize,
	//[2] = hiddenLayerSize
	//[3] = outputSize
	void generate(std::vector<size_t> params) {
		this->conv = ConvolutionalLayer(params[1], params[0]);

		size_t denseInputSize = (params[0] + 1 - params[1]) * (params[0] + 1 - params[1]);
		this->reshape = ReshapeLayer(denseInputSize);
		this->neat.createDefault(denseInputSize, params[2], params[3]);
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
		NEAT_layer newNeat = *this->neat.clone();

		
		newBrain->conv = newConv;
		newBrain->reshape = newReshape;
		newBrain->neat = newNeat;


		return newBrain;
	}


	std::vector<double> feedForward(matrix& const input1,
		matrix& const input2,
		matrix& const input3)
	{
		
		auto convResult = conv.propagate(input1, input2, input3);
		auto reshapeResult = reshape.propagate(convResult);
		auto neatResult = neat.propogate(reshapeResult);

		vector<double> direction(2);



		if (neatResult[0] > neatResult[1])
		{
			direction[0] = 0;
		}
		else
		{
			direction[0] = 1;
		}
		if (neatResult[2] > neatResult[3])
		{
			if (neatResult[2] > neatResult[4])
				direction[1] = 1;
			else
				direction[1] = 0;
		}
		else
		{
			if (neatResult[3] > neatResult[4])
				direction[1] = -1;
			else
				direction[1] = 0;
		}
		return direction;


	}
	




};