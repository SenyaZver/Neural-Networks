#pragma once
#include "../Common.h"


struct LoadingPerceptronData {
	size_t hiddenLayer1_horizontal;
	size_t hiddenLayer1_vertical;
	matrix hiddenLayer1;

	size_t bias1_size;
	std::vector<double> bias1;


	size_t hiddenLayer2_horizontal;
	size_t hiddenLayer2_vertical;
	matrix hiddenLayer2;

	size_t bias2_size;
	std::vector<double> bias2;

};