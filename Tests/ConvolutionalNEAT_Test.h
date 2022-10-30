#pragma once
#include <vector>
#include "../ConvolutionalNEAT_Brain/NEAT_layer.h"
#include <iostream>



void convNEAT_test() {

	NEAT_layer* example = new NEAT_layer();
	example->createDefault(30, 10, 2);


	//input example
	std::vector<double> input{ 55, 55, 57, 59, 61, 63, 66, 69, 72, 76, 80, 84, 88, 88, 56, 30, 35, 40, 48, 57, 61, 61, 59, 59, 57, 57, 56, 56, 56, 55 };
	//for (int i = 0; i < 30; i++) {
	//	(*input)[i] = i;
	//}

	std::vector<double> result = example->feedForward(&input);


	std::cout << "result is ";
	for (auto it : result) {
		std::cout << it << " ";
	}

	//example->ConnectionPrint();
	std::cout << std::endl;
}