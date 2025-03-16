#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#include "ProcesGenerator.h"

#define uint unsigned int

class SchedulingStrategy {
public:
	virtual void simulate(const std::vector<Proces>& vec) = 0;
	virtual ~SchedulingStrategy() = default;

};

class FCFS : public SchedulingStrategy {
private:
	struct Comparator {
		bool operator()(const Proces& a, const Proces& b) {
			return a.getCzasDodania() < b.getCzasDodania();
		}
	};
public:
	void simulate(const std::vector<Proces>& vec) override {
		
	}
};

class CPU {
	std::unique_ptr<SchedulingStrategy> strategy = std::make_unique<FCFS>();
public:
	void simulate() {

		//strategia->simulate();
	}

};