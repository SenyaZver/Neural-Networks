#pragma once
#include "../ConvolutionalNEAT_Brain/NewNeatLayer/NEAT.h"
#include <iostream>

void newNeatTest() {

	NEAT test;
	test.createDefault(2, 2, 1);

	
	test.print();




}