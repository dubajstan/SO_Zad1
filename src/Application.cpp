#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>

#include "CPU.h"

void print(const std::vector<std::unique_ptr<Proces>>& vec) {
	for (const auto& p : vec) {
		std::cout << p->toString();
	}
}

int main() {
	/*
	ProcesGenerator rng;
	std::ofstream file("data.txt");



	size_t sampleSize = 10000;
	for (size_t i = 0; i < sampleSize; i++) {
		file << rng.gaussian(50) << " " << rng.linear(50, 1) << " " << rng.inverseLinear(50) << "\n";
	}
	file.close();
	*/
	const uint ilosc = 1000;
	ProcesGenerator rng;
	// tutaj moge za pomoca funkcji w rng zmieniac strategie
	std::vector<Proces> vec = rng.generujProcesy({0.5, 0.3, 0.2}, ilosc);

	std::ofstream file("data.txt");
	for (auto obj : vec) {
		file << obj.getPriorytet() << " " << obj.getCzasTrwania() << " " << obj.getCzasDodania() << std::endl;
	}


	
	return 0;

}