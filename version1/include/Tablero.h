#ifndef TABLERO_H
#define TABLERO_H
#include "Matriz.h"

class Tablero{
private:
	int filas,columnas;
	int fichas_objetivo;
	Matriz tablero;
	bool partida_finalizada;
	int turno_actual;
public:
	Tablero(int nfichas, int filas, int columnas);

	int getFilas();

	int getColumnas();

	int getFichasObjetivo();

	int getDato(int i, int j);

	bool getPartidaFinalizada();

	int getTurnoActual();

	//Operaciones modifican
	void InsertaFicha(int columna);

	void Jugar(int i);

	void CompruebaPartida(int p);

	bool CalculaEmpate();

	int CalculaColumnas(int p);

	int CalculaFilas(int p);

	int CalculaDiagonalIzq(int p);

	int CalculaDiagonalDrcha(int p);

	void setTurnoActual();

	void VaciaTablero();

	void prettyPrint();
};

#endif
