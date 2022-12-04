#pragma once
class Connection
{
public:
	size_t input;
	size_t output;
	double weight;


	Connection(
		size_t inputGeneIndex,
		size_t outputGeneIndex,
		double weight
	) : input(inputGeneIndex), output(outputGeneIndex), weight(weight) {}


};