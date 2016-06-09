#ifndef TABLERO_H
#define TABLERO_H
#include "Matriz.h"
#include <iostream>
#include <fstream>


class Tablero{
private:
	int filas,columnas;
	int fichas_objetivo;
	int fichas_por_turno;
	Matriz tablero;
	bool partida_finalizada;
	int turno_actual;
	int quien_empezo;
public:
	Tablero();

	Tablero(int nfichas, int por_turno, int filas, int columnas);

	int getFilas();

	int getColumnas();

	int getFichasObjetivo();

	int getFichasPorTurno();

	int getDato(int i, int j);

	bool getPartidaFinalizada();

	int getTurnoActual();

	Matriz getMatriz();

	int getQuienEmpezo();

	//Operaciones modifican
	void InsertaFicha(int columna);

	void Jugar(int i);

	void CompruebaPartida(int p );

	bool CalculaEmpate();

	int CalculaColumnas(int p);

	int CalculaFilas(int p);

	int CalculaDiagonalIzq(int p);

	int CalculaDiagonalDrcha(int p);

	int SolicitarColumna();

	bool ColumnaValida(int col);

	void setTurnoActual();

	void VaciaTablero();

	void prettyPrint(std::ostream &out =std::cout);

	//OPERACIONES SET
	void setFil(int i);
	
	void setCol(int j);

	void setFichas(int f);

	void setFichasPorTurno(int i);

	void setMatriz(Matriz m);

	void setPartidaFinalizada(bool b);

	void setTurno(int i);
	
	void setQuienEmpezo(int i);

	friend std::ostream& operator<<(std::ostream& os, Tablero &t);

	friend std::istream& operator>>(std::istream& is, Tablero &t);

};

#endif
