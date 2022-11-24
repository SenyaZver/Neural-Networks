#pragma once
#include <vector>
#include "Connection.h"
#include <iostream>

class Node
{
	//TODO remove
public:
	//
	size_t number;
	double currentValue;
	
	std::vector<Connection> inputs = std::vector<Connection>();
	std::vector<Connection> outputs = std::vector<Connection>();
public:
	Node(size_t number) : number(number), currentValue(0) {}


	static void connect(Node& inputGene, Node& outputGene, double weight) {

		auto newConnection = new Connection(inputGene.number, outputGene.number, weight);
		inputGene.outputs.push_back(*newConnection);
		outputGene.inputs.push_back(*newConnection);

	}

	std::vector<size_t> getOutputGenesIndexes() {
		auto outputGenes = new std::vector<size_t>();
		for (auto& connection : outputs) {
			auto gene = connection.output;

			outputGenes->push_back(gene);
		}

		return *outputGenes;
	}

	std::vector<size_t> getInputGenesIndexes() {
		auto inputGenes = new std::vector<size_t>();
		for (auto& connection : inputs) {
			auto gene = connection.input;

			inputGenes->push_back(gene);
		}

		return *inputGenes;
	}

	size_t getNumber() {
		return number;
	}

	bool isConnectedTo(size_t otherGeneIndex) {
		for (auto& connection : outputs) {
			auto geneIndex = connection.output;

			if (geneIndex == otherGeneIndex) {
				return true;
			}
		}
		return false;
	}

	bool isConnectedFrom(size_t otherGeneIndex) {
		for (auto& connection : inputs) {
			auto geneIndex = connection.input;

			if (geneIndex == otherGeneIndex) {
				return true;
			}
		}
		return false;
	}

	void setValue(double value) {
		this->currentValue = value;
	}

	double getValue(double value) {
		return currentValue;
	}

	void fastSigmoid() {
		this->currentValue = currentValue / (1 + abs(currentValue));
	}

	double getWeight(Node& otherGene) {

	}

	static double disconnect(Node& input, Node& output) {
		size_t thisConnectionIndex = -1;
		size_t otherConnectionIndex = -1;

		//this gene is an input, other is an output
		for (size_t i = 0; i < output.inputs.size(); i++) {

			if (output.inputs[i].input == input.number) {
				otherConnectionIndex = i;
			}
		}

		for (size_t i = 0; i < input.outputs.size(); i++) {

			if (input.outputs[i].output == output.number) {
				thisConnectionIndex = i;
			}
		}



		if (thisConnectionIndex != -1 && otherConnectionIndex != -1) {
			double weight = input.outputs[thisConnectionIndex].weight;



			input.outputs.erase(input.outputs.begin() + thisConnectionIndex);

			output.inputs.erase(output.inputs.begin() + otherConnectionIndex);

			return weight;
		}
		return 0;
	}

	

	void print() {
		std::cout << "Gene " << this->getNumber() << std::endl;

		std::cout << "   Input Genes: " << std::endl;
		for (auto& input : this->getInputGenesIndexes()) {
			std::cout << "      " << input << std::endl;
		}

		std::cout << std::endl;

		std::cout << "   Output Genes: " << std::endl;
		for (auto& output : this->getOutputGenesIndexes()) {
			std::cout << "      " << output << std::endl;
		}

		std::cout << std::endl;
	}

};

