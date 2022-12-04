#pragma once
#include <vector>
#include "Node_gene.h"
#include "Connection_gene.h"

class NEAT_layer
{
private:

	//std::vector<Connection_gene*> connectionGenes;
	std::vector<Node_gene*> inputGenes;
	std::vector<Node_gene*> outputGenes;
	std::vector<Node_gene*> hiddenGenes;
	int fitnessScore;

	//there are used in mutation
	void addHiddenGene();
	void addConnection();
	void changeWeightsRandomly(int chance);
	void disableGenesRandomly();

public:
	NEAT_layer(
		std::vector<Node_gene*> inputGenes, 
		std::vector<Node_gene*> outputGenes, 
		std::vector<Node_gene*> hiddenGenes
	);
	NEAT_layer();
	~NEAT_layer();

	//changeWeight limit is not used currently, fix
	void mutate(int addConnectionChance, int addHiddenGeneChance, int changeWeightChance, int changeWeightLimit);
	void setFitnessScore();

	int getFitnessScore();
	int getNormalisedFitnessScore();


	//create a one layered perceptron
	void createDefault(int inputSize, int hiddenGenesAmount, int outputSize);

	//calculating the result, should be private, but i'll keep it for the first test
	std::vector<double> getOutput();

	//getting input and calculating the result
	std::vector<double> propogate(std::vector<double>& input);


	NEAT_layer* clone();


	//debug functions
	void setInput(std::vector<Node_gene*> input);
	void setOutput(std::vector<Node_gene*> output);

	
	void ConnectionPrint();
};
