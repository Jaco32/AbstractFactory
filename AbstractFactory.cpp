//============================================================================
// Name        : AbstractFactory.cpp
// Author      : Jacek Węgorkiewicz
// Description : Implementacja przykładu fabryki abstrakcyjnej dla portalu
//               www.algorytm.org
//============================================================================

#include <iostream>
#include <string>

using namespace std;

class Dysk {
public:
	virtual Dysk* dawajDysk() = 0;
	virtual ~Dysk() {}
};

class Grafika {
public:
	virtual Grafika* dawajGrafike() = 0;
	virtual ~Grafika() {};
};

class RAM {
public:
	virtual RAM* dawajRAM() = 0;
	virtual ~RAM() {};
};

class Procesor {
public:
	virtual Procesor* dawajProcesor() = 0;
	virtual ~Procesor() {};
};

class Chlodzenie {
public:
	virtual Chlodzenie* dawajChlodzenie() = 0;
	virtual ~Chlodzenie() {};
};

class FabrykaPodzespolowKomputerowych {
public:
	virtual Dysk* produkujemyDysk() = 0;
	virtual Grafika* produkujemyGrafike() = 0;
	virtual RAM* produkujemyRAM() = 0;
	virtual Procesor* produkujemyProcesor() = 0;
	virtual Chlodzenie* produkujemyChlodzenie() = 0;
	virtual ~FabrykaPodzespolowKomputerowych() {}
};

class DyskDlaPC: public Dysk {
private:
	string name;
public:
	DyskDlaPC() { name = "DyskDlaPC"; }

	Dysk* dawajDysk() {
		cout << "Dodaje " + name << endl;
		return new DyskDlaPC();
	}
};

class GrafikaDlaPC: public Grafika {
private:
	string name;
public:
	GrafikaDlaPC() { name = "GrafikaDlaPC"; }

	Grafika* dawajGrafike() {
		cout << "Dodaje " + name << endl;
		return new GrafikaDlaPC();
	}
};

class DDR3: public RAM {
private:
	string name;
public:
	DDR3() { name = "DDR3"; }

	RAM* dawajRAM() {
		cout << "Dodaje " + name << endl;
		return new DDR3();
	}
};

class ProcesorDlaPC: public Procesor {
private:
	string name;
public:
	ProcesorDlaPC() { name = "ProcesorDlaPC"; }

	Procesor* dawajProcesor() {
		cout << "Dodaje " + name << endl;
		return new ProcesorDlaPC();
	}
};

class FabrykaPodzespolowPC:
	public FabrykaPodzespolowKomputerowych
{
public:
	Dysk* produkujemyDysk() {
		return new DyskDlaPC();
	}

	Grafika* produkujemyGrafike() {
		return new GrafikaDlaPC();
	}

	RAM* produkujemyRAM() {
		return new DDR3();
	}

	Procesor* produkujemyProcesor() {
		return new ProcesorDlaPC();
	}

	Chlodzenie* produkujemyChlodzenie() {
		return NULL;
	}
};

class DyskDlaLaptopa: public Dysk {
private:
	string name;
public:
	DyskDlaLaptopa() { name = "DyskDlaLaptopa"; }

	Dysk* dawajDysk() {
		cout << "Dodaje " + name << endl;
		return new DyskDlaLaptopa();
	}
};

class GrafikaDlaLaptopa: public Grafika {
private:
	string name;
public:
	GrafikaDlaLaptopa() { name = "GrafikaDlaLaptopa"; }

	Grafika* dawajGrafike() {
		cout << "Dodaje " + name << endl;
		return new GrafikaDlaLaptopa();
	}
};

class DDR2: public RAM {
private:
	string name;
public:
	DDR2() { name = "DDR2"; }

	RAM* dawajRAM() {
		cout << "Dodaje " + name << endl;
		return new DDR2();
	}
};

class ProcesorDlaLaptopa: public Procesor {
private:
	string name;
public:
	ProcesorDlaLaptopa() { name = "ProcesorDlaLaptopa"; }

	Procesor* dawajProcesor() {
		cout << "Dodaje " + name << endl;
		return new ProcesorDlaLaptopa();
	}
};

class ChlodzenieDlaLaptopa: public Chlodzenie {
private:
	string name;
public:
	ChlodzenieDlaLaptopa() { name = "ChlodzenieDlaLaptopa"; }

	Chlodzenie* dawajChlodzenie() {
		cout << "Dodaje " + name << endl;
		return new ChlodzenieDlaLaptopa();
	}
};

class FabrykaPodzespolowLaptop:
	public FabrykaPodzespolowKomputerowych
{
public:
	Dysk* produkujemyDysk() {
		return new DyskDlaLaptopa();
	}

	Grafika* produkujemyGrafike() {
		return new GrafikaDlaLaptopa();
	}

	RAM* produkujemyRAM() {
		return new DDR2();
	}

	Procesor* produkujemyProcesor() {
		return new ProcesorDlaLaptopa();
	}

	Chlodzenie* produkujemyChlodzenie() {
		return new ChlodzenieDlaLaptopa();
	}
};

class Komputer {
protected:
	Dysk* dysk; Dysk* dysk_tmp;
	Grafika* grafika; Grafika* grafika_tmp;
	RAM* ram; RAM* ram_tmp;
	Procesor* procesor; Procesor* procesor_tmp;
	Chlodzenie* chlodzenie; Chlodzenie* chlodzenie_tmp;

	virtual void skladanie() = 0;
public:
	void instalowanieOprogramowania() {
		cout << "Instalowanie oprogramowania..." << endl;
	}

	void pakowanie() {
		cout << "Pakowanie..." << endl;
	}

	void sprzedawanie() {
		cout << "Sprzedaje..." << endl;
	}

	virtual ~Komputer() { }
};

class KomputerPC: public Komputer {
private:
	FabrykaPodzespolowKomputerowych* f;
protected:
	void skladanie() {
		dysk_tmp = f->produkujemyDysk();
		dysk = dysk_tmp->dawajDysk();
		grafika_tmp = f->produkujemyGrafike();
		grafika = grafika_tmp->dawajGrafike();
		procesor_tmp = f->produkujemyProcesor();
		procesor = procesor_tmp->dawajProcesor();
		ram_tmp = f->produkujemyRAM();
		ram = ram_tmp->dawajRAM();
	}
public:
	KomputerPC(FabrykaPodzespolowPC* fPC) : f(fPC) {
		skladanie();
	}

	~KomputerPC() {
		delete ram_tmp; delete ram;
		delete procesor_tmp; delete procesor;
		delete grafika_tmp; delete grafika;
		delete dysk_tmp; delete dysk;
		delete f;
	}
};

class Laptop: public Komputer {
private:
	FabrykaPodzespolowKomputerowych* f;
protected:
	void skladanie() {
		dysk_tmp = f->produkujemyDysk();
		dysk = dysk_tmp->dawajDysk();
		grafika_tmp = f->produkujemyGrafike();
		grafika = grafika_tmp->dawajGrafike();
		procesor_tmp = f->produkujemyProcesor();
		procesor = procesor_tmp->dawajProcesor();
		ram_tmp = f->produkujemyRAM();
		ram = ram_tmp->dawajRAM();
		chlodzenie_tmp = f->produkujemyChlodzenie();
		chlodzenie = chlodzenie_tmp->dawajChlodzenie();
	}
public:
	Laptop(FabrykaPodzespolowLaptop *fLaptop) : f(fLaptop) {
		skladanie();
	}

	~Laptop() {
		delete chlodzenie_tmp; delete chlodzenie;
		delete ram_tmp; delete ram;
		delete procesor_tmp; delete procesor;
		delete grafika_tmp; delete grafika;
		delete dysk_tmp; delete dysk;
		delete f;
	}
};

class FabrykaKomputerow {
private:
	Komputer* zlozKomputer(string model) {
		Komputer* komputer;
		if("PC" == model)
			komputer = new KomputerPC(new FabrykaPodzespolowPC());
		else
			komputer = new Laptop(new FabrykaPodzespolowLaptop());

		return komputer;
	}
public:
	Komputer* wydajKomputer(string model) {
		Komputer* komputer = zlozKomputer(model);
		komputer->instalowanieOprogramowania();
		komputer->pakowanie();
		komputer->sprzedawanie();
		return komputer;
	}
};

int main() {
	FabrykaKomputerow* fabrykaKomputerow = new FabrykaKomputerow();

	Komputer* pc = fabrykaKomputerow->wydajKomputer("PC");
	Komputer* laptop = fabrykaKomputerow->wydajKomputer("Laptop");

	delete laptop;
	delete pc;
	delete fabrykaKomputerow;

	return 0;
}
