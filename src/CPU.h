#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

#include "ProcesGenerator.h"

class SchedulingStrategy {
public:
	virtual void simulate(std::vector<Proces> vec) = 0;
	virtual ~SchedulingStrategy() = default;

};

class FCFS : public SchedulingStrategy {
private:
	struct Comparator {
		bool operator()(const Proces* a, const Proces* b) {
			return a->getCzasDodania() > b->getCzasDodania();
		}
	};

public:
	void simulate(std::vector<Proces> vec) override {
		std::priority_queue<Proces*, std::vector<Proces*>, Comparator> pq;

		for (Proces& p : vec) {
			pq.push(&p);
		}

		/*
		std::cout << "Wypisanie elementow:\n";

		while (!pq.empty()){
			std::cout << pq.top().toString();
			pq.pop();
		}
		*/

		std::cout << "Symulacja:\n";

		uint i_Count = 0;
		uint switch_Count = 0;

		Proces* curr = nullptr;
		Proces* next = nullptr;

		while (!pq.empty() && i_Count < LLONG_MAX - 10) { // ZABEZPIECZENIE ITERACJI PRZED PRZEPELNIENIEM
			if (curr == nullptr) {
				curr = pq.top();
				pq.pop();
			}
			i_Count++;
		}
		std::cout << i_Count;

		for (const Proces& p : vec) {
			std::cout << p.getCzasZakonczenia() << std::endl;
		}
		std::cout << "ZAKONCZONO\n";
	}
};

class CPU {
	std::unique_ptr<SchedulingStrategy> strategy = std::make_unique<FCFS>();

public:
	void simulate(std::vector<Proces>& vec) {

		strategy->simulate(vec);
	}

};