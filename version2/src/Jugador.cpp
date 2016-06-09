#include "Jugador.h"
#include "Tablero.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Jugador::Jugador(){ //constructor por defecto
	setNombre("\0");
	puntuacion=0;
	setPartidasGanadas(0);
	setEmpatadas(0);
	n_insertadas=0;
}

Jugador::Jugador(char nom[]){
  	setNombre(nom);
	puntuacion=0;
	setPartidasGanadas(0);
	setEmpatadas(0);
	n_insertadas=0;
	//turno=n;
}

Jugador::Jugador(const Jugador &j){
	//turno=j.turno;
	puntuacion=j.puntuacion;
	partidas_ganadas=j.partidas_ganadas;
	n_insertadas=j.n_insertadas;
	int tamanio=strlen(j.nombre)+1;
	nombre=new char[tamanio];
	strcpy(nombre, j.nombre);
}

Jugador& Jugador::operator=(const Jugador &j){
	if(&j!=this){
		delete[] this->nombre;
		//this->turno=j.turno;
		this->puntuacion=j.puntuacion;
		this->partidas_ganadas=j.partidas_ganadas;
		this->n_insertadas=j.n_insertadas;
		int tamanio=strlen(j.nombre)+1;
		this->nombre=new char[tamanio];
		strcpy(this->nombre,j.nombre);
	}

	return *this;
}

Jugador::~Jugador(){
	delete[] nombre;
}

int Jugador::getPartidasGanadas(){
	return partidas_ganadas;
}

int Jugador::getNInsertadas(){
	return n_insertadas;
}

void Jugador::setNombre(char n[]){
	int tamanio=strlen(n)+1;
	nombre=new char[tamanio];
	for(int i=0; i<tamanio; i++)
		nombre[i]=n[i];
	
}

int Jugador::getPuntuacion(){
	return puntuacion;
}

char Jugador::getTipoFicha(Tablero t){
	if(t.getTurnoActual()==1)
		return 'x';
	else
		return 'o';
}

int Jugador::CalculaPuntuacion(Tablero tablero){
	int puntuacion = 0;
	for (int i = 0; i< tablero.getFilas();i++){
		for(int j = 0; j< tablero.getColumnas();j++){
			if(tablero.getDato(i,j) == 0){
				puntuacion++;
			}
		}
	}
	return puntuacion;
}

bool Jugador::Jugar(Tablero &t){
	int col=-1;
	bool exito=true;
	system("clear");
	t.prettyPrint();
	
	while(n_insertadas<t.getFichasPorTurno() && exito != false && t.getPartidaFinalizada()==false){
		col = SolicitarColumna(t);
		exito=ColumnaValida(col,t);
		if(exito==true){
			t.InsertaFicha(col);
			t.CompruebaPartida(t.getTurnoActual());
			n_insertadas++;
			system("clear");
			t.prettyPrint();
		}
	}
	
	if(exito==true){
		t.setTurnoActual();	
		n_insertadas=0;
	}
	
	return exito;
}

int Jugador::SolicitarColumna(Tablero t){
	int columna;
	if(nombre[0] == '@'){
		srand(time(NULL));
		do{
       			columna=rand()%t.getColumnas();
		}while(t.getDato(0,columna)!=0);
		char letra=columna+97;
		cout << "Turno: jugador " << t.getTurnoActual() << " : (" << getTipoFicha(t) << ")"<< endl;
		cout << "Ficha " << n_insertadas+1 << " de " << t.getFichasPorTurno() << ".\n";
		cout << "El jugador " << getNombre() << " introducirá una ficha en la columna " << letra << ".\n";
		system("sleep 3");
	}
	else{
		char col;
		char letra  ='a' +t.getColumnas()-1;
		cout << "Turno: jugador " << t.getTurnoActual() << " : (" << getTipoFicha(t) << ")"<< endl;//Turno: jugador 1: (x)
		cout << "Ficha " << n_insertadas+1 << " de " << t.getFichasPorTurno() << ".\n";
		cout << getNombre() << ", escoja una columna (letra a-"<< letra<<"): ";
		cin >> col;
		columna = col -97;
	}
	//cout << "He solicitado la columna " << columna << endl;
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
char *Jugador::getNombre(){
	return this->nombre;
}

int Jugador::getPartidasEmpatadas(){
	return partidas_empatadas;
}

// devuelve el turno del jugador
/*
int Jugador::getTurno(){
	return turno;
}*/
/*/
void Jugador::setTurno(int i){
	turno = i;
}
*/
void Jugador::setPuntuacion(int puntos){
	puntuacion += puntos;

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

void Jugador::setEmpatadas(int empatadas){
	partidas_empatadas = empatadas;
}

void Jugador::setNInsertadas(int n){
	n_insertadas=n;
}

void Jugador::ImprimeFinal(){

	cout << getNombre() << " : " << getPartidasGanadas() << " ganadas que acumulan "<< puntuacion << " puntos." << endl;
	cout << getPartidasEmpatadas() << " empatadas." << endl;
}

/*
void Jugador::Escribir(const char nombre[]){
	ofstream f(nombre);
	ostream& os = f;		
	os << "MP-BUSCAMINAS-V2" << endl;
	os << this;
	f.close();
}

void Jugador::Leer(const char nombre[]){
	fstream f(nombre);
	istream& is=f;
	is >> this;
}
*/
//SOBRECARGA E/S

ostream& operator<<(ostream& os, Jugador &j){
	os << j.getNombre() << " " << j.getPuntuacion() << " " << j.getPartidasGanadas() << " " << j.getPartidasEmpatadas() << " " << j.getNInsertadas() << "\n";

	return os;
}

istream& operator>>(istream& is, Jugador &j){
	char n[100];
	int dato;
	
	is >> n;
	j.setNombre(n);
	is >> dato;
	j.setPuntuacion(dato);
	is >> dato;
	j.setPartidasGanadas(dato);
	is >> dato;
	j.setEmpatadas(dato);
	is >> dato;
	j.setNInsertadas(dato);
	
	return is;
}


