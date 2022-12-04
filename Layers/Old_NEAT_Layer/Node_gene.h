#pragma once
#include <set>
#include "Connection_gene.h"


class Connection_gene;

class Node_gene {
private:
	double value;
	std::set<Connection_gene*> inputs;
	std::set<Connection_gene*> outputs;


public:
	Node_gene(double value);
	Node_gene(double value, std::set<Connection_gene*>& inputs, std::set<Connection_gene*>& outputs);

	Node_gene(const Node_gene& obj) {	//TODO get this into cpp
		this->value = obj.value;
		for (auto it : obj.inputs) {
			this->inputs.insert(it);
		}
		for (auto it : obj.outputs) {
			this->outputs.insert(it);
		}
	}


	void setValue(double value);
	double getValue() const;


	std::set<Connection_gene*> getOutConnections() const;
	std::set<Connection_gene*> getInConnections() const;

	std::set<Node_gene*> getInputGenes() const;
	std::set<Node_gene*> getOutputGenes() const;

	bool isConnected(Node_gene* gene);

	double fastSigmoid(double value);


	void setOutput(Node_gene* newOutput, double connectionValue, int innovationNumber);
	void setInput(Node_gene* newInput, double connectionValue, int innovationNumber);

	void setInputs(std::set<Connection_gene*>& inputs);

	void calculate();


	//debug functions
	void printOutputs();
	void printInputs();
	void print();
};

