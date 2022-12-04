#pragma once

#include <iostream>
#include "../../Layers/Old_NEAT_Layer/NEAT_layer.h"




void NEAT_layer_Test() {
	NEAT_layer* example = new NEAT_layer();
	example->createDefault(30, 10, 2);


	//input example
	std::vector<double> input{ 55, 55, 57, 59, 61, 63, 66, 69, 72, 76, 80, 84, 88, 88, 56, 30, 35, 40, 48, 57, 61, 61, 59, 59, 57, 57, 56, 56, 56, 55 };


	std::vector<double> result = example->propogate(input);


	std::cout << "result is ";
	for (auto it : result) {
		std::cout << it << " ";
	}

//	example->ConnectionPrint();
	std::cout << std::endl;


	NEAT_layer* copy = new NEAT_layer();
	copy = example->clone();

	result = copy->propogate(input);

	std::cout << "result is ";
	for (auto it : result) {
		std::cout << it << " ";
	}

//	copy->ConnectionPrint();
}