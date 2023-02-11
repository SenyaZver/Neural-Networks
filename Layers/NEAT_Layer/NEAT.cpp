#include "NEAT.h"
#include <set>
#include <algorithm>
#include "../../Utils.h"
#include <sstream>




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
			genes[geneToCalculateIndex].fastSigmoid();
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





void NEAT::createSingleLayerPerceptron(size_t inputSize, size_t hiddenSize, size_t outputSize)
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
			double weight = Utils::getRandomNumber(-1, 1);
			Node::connect(genes[i], genes[j], weight);

			
		}
		
	}

	for (auto i : hiddenIndexes) {
		for (auto j : outputIndexes) {
			double weight = Utils::getRandomNumber(-1, 1);
			Node::connect(genes[i], genes[j], weight);
		}
	}
	
	this->size = inputSize + hiddenSize + outputSize;

}

void NEAT::mutate(size_t addHiddenGeneChance, size_t addConnectionChance, size_t weightChangeChance, size_t weightChangeLimit)
{

	this->changeWeightsRandomly(weightChangeChance, weightChangeLimit);

	size_t chance = Utils::getRandomNumber(0, 100);
	if (chance < addHiddenGeneChance) {
		this->addHiddenGene();
	}
	chance = Utils::getRandomNumber(0, 100);
	if (chance < addConnectionChance) {
		this->addConnection();
	}

}

void NEAT::save(std::ofstream& file)
{
	file << "genesAmount" << std::endl;
	file << this->size << std::endl;

	file << "inputSize" << std::endl;
	file << this->inputIndexes.size() << std::endl;
	for (size_t i = 0; i < this->inputIndexes.size(); i++) {
		file << this->inputIndexes[i] << std::endl;
	}

	file << "hiddenSize" << std::endl;
	file << this->hiddenIndexes.size() << std::endl;
	for (size_t i = 0; i < this->hiddenIndexes.size(); i++) {
		file << this->hiddenIndexes[i] << std::endl;
	}


	file << "outputSize" << std::endl;
	file << this->outputIndexes.size() << std::endl;
	for (size_t i = 0; i < this->outputIndexes.size() ; i++) {
		file << this->outputIndexes[i] << std::endl;
	}

	for (auto gene : this->genes) {

		for (auto& connection : gene.outputs) {
			file << gene.number << " " << connection.output << " " << connection.weight << std::endl;
		}
	}

}

NEAT NEAT::load(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (!file.good()) {
		throw "File " + filename + " couldn't open";
	}


	std::string currentLine;
	size_t genesAmount;

	NEAT loadedBrain;


	genesAmount = Utils::readNumber(file);

	std::cout << genesAmount << std::endl;

	for (size_t i = 0; i < genesAmount; i++) {
		loadedBrain.genes.push_back(Node(i));
	}

	getline(file, currentLine);
	std::istringstream iss(currentLine);

	std::string temp;
	iss >> temp;


	if (temp == "inputSize") {
		size_t inputSize = Utils::readNumber(file);

		std::cout << inputSize << std::endl;



		for (size_t i = 0; i < inputSize; i++) {
			size_t index = Utils::readNumber(file);
			loadedBrain.inputIndexes.push_back(index);
		}
		
	}
	getline(file, currentLine);
	iss = std::istringstream(currentLine);
	iss >> temp;



	if (temp == "hiddenSize") {

		size_t hiddenSize = Utils::readNumber(file);
		
		for (size_t i = 0; i < hiddenSize; i++) {
			size_t index = Utils::readNumber(file);
			loadedBrain.hiddenIndexes.push_back(index);
		}
	}

	getline(file, currentLine);
	iss = std::istringstream(currentLine);
	iss >> temp;

	if (temp == "outputSize") {
		size_t outputSize = Utils::readNumber(file);
		
		for (size_t i = 0; i < outputSize; i++) {
			size_t index = Utils::readNumber(file);
			loadedBrain.outputIndexes.push_back(index);
		}
	}


	for (size_t i = 0; i < genesAmount; i++) {
		getline(file, currentLine);
		std::istringstream lineStream(currentLine);

		size_t inputIndex;
		size_t outputIndex;

		double weight;

		lineStream >> inputIndex;
		lineStream >> outputIndex;
		lineStream >> weight;

		Node::connect(loadedBrain.genes[inputIndex], loadedBrain.genes[outputIndex], weight);
	}

	file.close();

	loadedBrain.size = loadedBrain.genes.size();


	return loadedBrain;
}

bool NEAT::isCyclic()
{
	std::vector<size_t> vis = std::vector<size_t>(this->size);
	std::vector<size_t> dfsVis = std::vector<size_t>(this->size);
	
	for (int i = 0; i < this->size; i++) {
		vis[i] = 0;
		dfsVis[i] = 0;
	}

	for (int i = 0; i < this->size; i++) {
		if (!vis[i]) {
			if (checkCycle(i, vis, dfsVis)) {
				return true;
			}
		}
	}
	return false;
}

bool NEAT::checkCycle(int index, std::vector<size_t> vis, std::vector<size_t> dfsVis)
{
	vis[index] = 1;
	dfsVis[index] = 1;
	for (auto it : genes[index].getOutputGenesIndexes()) {
		if (!vis[it]) {
			if (checkCycle(it, vis, dfsVis)) return true;
		}
		else if (dfsVis[it]) {
			return true;
		}
	}
	dfsVis[index] = 0;
	return false;
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
		size_t InputGene = Utils::getRandomNumber(0, eligebleInputs.size() - 1);

		Node* inputGene = &genes[eligebleInputs[InputGene]];
		

		//actual indexes
		auto outputsForChosenGene = inputGene->getOutputGenesIndexes();


		if (outputsForChosenGene.size() == 0) {
			continue;
		}
		
		else {
			//local index
			size_t temp = Utils::getRandomNumber(0, outputsForChosenGene.size() - 1);
			
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
	auto eligebleInputs = std::vector<size_t>();
	eligebleInputs.insert(eligebleInputs.end(), this->inputIndexes.begin(), this->inputIndexes.end());
	eligebleInputs.insert(eligebleInputs.end(), this->hiddenIndexes.begin(), this->hiddenIndexes.end());

	auto eligebleOutputs = std::vector<size_t>();
	eligebleOutputs.insert(eligebleOutputs.end(), this->outputIndexes.begin(), this->outputIndexes.end());
	eligebleOutputs.insert(eligebleOutputs.end(), this->hiddenIndexes.begin(), this->hiddenIndexes.end());


	size_t randomInputIndex = Utils::getRandomNumber(0, eligebleInputs.size() - 1);
	size_t randomOutputIndex = Utils::getRandomNumber(0, eligebleInputs.size() - 1);

	std::cout << randomInputIndex << " - " << randomOutputIndex << std::endl;

	if (genes[randomInputIndex].isConnectedTo(randomOutputIndex)) {
		return;
	}

	Node::connect(genes[randomInputIndex], genes[randomOutputIndex], 0);

	if (this->isCyclic()) {
		Node::disconnect(genes[randomInputIndex], genes[randomOutputIndex]);
	}

}

void NEAT::changeWeightsRandomly(size_t changeChance, double changeLimit)
{
	for (auto gene1 : genes) {
		for (auto gene2 : genes) {
			if (gene1.isConnectedTo( gene2.getNumber() )) {
				size_t chance = Utils::getRandomNumber(0, 100);

				if (chance < changeChance) {
					double weightChange = Utils::getRandomNumber(-changeLimit, changeLimit);
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
