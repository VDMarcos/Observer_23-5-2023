#include<iostream>
#include<sstream>
#include<Windows.h>

using namespace std;

//observer Padre
//----------------------------------------------------------------------------------------------------------------------
class Partido {
protected:
	int valorPLN;
	int valorPUSC;
	int valorPSD;
public:
	Partido();
	virtual~Partido();
	virtual void upDate(int, int, int) = 0;
	virtual string toString() = 0;
	virtual void graficando() = 0;
	virtual int getValPLN();
	virtual int getValPUSC();
	virtual int getValPSD();
};

Partido::Partido()
{
	cout << "Construyendo partido...\n";
	valorPLN = 0;
	valorPSD = 0;
	valorPUSC = 0;
}

Partido::~Partido()
{
}

int Partido::getValPLN()
{
	return valorPLN;
}

int Partido::getValPUSC()
{
	return valorPUSC;
}

int Partido::getValPSD()
{
	return valorPSD;
}
//----------------------------------------------------------------------------------------------------------------------

//Subclases...formas de ver...

class PartidoLiberacion : public Partido {

private:
	string nombre;
	//etc...
public:
	PartidoLiberacion() : Partido() {
		nombre = "Partido Liberacion Nacional";
	}
	virtual~PartidoLiberacion(){}
	void upDate(int a, int b, int c) {
		this->valorPLN += a;
		this->valorPUSC += b;
		this->valorPSD += c;
	}
	string toString() {
		stringstream s;
		s << "--------" << nombre << "--------\n";
		s << "Votos a PLN: " << valorPLN << endl;
		s << "Votos a PUSC: " << valorPUSC << endl;
		s << "Votos a PSD: " << valorPSD << endl;
		return s.str();
	}
	void graficando() {
		//esta vision no le interesa al PLN...
	}
};

//----------------------------------------------------------------------------------------------------------------------

class PartidoUnidad : public Partido {

private:
	string nombre;
	//etc...
public:
	PartidoUnidad() : Partido() {
		nombre = "Partido Unidad Cristiana";
	}
	virtual~PartidoUnidad() {}
	void upDate(int a, int b, int c) {
		this->valorPLN += a;
		this->valorPUSC += b;
		this->valorPSD += c;
	}
	string toString() {
		return "";         //al de unidad no le interesa al toString...
	}
	void graficando() {
		cout << "1-PLN = \n";
		for (int i = 0; i < valorPLN/100; i++)
			cout << "*\t"; 
		cout << endl;
		cout << "1-PUSC = \n";
		for (int i = 0; i < valorPUSC/100; i++)
			cout << "*\t";
		cout << endl;
		cout << "1-PSD = \n";
		for (int i = 0; i < valorPSD/100; i++)
			cout << "*\t";
		cout << endl;
	}
};

//----------------------------------------------------------------------------------------------------------------------

class PartidoSocialDemocrata : public Partido {

private:
	string nombre;
	//etc...
public:
	PartidoSocialDemocrata() : Partido() {
		nombre = "Partido Social Democrata";
	}
	virtual~PartidoSocialDemocrata() {}
	void upDate(int a, int b, int c) {
		this->valorPLN += a;
		this->valorPUSC += b;
		this->valorPSD += c;
	}
	string toString() {
		int sumaVotos = valorPLN + valorPUSC + valorPSD;
		stringstream s; 
		s << "--------" << nombre << "--------\n"; 
		s << "Porcentajes...PLN: " << (double)valorPLN * 100 / sumaVotos << "%" << endl;
		s << "Porcentajes...PUSC: " << (double)valorPUSC * 100 / sumaVotos << "%" << endl;
		s << "Porcentajes...PSD: " << (double)valorPSD * 100 / sumaVotos << "%" << endl;
		return s.str();  
	}
	void graficando() {
		//no les interesa...
	}
};

//----------------------------------------------------------------------------------------------------------------------

//SUBJECT -> LO OBSERVADO -> TSE...
// los 3 importantes aca, son -> attach, setValores y notify...

class TSE {
private:
	int numMesa;
	int valor1;      //votos de la mesa numMesa del PLN...
	int valor2;      //votos de la mesa numMesa del PUSC...
	int valor3;      //votos de la mesa numMesa del PSD...
	//aca cont de observers
	Partido** vec;
	int can;
	int tam;
public:
	TSE();
	virtual~TSE();
	void attach(Partido*);   //agrega observer...  
	void setValores(int a, int b, int c); //setea sus valores por cada mesa nueva...
	void notify(); //notificar de los cambios(nueva mesa) a todos los observers...
	void conteoDeVotosXMesa();
	void infoDeMesa();
	void solicitudDeNuevaMesa();
};

TSE::TSE()
{
	numMesa = 0;
	valor1 = 0;
	valor2 = 0;
	valor3 = 0;
	//contenedor...
	vec = new Partido * [5];
	tam = 5;
	can = 0;
	for (int i = 0; i < tam; i++)
		vec[i] = NULL;
}

TSE::~TSE()
{
	for (int i = 0; i < can; i++)
		delete vec[i];
	delete[] vec;
}

void TSE::attach(Partido* obs)
{
	if (can < tam)
		vec[can++] = obs;
}

void TSE::setValores(int a, int b, int c)
{
	valor1 = a;
	valor2 = b;
	valor3 = c;
	notify();
}

void TSE::notify()
{
	for (int i = 0; i < can; i++)
		vec[i]->upDate(valor1, valor2, valor3);
}

void TSE::conteoDeVotosXMesa()
{
	int V1 = 0;
	int V2 = 0;
	int V3 = 0;
	V1 = 1 + rand() / (101 - 1);
	V2 = 1 + rand() / (101 - 1);
	V3 = 1 + rand() / (101 - 1);
	numMesa = 1 + rand() % (10001 - 1);
	//valores random...
	this->setValores(V1, V2, V3);    //facil facil pa
}

void TSE::infoDeMesa()
{
	cout << "INFORMACION DE LA MESA NUM: " << numMesa << endl;
	cout << "PLN: " << valor1 << " votos.\n";
	cout << "PUSC: " << valor1 << " votos.\n";
	cout << "PSD: " << valor1 << " votos.\n";
}

void TSE::solicitudDeNuevaMesa()
{
	this->conteoDeVotosXMesa();
}

//----------------------------------------------------------------------------------------------------------------------
//fin del subject


int main() {

	int x = 0;

	cout << "-----------PARTICIPACION POPULAR-----------\n";
	cout << "Creacion de los obervers Partidos Politicos...\n";
	Partido* obs1 = new PartidoLiberacion();
	Partido* obs2 = new PartidoUnidad(); 
	Partido* obs3 = new PartidoSocialDemocrata(); 

	cout << "Creacion del TSE (SUBJECT)...\n";
	TSE* tribu = new TSE();

	system("pause");

	tribu->attach(obs1);
	tribu->attach(obs2);
	tribu->attach(obs3);

	tribu->infoDeMesa();

	while (x < 100) {
		system("cls");
		cout << "--------------------TSE--------------------\n";
		tribu->solicitudDeNuevaMesa();
		cout << "INFORMACION DE LA MESA: \n";
		tribu->infoDeMesa();
		cout << "-----INFORMACION E LA VISTA DE LOS PATIDOS POLITICOS\n";
		cout << obs1->toString() << endl;
		obs2->graficando();
		cout << obs3->toString() << endl;
		x++;
		system("pause");
	}
	system("pause");

	return 0;
}