#pragma once



struct LoadingConvData {
	size_t convInputSize; 
	size_t filterSize; 
	Utils::matrix filter1; 
	Utils::matrix filter2;
	Utils::matrix filter3;
	size_t convBiasSize;
	Utils::matrix convBias;


};