#ifndef JUGADOR_H
#define JUGADOR_H
#include "Tablero.h"
#include <fstream>

class Jugador{
private:
	char *nombre;
	int puntuacion;
	int partidas_ganadas;
	int partidas_empatadas;
	int n_insertadas;
public:
	Jugador();

	Jugador(char nom[]);

	Jugador(const Jugador &j);

	Jugador& operator=(const Jugador &j);
	
	~Jugador();
/*	
	std::ostream& operator<<(ostream& os, const Jugador &j);

	std::istream& operator>>(istream& is, Jugador &j);
*/
   	int getPartidasGanadas();

   	int getPartidasEmpatadas();

   	int getPuntuacion();

	char getTipoFicha(Tablero t);

	char *getNombre();

	int getNInsertadas();

	//int getTurno();


	//int ObtenerPuntuacion(Tablero t, int total_alineadas);

	int CalculaPuntuacion(Tablero tablero);

	bool Jugar(Tablero &t);

	int SolicitarColumna(Tablero t);

	bool ColumnaValida(int col,Tablero t);

	void setNombre(char n[]);	

   	void setPuntuacion(int puntos);

   	void setPartidasGanadas(int ganadas);
	
	void setNInsertadas(int n);
    
	void nueva_victoria();

	void nuevo_empate();

	void setEmpatadas(int empatadas);

	void ImprimeFinal();

	friend std::ostream& operator<<(std::ostream& os, Jugador &j);

	friend std::istream& operator>>(std::istream& is, Jugador &j);

};

#endif
