#include "Matriz.h"

Matriz::Matriz(){
  for(int i=0; i<MAX_FIL; i++)
	for(int j=0; j<MAX_COL; j++)
		setElemento(i,j,0);
  filas=0;
  columnas=0;
}

int Matriz::Columnas(){
	return columnas;
}

int Matriz::Filas(){
	return filas;
}

int Matriz::getElemento(int i ,int j){
	return datos[i][j];
}

void Matriz::setFilas(int i){
	filas=i;
}

void Matriz::setColumnas(int j){
	columnas=j;
}

void Matriz::setElemento(int i,int j,int ficha){
	if(ficha>=0 && ficha <=2)
		datos[i][j] = ficha;
}

//Especie de constructor que inicializa filas y columnas, reserva memoria para *datos y pone la matriz a 0
void Matriz::init(int i, int j){
	setFilas(i);
	setColumnas(j);

	for(int i=0; i<Filas(); i++)
		for(int j=0; j<Columnas(); j++)
			setElemento(i,j,0);
}
