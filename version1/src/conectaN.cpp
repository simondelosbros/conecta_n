#include <iostream>
#include <stdlib.h>
#include "Tablero.h"
#include "Jugador.h"

using namespace std;

int main(){
	const int TAMANIO=100;
	int fil, col, fichas_a_alinear;
	char nombre1[TAMANIO], nombre2[TAMANIO];
	char opcion = 's';

	system("clear");
	
	do{
		cout << "Introduzca filas: ";
		cin >> fil;
	}while (fil < 4 || fil > 20);

	do{
		cout << "\n"<< "Introduzca columnas: ";
		cin >> col;
	}while (col < 4 || col > 20);

	do{
		cout << "\n"<< "Introduzca fichas a alinear (3-5): ";
		cin >> fichas_a_alinear;
	}while(fichas_a_alinear < 3 || fichas_a_alinear > 5);

	cin.ignore();

	cout << "\n"<< "Introduzca nombre del primer jugador: ";
	cin.getline(nombre1, 50);

	cout << "\n"<< "Introduzca nombre del segundo jugador: ";
	cin.getline(nombre2, 50);

	Jugador jugador1(nombre1);
	Jugador jugador2(nombre2);
	Tablero tablero(fichas_a_alinear,fil,col);
	
	while(opcion == 's'){
		while(tablero.getPartidaFinalizada() != true){
			if(tablero.getTurnoActual() == 1){
				jugador1.Jugar(tablero);
			}
			if(tablero.getTurnoActual() == 2){
				jugador2.Jugar(tablero);
			}
		}

		system("clear");
		tablero.prettyPrint();
		if(tablero.getTurnoActual() == 1 && jugador1.CalculaPuntuacion(tablero) != 0 ){
			jugador1.setPuntuacion(jugador1.CalculaPuntuacion(tablero));
			jugador1.nueva_victoria();
			cout << "Partida finalizada. Ganador: jugador " << tablero.getTurnoActual() << endl;
			cout << "Resultados tras esta partida:" << endl;
			jugador1.ImprimeFinal();
			jugador2.ImprimeFinal();
		}
		
		if(tablero.getTurnoActual() == 2 && jugador2.CalculaPuntuacion(tablero) != 0){
			jugador2.setPuntuacion(jugador1.CalculaPuntuacion(tablero));
			jugador2.nueva_victoria();
			cout << "Partida finalizada. Ganador: jugador " << tablero.getTurnoActual() << endl;
			cout << "Resultados tras esta partida:" << endl;
			jugador1.ImprimeFinal();
			jugador2.ImprimeFinal();
		}
		if(jugador1.CalculaPuntuacion(tablero) == 0  && jugador2.CalculaPuntuacion(tablero) == 0){
			jugador1.nuevo_empate();
			jugador2.nuevo_empate();
			cout << "Partida finalizada. Empate "  << endl;
			cout << "Resultados tras esta partida:" << endl;
			jugador1.ImprimeFinal();
			jugador2.ImprimeFinal();
		}
		

		cout << "¿Jugar de nuevo(S/N)?: ";
		cin  >> opcion;
		if(opcion == 's'){
			tablero.VaciaTablero();
		}
	}

	if(opcion != 's' ){
		system("clear");
        	cout << "Resultados finales: "<<endl;
        	jugador1.ImprimeFinal();
        	jugador2.ImprimeFinal();
	}

	cout << "\n\n";
    
}
