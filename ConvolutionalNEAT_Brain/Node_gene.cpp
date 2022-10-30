#include "Node_gene.h"
#include <iostream>


Node_gene::Node_gene(double value) {
	this->value = value;
	this->inputs;
	this->outputs;
}

Node_gene::Node_gene(double value, std::set<Connection_gene*>& inputs, std::set<Connection_gene*>& outputs) {
	this->value = value;
	this->inputs = inputs;
	this->outputs = outputs;
}

std::set<Connection_gene*> Node_gene::getOutConnections() const {
	return this->outputs;
}

std::set<Connection_gene*> Node_gene::getInConnections() const {
	return this->inputs;
}

std::set<Node_gene*> Node_gene::getInputGenes() const
{
	std::set<Node_gene*>* inputGenes = new std::set<Node_gene*>();
	for (auto connection : inputs) {
		inputGenes->insert(connection->getInGene());
	}

	return *inputGenes;
}

std::set<Node_gene*> Node_gene::getOutputGenes() const
{
	std::set<Node_gene*>* outputGenes = new std::set<Node_gene*>();
	for (auto connection : outputs) {
		outputGenes->insert(connection->getOutGene());
	}

	return *outputGenes;
}

void Node_gene::setInputs(std::set<Connection_gene*>& inputs) {
	this->inputs = inputs;
}

void Node_gene::setInput(Node_gene* newInput, double connectionValue, int innovationNumber) {
	Connection_gene* newConnection = new Connection_gene(newInput, this, connectionValue, innovationNumber);
	newInput->outputs.insert(newConnection);
	this->inputs.insert(newConnection);
}

void Node_gene::setOutput(Node_gene* newOutput, double connectionValue, int innovationNumber) {
	Connection_gene* newConnection = new Connection_gene(this, newOutput, connectionValue, innovationNumber);
	newOutput->inputs.insert(newConnection);
	this->outputs.insert(newConnection);
}



void Node_gene::setValue(double value) {
	this->value = value;
}

double Node_gene::fastSigmoid(double value) {
	return value / (1 + abs(value));
}

double Node_gene::getValue() const {
	return this->value;
}

void Node_gene::print() {
	std::cout << "Node " << this->value;
}

void Node_gene::printOutputs() {

	std::cout << "Node " << this->value << " .Outputs are: ";

	for (Connection_gene* connection : outputs) {
		connection->getOutGene()->print();
	}

}

void Node_gene::printInputs()
{
	std::cout << "Node " << this->value << " .inputs are: ";

	for (Connection_gene* connection : inputs) {
		connection->getInGene()->print();
	}
}

void Node_gene::calculate() {
	double sum = 0;
	for (Connection_gene* connection : inputs) {
		sum += connection->getWeight() * connection->getInputValue();
	}
	sum = sum / (1 + abs(sum));	//fastSigmoid
	this->value = sum;
	//	std::cout << "calculated gene " << this->name << " value is " << this->value << std::endl;
}
