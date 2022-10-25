#pragma once
#include "../Common.h"


struct LoadingConvData {
	size_t convInputSize; 
	size_t filterSize; 
	matrix filter1; 
	matrix filter2; 
	matrix filter3; 
	size_t convBiasSize;
	matrix convBias;


	size_t denseInputSize;
	size_t hiddenLayerSize; 
	matrix hiddenLayer; 
	size_t denseBiasSize;
	std::vector<double> denseBias;
	size_t outputSize;
};