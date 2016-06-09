#include "Matriz.h"

using namespace std;

Matriz::Matriz(){
  filas=0;
  columnas=0;
}

Matriz::Matriz(const Matriz &m){ //Constructor de copia
	filas=m.filas;
	columnas=m.columnas;
	datos=new int[filas*columnas];
	for(int i=0; i<Filas(); i++)
		for(int j=0; j<Columnas(); j++)
			datos[i*columnas+j]=m.datos[i*columnas+j];
}

Matriz& Matriz::operator=(const Matriz &m){ //Operador de asignación
	if(&m!=this){
		delete[] this->datos;
		this->filas=m.filas;
		this->columnas=m.columnas;
		this->datos=new int[this->filas*this->columnas];
		for(int i=0; i<Filas(); i++)
			for(int j=0; j<Columnas(); j++)
				this->datos[i*columnas+j]=m.datos[i*columnas+j];
	}

	return *this;
}

Matriz::~Matriz(){ //Destructor
	delete[] datos;
}

int Matriz::Columnas(){
	return columnas;
}

int Matriz::Filas(){
	return filas;
}

int Matriz::getElemento(int i ,int j){
	return datos[i*columnas+j];
}

void Matriz::setFilas(int i){
	if(i>=MAX_FIL)	
		filas=MAX_FIL;
	else
		filas=i;
}

void Matriz::setColumnas(int j){
	if(j>=MAX_COL)	
		columnas=MAX_COL;
	else
		columnas=j;
}

void Matriz::setElemento(int i,int j,int ficha){
	if(ficha>=0 && ficha <=2)
		datos[i*columnas+j] = ficha;
}

void Matriz::crear(){
	datos=new int[filas*columnas];
}

//Especie de constructor que inicializa filas y columnas, reserva memoria para *datos y pone la matriz a 0
void Matriz::init(int i, int j){
	setFilas(i);
	setColumnas(j);
	crear();
	for(int i=0; i<Filas(); i++)
		for(int j=0; j<Columnas(); j++)
			setElemento(i,j,0);
}

//SOBRECARGA E/S


ostream& operator<<(ostream& os, Matriz& m){
	os << m.Filas() << " " << m.Columnas() << "\n";
	for(int i=0; i<m.Filas(); i++)
		for(int j=0; j<m.Columnas(); j++)
			os << m.getElemento(i, j) << " ";
	return os;
}

istream& operator>>(istream& is, Matriz& m){
	int dato, fil, col;
	is >> fil;
	m.setFilas(fil);
	is >> col;
	m.setColumnas(col);
	
	m.crear();	

	for(int i=0; i<m.Filas(); i++){
		for(int j=0; j<m.Columnas(); j++){
			is >> dato;
			m.setElemento(i,j,dato);
		}
	}

	return is;
}
