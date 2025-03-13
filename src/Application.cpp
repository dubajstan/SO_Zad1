#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

#include "Process.h"

#define uint unsigned int


using namespace std;

class Proces {
private:
	uint id, czasTrwania, priorytet, czasDodania, czasZakonczenia, czasOczekiwania;

public:
	Proces(uint id, uint czasTrwania, uint priorytet, uint czasDodania, uint czasZakonczenia) {
		this->id = id;
		this->czasTrwania = czasTrwania;
		this->priorytet = priorytet;
		this->czasDodania = czasDodania;
		this->czasZakonczenia = czasZakonczenia;
		czasOczekiwania = 0;
	}

	~Proces() {}

	inline uint getId() const {
		return id;
	}
	inline uint getCzasTrwania() const {
		return czasTrwania;
	}
	inline uint getPriorytet() const {
		return priorytet;
	}
	inline uint getCzasDodania() const {
		return czasDodania;
	}
	inline uint getCzasZakonczenia() const {
		return czasZakonczenia;
	}
	inline uint getCzasOczekiwania() const {
		return czasOczekiwania;
	}

	inline string toString() const {
		return "Proces " + to_string(id) + ": czas( " + to_string(czasDodania) + "; " + to_string(czasZakonczenia) + " )";
	}

};

class ComparatorStrategy {
public:
	virtual bool operator()(Proces& a, Proces& b) const = 0;
	virtual ~ComparatorStrategy() = default;
};

class ArrivalTimeComparator : public ComparatorStrategy {
public:
	bool operator() (Proces& a, Proces& b) const override {
		return a.getCzasDodania() < b.getCzasDodania();
	}
};

class BurstTimeComparator : public ComparatorStrategy {
public:
	bool operator() (Proces& a, Proces& b) const override{
		return a.getCzasTrwania() < b.getCzasTrwania();
	}
};

class CPU {
private:
	uint time;
	vector<Proces> terminatedProcesess;
	priority_queue<Proces> pq;
	ComparatorStrategy* comparator;
	uint quant;

public:
	CPU(vector<Proces>& vec, uint quant) {
		
	}

	~CPU() {}

	void setStrategy(ComparatorStrategy* comp) {
		comparator = comp;
	}

	void restart(priority_queue<Proces> pq, uint quant) {
		time = 0;
		terminatedProcesess.clear();
		this->pq = pq;
		this->quant = quant;
	}

	void 

	void simulate() {
		while (!pq.empty()) {
			//TODO: zaimplementowac dzialanie algorytmu
		}
	}

};



int main() {
	ArrivalTimeComparator arrivalTimeComparator;
	BurstTimeComparator burstTimeComparator;





	return 0;
}