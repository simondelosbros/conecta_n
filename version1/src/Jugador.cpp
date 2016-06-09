#include <iostream>
#include "Jugador.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

Jugador::Jugador(char nom[]){
  	setNombre(nom);
	puntuacion=0;
	partidas_ganadas=0;
	partidas_empatadas=0;
}

void Jugador::setNombre(char n[]){
	strcpy(n,nombre);
}

char Jugador::getTipoFicha(Tablero t){
	if(t.getTurnoActual()==1)
		return 'x';
	else
		return 'o';
}

int Jugador::CalculaPuntuacion(Tablero tablero){
	int puntuacion = 0;
	for(int i = 0; i< tablero.getFilas();i++){
		for(int j = 0; j< tablero.getColumnas();j++){
			if(tablero.getDato(i,j) == 0){
				puntuacion++;
			}
		}
	}
	return puntuacion;
}

void Jugador::Jugar(Tablero &t){
	int col;
	do{
		system("clear");
		t.prettyPrint();
		col=SolicitarColumna(t);
	}while(ColumnaValida(col,t) != true);
	t.InsertaFicha(col);
	t.CompruebaPartida(t.getTurnoActual());
	if(t.getPartidaFinalizada() == false)
		t.setTurnoActual();
}

int Jugador::SolicitarColumna(Tablero t){
	int columna;
	char col;
	char letra  ='a' +t.getColumnas()-1;
	cout << "Turno: jugador " << t.getTurnoActual() << " : (" << getTipoFicha(t) << ")"<< endl;
	cout << getNombre() << ", escoja una columna (letra a-"<< letra<<"): ";
	cin >> col;
	columna = col-97;
	return columna;
}

bool Jugador::ColumnaValida(int col,Tablero t){
	bool result = false;
	if(col < t.getColumnas() && col >= 0 ){//si la columna está en el rango del total de columnas
		if(t.getDato(0,col) == 0){//si cabe al menos una ficha(en la primera fila) en la columna col
			result = true;
		}
	}

	return result;
}

// devuelve el nombre del jugador
const char *Jugador::getNombre(){
	return nombre;	
}

int Jugador::getPuntuacion(){
	return puntuacion;
}

void Jugador::setPuntuacion(int puntos){
	puntuacion += puntos;
}

int Jugador::getPartidasGanadas(){
	return partidas_ganadas;
}

void Jugador::setPartidasGanadas(int ganadas){
	partidas_ganadas = ganadas;
}

void Jugador::nueva_victoria(){
	partidas_ganadas++;
}

void Jugador::nuevo_empate(){
	partidas_empatadas++;
}

int Jugador::getPartidasEmpatadas(){
	return partidas_empatadas;
}

void Jugador::setEmpatadas(int empatadas){
	partidas_empatadas = empatadas;
}

void Jugador::ImprimeFinal(){
	cout << getNombre() << " : " << getPartidasGanadas() << " ganadas que acumulan "<< puntuacion << " puntos." << endl;
	cout << getPartidasEmpatadas() << " empatadas." << endl;
}
