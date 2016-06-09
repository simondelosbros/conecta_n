#ifndef JUGADOR_H
#define JUGADOR_H
#include "Matriz.h"
#include "Tablero.h"

class Jugador{
private:
	static const int MAX_CHAR = 50;
	char nombre[];
	int puntuacion;
	int partidas_ganadas;
	int partidas_empatadas;
public:
	Jugador(char nom[]);
	
	int getPartidasGanadas();

   	int getPartidasEmpatadas();

   	int getPuntuacion();

	char getTipoFicha(Tablero t);

	const char *getNombre();

	int CalculaPuntuacion(Tablero tablero);

	void Jugar(Tablero &t);

	int SolicitarColumna(Tablero t);

	bool ColumnaValida(int col,Tablero t);

	void setNombre(char n[]);	

   	void setPuntuacion(int puntos);

   	void setPartidasGanadas(int ganadas);

	void nueva_victoria();

	void nuevo_empate();

	void setEmpatadas(int empatadas);

	void ImprimeFinal();
};

#endif
