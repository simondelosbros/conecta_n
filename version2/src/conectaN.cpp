#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Tablero.h"
#include "Jugador.h"

using namespace std;

void OpcionGuardar(Jugador &j1, Jugador &j2, Tablero &t){ //Para no poder modificar los archivos de guardado, le quitaremos los permisos de escritura a todos los archivos *.conf del directorio. NOTA: si no hay ninguno en el directorio saltará un error de bash; no se como eliminar esa línea en la terminal :(
	char eleccion;
	cout << "¿Quieres guardar la partida? (S/N): ";
	cin >> eleccion;
	if(eleccion=='s'){
		system("chmod +w *.conf"); // ------> Por si quisieramos sobreescribir algun archivo
		char nombre[100];
		cout << "Introduzca el nombre del archivo a guardar (se añadirá automáticamente la extensión): ";
		cin.ignore();
		cin.getline(nombre, 100);
		strcat(nombre, ".conf");

		cout << "Guardando...\n";
		system("sleep 1");
		cout << "...\n";
		system("sleep 1");
		cout << "...\n";
		system("sleep 1");
		
		ofstream f(nombre);		
		f << "#MP-CONECTAN-1.0" << endl;
		f << j1;
		f << j2;
		f << t;
		f << "\n";
		f.close();
		
		system("chmod -w *.conf"); // ------> Ahora no se podrá modificar el archivo de guardado
	}
}

bool Cargar(const char *nombre_archivo, Jugador& j1, Jugador& j2, Tablero& t){
	ifstream f(nombre_archivo);
	cout << "Cargando partida...\n";
	system("sleep 2"); //No me gusta que cargue la partida tan rapido jajaja
	
	if(f){
		char compara[20];
		f.getline(compara,20);

		if(strcmp(compara,"#MP-CONECTAN-1.0")!=0){
			//cout << "No son iguales.\n" << compara << "\n";
			return false;
		}

		f >> j1;
		f >> j2;
		f >> t;
		f.close();
		return true;
	}else
		return false;

}

int main(int argc, char *argv[]){
	int fil=0, col=0, fichas_a_alinear=0, fichas_por_turno=0;
	const int TAMANIO=100;
	char nombre1[TAMANIO], nombre2[TAMANIO];
	char opcion = 's';

	system("clear");
	
	Jugador j1,j2;
	Tablero t;
	
	//INICIALIZACIÓN
	if(argc==2){
		bool exito=Cargar(argv[1],j1,j2,t);
		if(exito==false){
			cout << "\nError al cargar el archivo; puede que no exista o que no sea un archivo de guardado de ConectaN.\n";
			exit(0);		
		}
		
	}else if(argc==1){
		do{
			cout << "Introduzca filas: ";
			cin >> fil;
		}while (fil < 4 || fil > 20);

		do{
			cout << "\n"<< "Introduzca columnas: ";
			cin >> col;
		}while (col < 4 || col > 20);

		do{
			cout << "\n"<< "Introduzca fichas a alinear (3-6): ";
			cin >> fichas_a_alinear;
		}while(fichas_a_alinear < 3 || fichas_a_alinear > 6);

		do{
			cout << "\n" << "Introduzca fichas por turno (1-" << fichas_a_alinear-2 <<"): ";
			cin >>fichas_por_turno;
		}while(fichas_por_turno < 1 || fichas_por_turno > fichas_a_alinear-2);

		cin.ignore(); //Porque el getline reacciona al intro introducido en cin >> fichas_a_alinear;
		cout << "\n"<< "Introduzca nombre del primer jugador: ";
		cin.getline(nombre1, TAMANIO/2);

		cout << "\n"<< "Introduzca nombre del segundo jugador: ";
		cin.getline(nombre2, TAMANIO/2);

	}else{
		cout << "\nNúmero incorrecto de argumentos (./conectan comienza el juego desde cero; ./conectan [archivo.conf] carga una partida).\n";
		exit(0);
	}
	
	Tablero tablero(fichas_a_alinear,fichas_por_turno, fil,col);
	Jugador jugador1(nombre1);
	Jugador jugador2(nombre2);

	if(argc==2){
		tablero=t;
		jugador1=j1;
		jugador2=j2;	
	}
	
	system("clear");
	
	//Comienza el juego
	while(opcion == 's'){
		while(tablero.getPartidaFinalizada() != true){
			bool exito;
			if(tablero.getTurnoActual() == 1){
				do{
					exito=jugador1.Jugar(tablero);
					if(exito==false){
						cout << "Opción incorrecta. ";
						OpcionGuardar(jugador1,jugador2,tablero);	
					}
				}while(exito!=true);

			}
			if(tablero.getTurnoActual() == 2){
				do{
					exito=jugador2.Jugar(tablero);
					if(exito==false){
						cout << "Opción incorrecta. ";
						OpcionGuardar(jugador1,jugador2,tablero);	
					}
				}while(exito!=true);
			}
		}

		system("clear");
		tablero.prettyPrint();
		if(tablero.getTurnoActual() == 1 && jugador1.CalculaPuntuacion(tablero) != 0 ){
			jugador1.setPuntuacion(jugador1.CalculaPuntuacion(tablero));
			jugador1.nueva_victoria();
			cout << "\nPartida finalizada. Ganador: jugador " << tablero.getTurnoActual() << endl;
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
			jugador1.setNInsertadas(0);
			jugador2.setNInsertadas(0);
		}
	}

	if(opcion != 's' ){
		system("clear");
        	cout << "Resultados finales: "<<endl;
        	jugador1.ImprimeFinal();
        	jugador2.ImprimeFinal();
		cout << "\n";
		tablero.VaciaTablero();
		OpcionGuardar(jugador1,jugador2,tablero);

        	//cout << tablero.getEmpatadas() << " empatadas."<< endl;
    	}



}
