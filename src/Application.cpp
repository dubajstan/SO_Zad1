#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>

#include "ProcesGenerator.h"


int main() {
	ProcesGenerator rng;
	std::ofstream file("data.txt");

	size_t sampleSize = 1000;
	for (size_t i = 0; i < sampleSize; i++) {
		file << rng.gaussian(50, 15) << " " << rng.linear(0, 100) << " " << rng.customDistribution(0, 10) << "\n";
	}
	file.close();

	return 0;

}