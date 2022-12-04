#include "Connection_gene.h"

#include "Connection_gene.h"

Connection_gene::Connection_gene(Node_gene* in, Node_gene* out, double weight, int innovationNumber)
{
	this->in = in;
	this->out = out;
	this->weight = weight;
	this->innovationNumber = innovationNumber;
	this->Enabled = true;
}

Connection_gene::Connection_gene(const Connection_gene& obj) {
	this->weight = obj.weight;
	this->innovationNumber = obj.innovationNumber;
	this->Enabled = obj.Enabled;
	this->in = in;
	this->out = out;

}

Connection_gene::~Connection_gene()
{
	//delete this->in;
	//delete this->out;
}

void Connection_gene::setWeight(double weight)
{
	this->weight = weight;
}

void Connection_gene::enable()
{
	this->Enabled = true;
}

void Connection_gene::disable()
{
	this->Enabled = false;
}

double Connection_gene::getInputValue() const
{
	return this->in->getValue();
}

double Connection_gene::getWeight() const
{
	return this->weight;
}

bool Connection_gene::isEnabled() const
{
	return this->Enabled;
}

Node_gene* Connection_gene::getOutGene() const {
	return this->out;
}

Node_gene* Connection_gene::getInGene() const
{
	return this->in;
}