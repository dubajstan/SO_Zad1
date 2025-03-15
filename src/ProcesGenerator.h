#pragma once

#include <random>
#include <fstream>
#include <vector>
#include <cmath>  // Do std::floor()

#define uint unsigned int

class ProcesGenerator {
private:
    std::mt19937 engine;

public:
    // Konstruktor z seedem
    explicit ProcesGenerator(unsigned int seed)
        : engine(seed)
    {
    }

    // Konstruktor bez seed
    ProcesGenerator() {
        std::random_device rd;
        engine.seed(rd());
    }

    ~ProcesGenerator() {}

    uint gaussian(uint mean, uint stddev) {
        std::normal_distribution<double> dist(mean, stddev);
        return static_cast<uint>(dist(engine)); // Przekazywanie generatora przez referencjê
    }

    uint linear(uint max, uint min = 1) {
        std::piecewise_linear_distribution<double> dist(
            { 0.0, 0.5, 1.0 }, [](double x) { return 0.8 * x; }
        );

        double normalized = dist(engine); // Przekazywanie generatora przez referencjê
        double scaled = min + normalized * (max - min);
        return static_cast<uint>(std::floor(scaled));  // U¿ywanie std::floor dla ca³kowitych wyników
    }

    double customDistribution(int min, int max) {
        std::vector<int> numbers;
        for (int i = min; i <= max; i++) {
            numbers.push_back(i);
            if (i % 2 == 0) numbers.push_back(i); // Powielanie liczb parzystych
        }
        std::uniform_int_distribution<int> dist(0, numbers.size() - 1);
        return numbers[dist(engine)]; // Przekazywanie generatora przez referencjê
    }
};