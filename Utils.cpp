#include "Utils.h"
#include <random>

namespace Utils {
	float calcYPos(int i, float basePos) {
		if (i % 2) return -1 * basePos;
		else return basePos;
	}

	float sigmoid(float x)
	{
		return 1 / (abs(x) + 1);
	}

	vector<float>& setSigmoid(vector<float>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			v[i] = sigmoid(v[i]);
		}
		return v;
	}

	vector<float>& normalize(vector<float>& v)
	{
		float norm = 0;
		float sq_sum = 0;
		for (int i = 0; i < v.size(); ++i)
		{
			sq_sum += v[i] * v[i];;
		}
		norm = sqrt(sq_sum);
		for (int i = 0; i < v.size(); i++)
		{
			v[i] /= norm;
		}
		return v;
	}

	template <typename T>
	size_t getMaxVectorIndex(vector<T> v, size_t from, size_t to)
	{
		size_t maxIndex = 0;
		T maxElem = v[from];
		for (size_t i = from; i < to; i++) {
			if (maxElem < v[i]) {
				maxElem = v[i];
				maxIndex = i;
			}
		}
		return maxIndex;
	}

	// Standart brain result conderter from 5-element float vector to 2-elements int vector.
	vector<int> convertBrainResult(vector<double>& brainResult) {
		vector<int> res(2);
		if (brainResult[0] > brainResult[1])
			res[0] = 0;
		else
			res[0] = 1;

		if (brainResult[2] > brainResult[3])
			if (brainResult[2] > brainResult[4])
				res[1] = 1;
			else
				res[1] = 0;
		else
			if (brainResult[3] > brainResult[4])
				res[1] = -1;
			else
				res[1] = 0;

		return res;

	}

	double getRandomNumber(double begin, double end) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(begin, end);

		return dis(gen);
	}
}