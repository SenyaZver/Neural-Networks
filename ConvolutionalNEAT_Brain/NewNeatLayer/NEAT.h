#pragma once
#include <vector>
#include "Node.h"

class NEAT
{

	size_t size = 0;
	std::vector<size_t> inputIndexes = std::vector<size_t>();
	std::vector<size_t> hiddenIndexes = std::vector<size_t>();
	std::vector<size_t> outputIndexes = std::vector<size_t>();
	std::vector<Node> genes = std::vector<Node>();

	
public:
	std::vector<double> propogate(std::vector<double>& input);

	void createDefault(size_t inputSize, size_t hiddenSize, size_t outputSize);
	void mutate(size_t addHiddenGeneChance, size_t addConnectionChance, size_t weightChangeChance, size_t weightChangeLimit);

private:

	void addHiddenGene();
	void addConnection();
	void changeWeightsRandomly(size_t chance, double changeLimit);

public:

	void print();

};

