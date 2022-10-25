#pragma once
#include <vector>

using std::vector;
namespace Utils {
	float calcYPos(int i, float basePos);
	float sigmoid(float x);
	vector<float>& setSigmoid(vector<float>& v);
	vector<float>& normalize(vector<float>& v);

	template <typename T>
	size_t getMaxVectorIndex(vector<T> v, size_t from, size_t to);

	vector<int> convertBrainResult(vector<double>& brainResult);
}