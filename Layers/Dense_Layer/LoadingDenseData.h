#pragma once
#include <vector>
#include "../../Utils.h"


struct LoadingDenseData {
	size_t denseInputSize;
	size_t hiddenLayerSize;
	Utils::matrix hiddenLayer;
	size_t denseBiasSize;
	std::vector<double> denseBias;
	size_t outputSize;
};