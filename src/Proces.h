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
	uint czasProgres;

public:
	Proces(uint id, uint priorytet, uint czasTrwania, uint czasDodania)
		: id(id), priorytet(priorytet), czasTrwania(czasTrwania), czasDodania(czasDodania), czasZakonczenia(0), czasProgres(0)
	{ }

	~Proces() {}

	uint getId() const{
		return id;
	}
	uint getCzasDodania() const {
		return czasDodania;
	}
	uint getCzasZakonczenia() const {
		return czasZakonczenia;
	}
	uint getPriorytet() const {
		return priorytet;
	}
	uint getCzasTrwania() const {
		return czasTrwania;
	}
	uint getCzasProgres() const {
		return czasProgres;
	}
	
	void setCzasZakonczenia(uint czasZakonczenia) {
		this->czasZakonczenia = czasZakonczenia;
	}

	void setCzasProgres(uint czasProgres) {
		this->czasProgres = czasProgres;
	}

	void czasProgresIncrement() {
		czasProgres++;
	}

	std::string toString() const {
		return std::to_string(id) + ": " + std::to_string(czasDodania) + "\n";
	}

};