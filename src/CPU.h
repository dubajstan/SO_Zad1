#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

#include "ProcesGenerator.h"

struct Stats {
	std::vector<Proces> vec;
	uint time;
	uint switch_Count;
	uint sredniTAT;
	uint sredniWT;
};

class CPU {
private:
	uint quant = UINT_MAX;

public:

	CPU(uint quant) 
		: quant(quant)
	{ }

	~CPU() {}

	void makeStats(uint& sredniTAT, uint& sredniWT, std::vector<Proces>& terminated) {
		for (Proces& p : terminated) {
			p.setTAT(p.getCzasZakonczenia() - p.getCzasDodania());
			p.setWT(p.getTAT() - p.getCzasTrwania());
			sredniTAT += p.getTAT();
			sredniWT += p.getWT();
		}
		sredniTAT /= terminated.size();
		sredniWT /= terminated.size();
	}

	Stats FCFS(std::vector<Proces>& vec){
		// WYPELNIANIE KOLEJKI FIFO
		std::queue<Proces> q;
		for (Proces& p : vec) {
			q.push(p);
		}
		
		// Stworzenie zwracanej kolekcji zakonczonych procesow
		std::vector<Proces> terminated;

		// Tworzenie zmiennych time, switch_Count
		uint time = 0;
		uint switch_Count = 0;


		while (!q.empty() && time < UINT_MAX - 10) {
			if (q.front().getCzasDodania() <= time) {
				time += q.front().getCzasTrwania();
				q.front().setCzasZakonczenia(time);
				terminated.push_back(q.front());
				q.pop();
				switch_Count++;
			}
			else {
				time++;
			}
		}

		if (terminated.size() == 0) {
			return { {}, 0, 0, 0, 0 };
		}

		uint sredniTAT = 0;
		uint sredniWT = 0;

		makeStats(sredniTAT, sredniWT, terminated);
		std::cout << "SredniTAT: " << sredniTAT << std::endl;
		

		return { terminated, time, switch_Count, sredniTAT, sredniWT };
	}

	static struct Comparator {
		bool operator()(Proces& a, Proces& b) {
			return a.getCzasTrwania() > b.getCzasTrwania();
		}
	};

	Stats SJF(std::vector<Proces>& vec) {
		std::priority_queue<Proces, std::vector<Proces>, Comparator> pq;
		//std::vector<Proces> pq;

		std::vector<Proces> terminated;

		uint time = 0;
		uint switch_Count = 0;
		uint i = 0;

		while ((!pq.empty() || i < vec.size()) && time < UINT_MAX - 10) {
			while (i < vec.size() && vec[i].getCzasDodania() <= time) {
				pq.push(vec[i]);
				//pq.push_back(vec[i]);
				i++;
				//
				//std::sort(pq.begin(), pq.end(), [](Proces& a, Proces& b) {return a.getCzasDodania() > b.getCzasDodania(); });
			}

			if (!pq.empty()) {
				Proces curr = pq.top();
				pq.pop();
				//Proces curr = pq.back();
				//pq.pop_back();
				time += curr.getCzasTrwania();
				curr.setCzasZakonczenia(time);
				terminated.push_back(curr);
				switch_Count++;
			}
			else {
				time++;
			}
		}

		if (terminated.size() == 0) {
			return { {}, 0, 0, 0, 0 };
		}

		uint sredniTAT = 0;
		uint sredniWT = 0;
		makeStats(sredniTAT, sredniWT, terminated);

		return { terminated, time, switch_Count, sredniTAT, sredniWT };
	}

	/*
	Stats SJFW(std::vector<Proces>& vec) {
		std::priority_queue<Proces, std::vector<Proces>, Comparator> pq;

		std::vector<Proces> terminated;

		uint time = 0;
		uint switch_Count = 0;

		while ((!vec.empty() || !pq.empty()) && time < UINT_MAX - 10) {
			while (!vec.empty() && vec.front().getCzasDodania() <= time) {
				pq.push(vec.front());
				vec.erase(vec.begin());
			}
		}

		uint sredniTAT = 0;
		uint sredniWT = 0;
		makeStats(sredniTAT, sredniWT, terminated);

		return { terminated, time, switch_Count, sredniTAT, sredniWT };
	}
	*/

};

// Moze lepiej by bylo zrobic to na kolejce priorytetowej