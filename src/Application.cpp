#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>

#include "CPU.h"

void makeTestStats(Stats& s, const std::string& filepath) {
	std::ofstream file(filepath);

	file << s.sredniTAT << " " << s.sredniWT << "\n";

	for (Proces& p : s.vec) {
		file << p.getId() << " " <<
			p.getCzasDodania() << " " <<
			p.getCzasZakonczenia() << " " <<
			p.getPriorytet() << " " <<
			p.getCzasTrwania() << " " <<
			p.getTAT() << " " << // 6 statystyka
			p.getWT() << "\n"; //7 statystyka
	}

	file.close();
}

int main() {
	//-----------------------------------------------------GENEROWANIE I WYPISYWANIE DO STATYSTYK

	//const uint ilosc_Procesow = 100000;
	const uint ilosc_Procesow = 10000;
	ProcesGenerator rng;
	std::vector<Proces> vec = rng.generujProcesy({ 0.5, 0.4, 0.1 }, 1, 20, 1, 50, ilosc_Procesow);
	
	std::ofstream file("data.txt");

	for (Proces obj : vec) {
		file << obj.getPriorytet() << " " << obj.getCzasTrwania() << " " << obj.getCzasDodania() << std::endl;
	}
	file.close();

	//-----------------------------------------------------SORTOWANIE WZGLEDEM KOLEJNOSCI POJAWIANIA SIE

	std::sort(vec.begin(), vec.end(), [](const Proces& a, const Proces& b) {return a.getCzasDodania() < b.getCzasDodania(); });

	//-----------------------------------------------------WYWOLYWANIE SYMULACJI FCFS

	CPU cpu(0);
	Stats s1 = cpu.FCFS(vec);

	makeTestStats(s1, "FCFS.txt");

	//-----------------------------------------------------WYWOLYWANIE SYMULACJI SJF

	Stats s2 = cpu.SJF(vec);

	makeTestStats(s2, "SJF.txt");

	//------------------------------------------------------WYWOLYWANIE SYMULACJI SJF z wywlaszczaniem

	//Stats s3 = cpu.SJFW(vec);

	//makeTestStats(s3, "SJFW.txt");

	// testuj:
	// - algorytm
	// - 
	
	return 0;
}