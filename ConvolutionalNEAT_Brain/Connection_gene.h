#pragma once
#include "Node_gene.h"

class Node_gene;

class Connection_gene
{
private:
	Node_gene* in;
	Node_gene* out;
	double weight;
	bool Enabled;
	int innovationNumber;

public:
	Connection_gene(Node_gene* in, Node_gene* out, double weight, int innovationNumber);
	~Connection_gene();
	Connection_gene(const Connection_gene& obj);

	void setWeight(double weight);
	void enable();
	void disable();
	double getInputValue() const;


	Node_gene* getOutGene() const;
	Node_gene* getInGene() const;
	double getWeight() const;
	bool isEnabled() const;

};