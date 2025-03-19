#pragma once

#include <string>

#define uint size_t

class Proces {
private:
	uint id;
	uint czasDodania;
	uint czasZakonczenia;
	uint priorytet;
	uint czasTrwania;
	uint TAT;
	uint WT;
	uint czasProgres;

public:
	Proces(uint id, uint priorytet, uint czasTrwania, uint czasDodania)
		: id(id), priorytet(priorytet), czasTrwania(czasTrwania), czasDodania(czasDodania), czasZakonczenia(0), TAT(0), WT(0), czasProgres(0)
	{ }

	~Proces() {}

	inline uint getId() const{
		return id;
	}
	inline uint getCzasDodania() const {
		return czasDodania;
	}
	inline uint getCzasZakonczenia() const {
		return czasZakonczenia;
	}
	inline uint getPriorytet() const {
		return priorytet;
	}
	inline uint getCzasTrwania() const {
		return czasTrwania;
	}
	inline uint getTAT() const {
		return TAT;
	}
	inline uint getWT() const {
		return WT;
	}
	inline uint getCzasProgres() const {
		return czasProgres;
	}
	
	void setCzasZakonczenia(uint czasZakonczenia) {
		this->czasZakonczenia = czasZakonczenia;
	}
	void setTAT(uint TAT) {
		this->TAT = TAT;
	}
	void setWT(uint WT) {
		this->WT = WT;
	}
	void setCzasProgres(uint czasProgres) {
		this->czasProgres = czasProgres;
	}

	void incCzasProgres() {
		czasProgres++;
	}
	

	std::string toString() const {
		return std::to_string(id) + ": " + std::to_string(czasDodania) + " " + std::to_string(czasTrwania) + "\n";
	}

};