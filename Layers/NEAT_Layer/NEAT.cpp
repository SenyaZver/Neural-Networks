#include "NEAT.h"
#include "../../Common.h"
#include <set>
#include <algorithm>




std::vector<double> NEAT::propogate(std::vector<double>& input)
{
	if (input.size() != this->inputIndexes.size()) {
		std::cout << "NEAT input size is wrong" << std::endl;
		return std::vector<double>();
	}

	for (size_t i = 0; i < input.size(); i++) {
		this->genes[i].setValue(input[i]);
	}

	std::set<size_t> calculatedSet = std::set<size_t>(this->inputIndexes.begin(), this->inputIndexes.end());
	std::set<size_t> availableSet;

	while (true) {
		for (auto calculatedGeneIndex : calculatedSet) {
			auto availableNodes = genes[calculatedGeneIndex].getOutputGenesIndexes();



			for (auto geneIndex : availableNodes) {

				if (calculatedSet.find(geneIndex) == calculatedSet.end()) {
					availableSet.insert(geneIndex);
				}
			}

			
		}

		if (availableSet.empty()) {
			break;
		}

		std::set<size_t> setToCalculate;
		


		for (size_t availableGeneIndex : availableSet) {
			auto inputGenes = genes[availableGeneIndex].getInputGenesIndexes();

			std::sort(inputGenes.begin(), inputGenes.end());

			if (std::includes(calculatedSet.begin(), calculatedSet.end(), inputGenes.begin(), inputGenes.end()) ) {
				setToCalculate.insert(availableGeneIndex);
			}

		}
		

		for (size_t geneToCalculateIndex : setToCalculate) {
			//calculate gene
			auto inputsIndexes = genes[geneToCalculateIndex].getInputGenesIndexes();
			
			double newValue = 0;
			for (size_t index : inputsIndexes) {
				double valueToAdd = genes[index].getValue();
				double weight = Node::getWeightBetween(genes[index], genes[geneToCalculateIndex]);

				newValue += valueToAdd * weight;
			}

			genes[geneToCalculateIndex].setValue(newValue);
			//

			availableSet.erase(geneToCalculateIndex);
			calculatedSet.insert(geneToCalculateIndex);
		}


	}

	std::vector<double> output;
	
	for (auto outputIndex : outputIndexes) {
		output.push_back(genes[outputIndex].getValue());
	}


	return output;
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

void NEAT::mutate(size_t addHiddenGeneChance, size_t addConnectionChance, size_t weightChangeChance, size_t weightChangeLimit)
{

	this->changeWeightsRandomly(weightChangeChance, weightChangeLimit);

	size_t chance = getRandomNumber(0, 100);
	if (chance < addHiddenGeneChance) {
		this->addHiddenGene();
	}
	chance = getRandomNumber(0, 100);
	if (chance < addConnectionChance) {
		this->addConnection();
	}

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
	//TODO
}

void NEAT::changeWeightsRandomly(size_t changeChance, double changeLimit)
{
	for (auto gene1 : genes) {
		for (auto gene2 : genes) {
			if (gene1.isConnectedTo( gene2.getNumber() )) {
				size_t chance = getRandomNumber(0, 100);

				if (chance < changeChance) {
					double weightChange = getRandomNumber(-changeLimit, changeLimit);
					Node::changeWeightBetween(gene1, gene2, weightChange);
				}

			}

		}
	}
}

void NEAT::print()
{
	for (auto& gene : genes) {
		gene.print();
	}

}
