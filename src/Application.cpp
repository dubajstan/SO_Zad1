#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>

#define uint unsigned int

using namespace std;


class ProcessGenerator {
private:
	random_device rd;
	mt19937 gen;

public:
	ProcessGenerator()
		: gen(rd())
	{}
	~ProcessGenerator() {}

	double gaussian(double mean, double stddev) {
		normal_distribution<double> dist(mean, stddev);
		return dist(gen);
	}

	double linear(double min, double max) {
		uniform_real_distribution<double> dist(0.0, 1.0);
		double r = dist(gen);
		return min + (max - min) * r * r;
	}

	double inverseLinear(double min, double max) {
		uniform_real_distribution<double> dist(0.0, 1.0);
		double r = dist(gen);
		return min + (max - min) * sqrt(r);
	}

	double customDistribution(int min, int max) {
		vector<int> numbers;
		for (int i = min; i <= max; i++) {
			numbers.push_back(i);
			if (i % 2 == 0)numbers.push_back(i);
		}
		uniform_int_distribution<int> dist(0, numbers.size() - 1);
		return numbers[dist(gen)];
	}
};


int main() {
	ProcessGenerator rng;

	vector<double> gaussData, linearData, inverseData, customData;
	
	size_t sampleSize = 1000;
	for (size_t i = 0; i < sampleSize; i++)
	{
		gaussData.push_back(rng.gaussian(50, 15));
		linearData.push_back(rng.linear(0, 100));
		inverseData.push_back(rng.inverseLinear(0, 100));
		customData.push_back(rng.customDistribution(0, 10));
	}



	return 0;
}