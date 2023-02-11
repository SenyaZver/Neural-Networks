#pragma once
#include <vector>
#include "Node.h"
#include "../../Utils.h"

class NEAT
{
private:

	size_t size = 0;
	std::vector<size_t> inputIndexes = std::vector<size_t>();
	std::vector<size_t> hiddenIndexes = std::vector<size_t>();
	std::vector<size_t> outputIndexes = std::vector<size_t>();
	std::vector<Node> genes = std::vector<Node>();

	
public:
	std::vector<double> propogate(std::vector<double>& input);

	void createSingleLayerPerceptron(size_t inputSize, size_t hiddenSize, size_t outputSize);
	void mutate(size_t addHiddenGeneChance, size_t addConnectionChance, size_t weightChangeChance, size_t weightChangeLimit);

	void save(std::ofstream& file);
	static NEAT load(std::string filename);

private:
	bool isCyclic();
	bool checkCycle(int node, std::vector<size_t> vis, std::vector<size_t> dfsVis);

	void addHiddenGene();
	void addConnection();
	void changeWeightsRandomly(size_t chance, double changeLimit);


public:
	void print();
	friend class NewNEAT_Tester;
};