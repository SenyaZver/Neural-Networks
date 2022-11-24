#include "NEAT.h"
#include "../../Common.h"

std::vector<double> NEAT::propogate(std::vector<double>& input)
{
	return std::vector<double>();
}

void NEAT::createDefault(size_t inputSize, size_t hiddenSize, size_t outputSize)
{
	for (int i = 0; i < inputSize; i++) {
		auto inputGene = new Node(i);
		this->genes.push_back(*inputGene);
		this->inputIndexes.push_back(i);
	}

	for (int i = inputSize; i < inputSize + hiddenSize; i++) {
		auto hiddenGene = new Node(i);
		this->genes.push_back(*hiddenGene);
		this->hiddenIndexes.push_back(i);
	}

	for (int i = inputSize + hiddenSize; i < inputSize + hiddenSize + outputSize; i++) {
		auto outputGene = new Node(i);
		this->genes.push_back(*outputGene);
		this->outputIndexes.push_back(i);
	}

	for (auto i: inputIndexes) {
		for (auto j: hiddenIndexes) {
			double weight = getRandomNumber(1, 1);
			Node::connect(genes[i], genes[j], weight);

			
		}
		
	}

	for (auto i : hiddenIndexes) {
		for (auto j : outputIndexes) {
			double weight = getRandomNumber(1, 1);
			Node::connect(genes[i], genes[j], weight);
		}
	}
	
	this->size = inputSize + hiddenSize + outputSize;

}

void NEAT::mutate(size_t addHiddenGeneChance, size_t addConnection, size_t weightChance, size_t weightChangeLimit)
{
	
}

void NEAT::addHiddenGene()
{

	//actual numbers
	auto eligebleInputs = std::vector<size_t>();
	eligebleInputs.insert(eligebleInputs.end(), this->inputIndexes.begin(), this->inputIndexes.end());
	eligebleInputs.insert(eligebleInputs.end(), this->hiddenIndexes.begin(), this->hiddenIndexes.end());


	
	bool isFound = false;

	while (!isFound) {
		//local index
		size_t InputGene = getRandomNumber(0, eligebleInputs.size() - 1);

		Node* inputGene = &genes[eligebleInputs[InputGene]];
		

		//actual indexes
		auto outputsForChosenGene = inputGene->getOutputGenesIndexes();


		if (outputsForChosenGene.size() == 0) {
			continue;
		}
		
		else {
			//local index
			size_t temp = getRandomNumber(0, outputsForChosenGene.size() - 1);
			
			size_t outputGeneNumber = outputsForChosenGene[temp];

			double oldWeight = Node::disconnect(*inputGene, this->genes[outputGeneNumber]);
			


			Node* newGene = new Node(this->size);
			this->size++;

			Node::connect(*inputGene, *newGene, oldWeight);
			Node::connect(*newGene, genes[outputGeneNumber], 1);

			genes.push_back(*newGene);

			break;

		}

	}
}

void NEAT::addConnection()
{
}

void NEAT::changeWeightsRandomly(size_t chance)
{
}

void NEAT::print()
{
	for (auto& gene : genes) {
		gene.print();
	}

}
