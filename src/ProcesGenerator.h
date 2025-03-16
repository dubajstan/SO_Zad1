#pragma once

#include <random>
#include <fstream>
#include <vector>
#include <cmath>  // Do std::floor()
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <numeric>

#include "Proces.h"

#define uint unsigned int

class DistributionStrategy {
public:
    virtual uint generate(double max, double min) = 0;
    virtual ~DistributionStrategy() = default;
};

class GaussianDistribution : public DistributionStrategy {
private:
    std::mt19937& engine;

public:
    explicit GaussianDistribution(std::mt19937& engine)
        : engine(engine)
    {}

    ~GaussianDistribution() {}

    uint generate(double max, double min) override{
        double mean = 0.5;
        double stddev = 0.2;
        std::normal_distribution<> dist(mean, stddev);

        double normalized = std::clamp(dist(engine), 0.0, 1.0);
        double val = normalized * (max - min) + min;
        return static_cast<uint>(val);
    }
};

class LinearDistribution : public DistributionStrategy {
private:
    std::mt19937& engine;

public:
    LinearDistribution(std::mt19937& engine)
        : engine(engine)
    { }
    ~LinearDistribution() {}

    uint generate(double max, double min) override {
        std::piecewise_linear_distribution<double> dist(
            { 0.0, 0.5, 1.0 }, [](double x) {return x; }
        );
        double normalized = std::clamp(dist(engine), 0.0, 1.0);
        double val = normalized * (max - min) + min;
        return static_cast<uint>(val);
    }
};

// To jest chyba blednie zrobione
class DiscreteDistribution : public DistributionStrategy {
private:
    std::mt19937& engine;

public:
    DiscreteDistribution(std::mt19937& engine)
        : engine(engine)
    {}
    ~DiscreteDistribution() {}

    uint generate(double max, double min) override {
        uint m_Max = static_cast<uint>(max);
        uint m_Min = static_cast<uint>(min);
        std::vector<double> propability = { 0.5, 0.3, 0.2 };
        std::discrete_distribution<> dist(propability.begin(), propability.end());
        return static_cast<uint>(dist(engine) + 1);
    }
};

class InverseLinearDistribution : public DistributionStrategy {
private:
    std::mt19937& engine;

public:
    InverseLinearDistribution(std::mt19937& engine)
        : engine(engine)
    {
    }
    ~InverseLinearDistribution() {}

    uint generate(double max, double min) override {
        std::piecewise_linear_distribution<double> dist(
            { 0.0, 0.5, 1.0 }, [](double x) {return 1.0-x; }
        );
        double normalized = std::clamp(dist(engine), 0.0, 1.0);
        double val = normalized * (max - min) + min;
        return static_cast<uint>(val);
    }
};



class ProcesGenerator {
private:
    std::mt19937 engine;

    //std::unique_ptr<DistributionStrategy> priorytetStrategy;
    std::unique_ptr<DistributionStrategy> czasTrwaniaStrategy;
    std::unique_ptr<DistributionStrategy> czasDodaniaStrategy;

public:
    // Konstruktor z seedem, zabezpieczony przed niejawna konwersja
    explicit ProcesGenerator(unsigned int seed)
        : engine(seed)
    {
        czasTrwaniaStrategy = std::make_unique<GaussianDistribution>(engine);
        czasDodaniaStrategy = std::make_unique<LinearDistribution>(engine);
    }

    ProcesGenerator() {
        std::random_device rd;
        engine.seed(rd());

        czasTrwaniaStrategy = std::make_unique<GaussianDistribution>(engine);
        czasDodaniaStrategy = std::make_unique<LinearDistribution>(engine);
    }

    ~ProcesGenerator() {}

    std::mt19937 getEngine() {
        return engine;
    }
    /*
    void setPriorytetStrategy(std::unique_ptr<DistributionStrategy> strategy) {
        priorytetStrategy = std::move(strategy);
    }
    */

    void setCzasTrwaniaStrategy(std::unique_ptr<DistributionStrategy> strategy) {
        czasTrwaniaStrategy = std::move(strategy);
    }

    void setCzasDodaniaStrategy(std::unique_ptr<DistributionStrategy> strategy) {
        czasDodaniaStrategy = std::move(strategy);
    }

    uint discrete(double a, double b, double c) {
        std::vector<double> probability = { a, b, c };
        std::discrete_distribution<> dist(probability.begin(), probability.end());
        return static_cast<uint>(dist(engine) + 1);
    }

    std::vector<Proces> generujProcesy(const std::vector<double>& p, const size_t& count) {
        std::vector<Proces> vec;
        vec.reserve(count);

        if (/*!priorytetStrategy ||*/ !czasTrwaniaStrategy || !czasDodaniaStrategy) {
            std::cout << "B³¹d: strategie nie s¹ ustawione!\n";
            return vec;
        }

        if (p.size() != 3)
        {
            std::cout << "blad w wektorze\n";
            return vec;
        }

        for (size_t i = 1; i <= count; i++) {
            vec.emplace_back(i, discrete(p[0], p[1], p[2]), czasTrwaniaStrategy->generate(50, 1), czasDodaniaStrategy->generate(10000,1));
        }

        return vec;
    }
    
};

/*
- czas trwania - ma znajdowac sie na rozkladach: gausa, liniowych, odwrotnie liniowych, jednym customowym
- priorytet - ma raz byc jednakowy dla wszystkich, raz ma byc losowy, raz ma byc na [1,2,3], gdzie odpowiadajacy rozkld to [50%, 40%, 10$]
- czasDodania - ma byc raz rownomierny, raz np. gaus dla zwiekszenia ilosci wielu procesow na poczatku, (raz liniowy i odwrotnie liniowy)?

*/