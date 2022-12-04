#pragma once
#include "../../Layers/NEAT_Layer/NEAT.h"


class NewNEAT_Tester {

public:

	void test1() {
		NEAT test;

		test.inputIndexes.push_back(0);
		test.inputIndexes.push_back(1);
		test.genes.push_back(Node(0));
		test.genes.push_back(Node(1));

		test.hiddenIndexes.push_back(2);
		test.genes.push_back(Node(2));

		Node::connect(test.genes[1], test.genes[2], 0.3);
		Node::connect(test.genes[0], test.genes[2], 0.2);

		test.hiddenIndexes.push_back(3);
		test.genes.push_back(Node(3));

		Node::connect(test.genes[0], test.genes[3], 0.5);
		Node::connect(test.genes[2], test.genes[3], 0.5);

		test.outputIndexes.push_back(4);
		test.genes.push_back(Node(4));

		Node::connect(test.genes[3], test.genes[4], 0.8);

		//	test.print();


		std::vector<double> input = std::vector<double>{ 0.8, 0.8 };

		auto result = test.propogate(input);


		std::cout << result[0] << std::endl;
	}


	void test2() {
		NEAT test;


		test.inputIndexes.push_back(0);

		test.hiddenIndexes.push_back(1);
		test.hiddenIndexes.push_back(2);
		test.hiddenIndexes.push_back(3);
		test.hiddenIndexes.push_back(4);

		test.outputIndexes.push_back(5);


		test.genes.push_back(Node(0));
		test.genes.push_back(Node(1));
		test.genes.push_back(Node(2));
		test.genes.push_back(Node(3));
		test.genes.push_back(Node(4));
		test.genes.push_back(Node(5));


		Node::connect(test.genes[0], test.genes[1], 0.1);
		Node::connect(test.genes[0], test.genes[2], 0.1);

		Node::connect(test.genes[2], test.genes[3], 0.1);
		Node::connect(test.genes[3], test.genes[4], 0.1);

		Node::connect(test.genes[4], test.genes[5], 0.1);
		Node::connect(test.genes[1], test.genes[5], 0.1);

		//	Node::connect(test.genes[4], test.genes[2], 0.1);

		std::vector<double> input = std::vector<double>{ 0.1 };

		auto result = test.propogate(input);

		std::cout << result[0] << std::endl;
	}


};