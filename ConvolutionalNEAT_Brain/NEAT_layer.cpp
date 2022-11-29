#include "NEAT_layer.h"
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include "../Common.h"


void NEAT_layer::addHiddenGene() {
	std::vector<Node_gene*> allGenes;


	allGenes.insert(allGenes.end(), inputGenes.begin(), inputGenes.end());
	allGenes.insert(allGenes.end(), hiddenGenes.begin(), hiddenGenes.end());

	int chosenGeneNumber = getRandomNumber(0, allGenes.size() - 1);//choose random gene	
	Node_gene* inGene = allGenes[chosenGeneNumber];


	std::set<Connection_gene*> set = inGene->getOutConnections();
	std::vector<Connection_gene*> connections(set.size());
	std::copy(set.begin(), set.end(), connections.begin());		//creating a vector of gene's connections

		
	int choosenConnectionNumber = getRandomNumber(0, connections.size() - 1);  //choose random outConnection of chosen gene	

	Connection_gene* connection = connections[choosenConnectionNumber];
	Node_gene* outGene = connection->getOutGene();
	double weight = connection->getWeight();


	inGene->getOutConnections().erase(connection);	//delete previous connection
	outGene->getInConnections().erase(connection);

	Node_gene* newGene = new Node_gene(0);
	newGene->setOutput(outGene, weight, 20);
	newGene->setInput(inGene, 1, 20);
	hiddenGenes.push_back(newGene);
}
void NEAT_layer::addConnection() {
	std::vector<Node_gene*> allGenes;


	allGenes.insert(allGenes.end(), inputGenes.begin(), inputGenes.end());
	allGenes.insert(allGenes.end(), hiddenGenes.begin(), hiddenGenes.end());


	int firstChosenNumber = getRandomNumber(0, allGenes.size() - 1);	//choose first random gene
	Node_gene* firstGene = allGenes[firstChosenNumber];

	int secondChosenNumber = getRandomNumber(0, allGenes.size() - 1);	//choose second random gene
	Node_gene* secondGene = allGenes[secondChosenNumber];

	std::set<Node_gene*> outputs = firstGene->getOutputGenes();


	if (outputs.find(secondGene) != outputs.end()) {
		double weight = getRandomNumber(-1, 1);//choose random number close to 1(actually it would be better to be close to 0
		firstGene->setOutput(secondGene, weight, 50);
	}

}
void NEAT_layer::changeWeightsRandomly(int chance) {
	for (auto input : inputGenes) {
		for (auto connection : input->getOutConnections()) {

			if (getRandomNumber(0, 100) < chance) {
				double value = connection->getWeight();
				value = value + getRandomNumber(-1, 1);		//choose random number close to 1
				connection->setWeight(value);
			}

		}
	}
	for (auto gene : hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {

			if (getRandomNumber(0, 100) < chance) {
				double value = connection->getWeight();
				value = value + getRandomNumber(-1, 1);		//choose random number close to 1
				connection->setWeight(value);
			}

		}
	}
}
void NEAT_layer::disableGenesRandomly() {
	//TODO
}


NEAT_layer::NEAT_layer(std::vector<Node_gene*> inputGenes, std::vector<Node_gene*> outputGenes, std::vector<Node_gene*> hiddenGenes) {
	this->inputGenes = inputGenes;
	this->outputGenes = outputGenes;
	this->hiddenGenes = hiddenGenes;
	fitnessScore = 0;
}

NEAT_layer::NEAT_layer()
{

	this->inputGenes = std::vector<Node_gene*>();
	this->outputGenes = std::vector<Node_gene*>();
	this->hiddenGenes = std::vector<Node_gene*>();
	fitnessScore = 0;
}

NEAT_layer::~NEAT_layer()
{
	for (auto gene : inputGenes) {
		for (auto connection : gene->getOutConnections()) {
			delete connection;
		}
	}
	for (auto gene : hiddenGenes) {
		for (auto connection : gene->getOutConnections()) {
			delete connection;
		}
	}

	for (auto gene : inputGenes) {
		delete gene;
	}
	for (auto gene : hiddenGenes) {
		delete gene;
	}
	for (auto gene : outputGenes) {
		delete gene;
	}


}

void NEAT_layer::mutate(int addConnectionChance, int addHiddenGeneChance, int changeWeightChance, int changeWeightLimit) {

	if (getRandomNumber(0, 100) < addConnectionChance) { //preferably 3
		this->addConnection();
	}
	if (getRandomNumber(0, 100) < addHiddenGeneChance) { //preferably 5
		this->addHiddenGene();
	}

	this->changeWeightsRandomly(changeWeightChance);
}
void NEAT_layer::setFitnessScore() {
	//TODO
}

int NEAT_layer::getFitnessScore() {
	return this->fitnessScore;
}
int NEAT_layer::getNormalisedFitnessScore() {
	//TODO
	return this->fitnessScore;
}

//calculating the result
std::vector<double> NEAT_layer::getOutput() {
	std::vector<double> output;

	std::set<Node_gene*> calculatedSet(this->inputGenes.begin(), this->inputGenes.end()); //vector->set;
	std::set<Node_gene*> availableSet;

	while (true) {
		
		for (Node_gene* calculatedNode : calculatedSet) {
			for (Connection_gene* connection : calculatedNode->getOutConnections()) {
				Node_gene* geneToAdd = connection->getOutGene();


				if (calculatedSet.find(geneToAdd) == calculatedSet.end()) {

					availableSet.insert(geneToAdd);
				}

			}
		}
		//step two finished

		if (availableSet.empty()) { //stop condition
			break;
		}

		std::set<Node_gene*> setToCalculate;
		for (Node_gene* availableNode : availableSet) {
			std::set<Node_gene*> inputs = availableNode->getInputGenes();

			if (std::includes(calculatedSet.begin(), calculatedSet.end(), inputs.begin(), inputs.end()))
			{
				setToCalculate.insert(availableNode);
			}
		}
		//step three finished

		for (Node_gene* gene : setToCalculate) {
			gene->calculate();
			availableSet.erase(gene);
			calculatedSet.insert(gene);
		}
		//steps four, five and six finished

	}

	for (auto result : outputGenes) {
		output.push_back(result->getValue());
	}



	return output;
}

void NEAT_layer::createDefault(int inputSize, int hiddenGenesAmount, int outputSize)
{

	for (int i = 0; i < inputSize; i++) {
		inputGenes.push_back(new Node_gene(0));
	}

	for (int i = 0; i < outputSize; i++) {
		outputGenes.push_back(new Node_gene(0));
	}


	for (int i = 0; i < hiddenGenesAmount; i++) {
		Node_gene* hiddenNode = new Node_gene(0);

		double weight = getRandomNumber(-1, 1);

		int innovationNumber = 0;
		for (auto input : inputGenes) {
			weight = getRandomNumber(-1, 1);
			hiddenNode->setInput(input, weight, innovationNumber);
		}

		weight = getRandomNumber(-1, 1);

		for (auto output : outputGenes) {
			weight = getRandomNumber(-1, 1);
			output->setInput(hiddenNode, weight, innovationNumber);
		}
		hiddenGenes.push_back(hiddenNode);
	}

}



void NEAT_layer::setInput(std::vector<Node_gene*> input) {
	this->inputGenes = input;
}



std::vector<double> NEAT_layer::propogate(std::vector<double>& input)
{
	if (input.size() != this->inputGenes.size()) {
		return std::vector<double>(outputGenes.size());
	}

	for (int i = 0; i < input.size(); i++) {
		inputGenes[i]->setValue(input[i]);
	}

	return this->getOutput();
}



void NEAT_layer::setOutput(std::vector<Node_gene*> output) {
	this->outputGenes = output;
}

void NEAT_layer::ConnectionPrint() {
	int i = 0;
	for (auto gene : hiddenGenes) {
		i++;
	}
	std::cout << i << std::endl;
	i = 0;
	for (auto gene : inputGenes) {
		i++;
	}
	std::cout << i << std::endl;
	//for (auto gene : outputGenes) {
	//	std::cout << gene->getOutConnections().size() << std::endl;
	//}
}


NEAT_layer* NEAT_layer::clone() {
	std::vector<Node_gene*> newInputGenes = std::vector<Node_gene*>();
	std::vector<Node_gene*> newOutputGenes = std::vector<Node_gene*>();
	std::vector<Node_gene*> newHiddenGenes = std::vector<Node_gene*>();
	NEAT_layer* copy = new NEAT_layer();



	for (int i = 0; i < (this->inputGenes.size()); i++) {
		Node_gene* inputNode = new Node_gene(0);
		newInputGenes.push_back(inputNode);
	}
	for (int i = 0; i < (this->hiddenGenes.size()); i++) {
		Node_gene* hiddenNode = new Node_gene(0);
		newHiddenGenes.push_back(hiddenNode);
	}
	for (int i = 0; i < (this->outputGenes.size()); i++) {
		Node_gene* outputNode = new Node_gene(0);
		newOutputGenes.push_back(outputNode);
	}


	for (int i = 0; i < inputGenes.size(); i++) {
		for (int j = 0; j < hiddenGenes.size(); j++) {
			//chech if hiddenGene[j] is connected to inputgene[i]
			auto temp = inputGenes[i]->getOutputGenes();

			if (temp.find(hiddenGenes[j]) != temp.end()) {
				double weight = 0;
				for (auto connection : inputGenes[i]->getOutConnections()) {
					if (connection->getOutGene() == hiddenGenes[j]) {
						weight = connection->getWeight();
					}
				}
				newInputGenes[i]->setOutput(newHiddenGenes[j], weight, 1337);
			}
		}
	}

	for (int i = 0; i < hiddenGenes.size(); i++) {
		for (int j = 0; j < hiddenGenes.size(); j++) {

			auto temp = hiddenGenes[i]->getOutputGenes();

			//chech if hiddenGene[j] is connected to hiddengene[i]
			if (temp.find(hiddenGenes[j]) != temp.end()) {
				double weight = 0;
				for (auto connection : hiddenGenes[i]->getOutConnections()) {
					if (connection->getOutGene() == hiddenGenes[j]) {
						weight = connection->getWeight();
					}
				}
				newHiddenGenes[i]->setOutput(newHiddenGenes[j], weight, 1337);
			}
		}
	}

	for (int i = 0; i < hiddenGenes.size(); i++) {
		for (int j = 0; j < outputGenes.size(); j++) {
			auto temp = hiddenGenes[i]->getOutputGenes();
			//chech if hiddenGene[j] is connected to outputgene[i]
			if (temp.find(outputGenes[j]) != temp.end()) {
				double weight = 0;
				for (auto connection : hiddenGenes[i]->getOutConnections()) {
					if (connection->getOutGene() == outputGenes[j]) {
						weight = connection->getWeight();
					}
				}
				newHiddenGenes[i]->setOutput(newOutputGenes[j], weight, 1337);
			}
		}
	}

	copy->inputGenes = newInputGenes;
	copy->outputGenes = newOutputGenes;
	copy->hiddenGenes = newHiddenGenes;



	return copy;


}