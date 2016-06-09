#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Tablero.h"
#include "Matriz.h"

using namespace std;

Tablero::Tablero(){ //Constructor por defecto;
	fichas_objetivo=0;
	fichas_por_turno=0;
	filas=0;
	columnas=0;
	partida_finalizada=false;
	tablero.init(filas,columnas);
	turno_actual=1;
	quien_empezo=1;
}

Tablero::Tablero(int nfichas, int por_turno, int fil, int col){

	filas = fil;
	columnas = col;
	partida_finalizada = false;
	fichas_por_turno=por_turno;
	fichas_objetivo=nfichas;

	tablero.init(fil,col);

	turno_actual=1;
	
	quien_empezo=1;
}

int Tablero::getFilas(){
	return filas;
}

int Tablero::getColumnas(){
	return columnas;
}

int Tablero::getFichasObjetivo(){
	return fichas_objetivo;
}

int Tablero::getFichasPorTurno(){
	return fichas_por_turno;
}

int Tablero::getDato(int i, int j){
	return tablero.getElemento(i,j);
}

bool Tablero::getPartidaFinalizada(){
	return partida_finalizada;
}

int Tablero::getTurnoActual(){
	return turno_actual;
}

Matriz Tablero::getMatriz(){
	return tablero;
}

int Tablero::getQuienEmpezo(){
	return quien_empezo;
}

//Operaciones modifican
void Tablero::InsertaFicha(int columna){
	bool insertada=false;

	for(int i=getFilas()-1; i>=0 && insertada==false; i--){
		if(tablero.getElemento(i, columna)==0){
			tablero.setElemento(i, columna, turno_actual);
			insertada=true;
		}
	}
}

void Tablero::CompruebaPartida(int p ){
	int comprueba1=CalculaColumnas(p),comprueba2=CalculaFilas(p),comprueba3=CalculaDiagonalIzq(p),comprueba4=CalculaDiagonalDrcha(p);
    
	if(comprueba1 >= fichas_objetivo){
		partida_finalizada = true;
	}
	if(comprueba2 >= fichas_objetivo){
		partida_finalizada = true;
	}
	if(comprueba3 >= fichas_objetivo){
		partida_finalizada = true;
	}
	if(comprueba4 >= fichas_objetivo){
		partida_finalizada = true;
	}
	if(CalculaEmpate()){
		partida_finalizada = true;
	}


}
bool Tablero::CalculaEmpate(){
	bool result = false;
	int numero_de_vacias=0;
	for (int i = 0; i<tablero.Columnas();i++){
		if (getDato(0,i) == 0){
			numero_de_vacias++;
		}
	}
	if (numero_de_vacias == 0){
		result = true;
	}
	return result;
}

int Tablero::CalculaColumnas(int p){
	//cout << "Miro las fichas " << p << endl;
	int encadenadas = 0;
	int maximo_encontrado = 0;
	//int columnas = tablero.Columnas();
	//cout << "numero columnas: " << columnas << endl; 
	for (int i = 0 ; i < tablero.Columnas() ; i++){
		encadenadas = 0;
		for (int j = tablero.Filas()-1 ; j>=0 &&  (encadenadas >= (fichas_objetivo-j-1)); j--){
			//cout << "Bucle: " << j << " es mayor que 0, " << encadenadas << " es mayor o igual que " << fichas_objetivo-j-1 <<" por lo tanto entro."<< endl; 

			//cout << "Miro la posicion " << j << " " << i << " , en esta posicion hay un " << getDato(j,i)<< endl;
			if(getDato(j,i) == p){
				encadenadas++;
				//cout << "He encontrado una ficha " << endl;
				if(encadenadas > maximo_encontrado){
					maximo_encontrado = encadenadas;
					//cout << "Mi maximo por ahora es:  " << maximo_encontrado << endl;
				}
			}
			else{
				encadenadas = 0;
			}
		}
	}
return maximo_encontrado;
}

int Tablero::CalculaFilas(int p){

	int encadenadas = 0;
	int maximo_encontrado = 0;
	//int filas = tablero.Filas();
	//cout << "numero filas: " << filas << endl; 
	for(int i = tablero.Filas()-1;i>0;i--){
		encadenadas = 0;
		for(int j = 0; j< tablero.Columnas() && (encadenadas >= (fichas_objetivo-tablero.Columnas()+j)) ; j++){
			//cout << "Bucle: " << j << " es menor que: "<< tablero.Columnas()<< " y " << encadenadas << " es mayor o igual que " << fichas_objetivo-tablero.Columnas()+j <<" por lo tanto entro."<< endl; 
			//cout << "Miro la posicion " << i << " " << j << " , en esta posicion hay un " << getDato(i,j)<< endl;
			if(getDato(i,j) == p){
				encadenadas++;
				//cout << "He encontrado una ficha " << endl;
				if(encadenadas > maximo_encontrado){
				maximo_encontrado = encadenadas;
				//cout << "Mi maximo por ahora es:  " << maximo_encontrado << endl;
				}
			}
			else{
				encadenadas = 0;
			}
		}
	}
return maximo_encontrado;
}


int Tablero::CalculaDiagonalIzq(int p){
	int encadenadas = 0;
	int maximo_encontrado = 0;
	//cout << "Comprobamos diagonal izq :" << endl;
	for(int i  = fichas_objetivo-1; i<=tablero.Filas()-1;i++){
		int rotasion_loco = i;
		encadenadas = 0;
		//cout << "Empiezo en la diagonal: " << fichas_objetivo-1<< endl;
		for(int j = 0 ; j<tablero.Columnas() && rotasion_loco >= 0;j++){
			//cout << "Bucle: " << j << " es menor que: "<< tablero.Columnas()<< " y " << rotasion_loco << " es mayor o igual que  0" <<" por lo tanto entro."<< endl; 
			//cout << "Miro la posicion " << rotasion_loco << " " << j << " , en esta posicion hay un " << getDato(rotasion_loco,j)<< endl;
			if(getDato(rotasion_loco,j) == p){
				encadenadas++;
				//cout << "He encontrado una ficha " << endl;
				if(encadenadas > maximo_encontrado){
				maximo_encontrado = encadenadas;
				//cout << "Mi maximo por ahora es:  " << maximo_encontrado << endl;
				}
			}
			else{
				encadenadas = 0;
			}
			rotasion_loco--;

		}

	}

	for(int i = tablero.Columnas() - fichas_objetivo; i>0; i--){
		int rotasion_loco = i;
		encadenadas = 0;
		for(int j = tablero.Filas()-1 ;j>=0 && rotasion_loco < tablero.Columnas() ;j-- ){
			if(getDato(j,rotasion_loco) == p){
				encadenadas++;
				if(encadenadas > maximo_encontrado){
				maximo_encontrado = encadenadas;
				}
			}
			else{
				encadenadas = 0;
			}
			rotasion_loco++;

		}
	}
return maximo_encontrado;

}


int Tablero::CalculaDiagonalDrcha(int p){
	int encadenadas = 0;
	int maximo_encontrado = 0;
	//cout << "Comprobamos diagonal drcha :" << endl;
	for(int i = fichas_objetivo-1;i<=tablero.Columnas()-1;i++){
		int rotasion_loco = i;
		//cout << "Empiezo en la diagonal: " << i<< endl;
		encadenadas = 0;
		for(int j = tablero.Filas()-1;rotasion_loco >= 0 && j >= 0;j--){
			//cout << "Bucle: " << rotasion_loco << " es mayor o igual que: 0  y " << j << " es mayor o igual que  0" <<" por lo tanto entro."<< endl; 
			//cout << "Miro la posicion " << j << " " << rotasion_loco << " , en esta posicion hay un " << getDato(j,rotasion_loco)<< endl;

			if(getDato(j,rotasion_loco) == p){
				encadenadas++;
				//cout << "He encontrado una ficha " << endl;
				if(encadenadas > maximo_encontrado){
					maximo_encontrado = encadenadas;
					//cout << "Mi maximo por ahora es:  " << maximo_encontrado << endl;

				}
			}
			else{
				encadenadas = 0;
			}
			rotasion_loco--;
		}
	}

	for(int i = fichas_objetivo-1; i<tablero.Filas()-1;i++){
		int rotasion_loco = i;
		//cout << "Empiezo en la diagonal: " << i<< endl;
		encadenadas = 0;
		for(int j = tablero.Columnas()-1;rotasion_loco >= 0 && j >= 0;j--){
			//cout << "Bucle: " << rotasion_loco << " es mayor o igual que: 0  y " << j << " es mayor o igual que  0" <<" por lo tanto entro."<< endl; 
			//cout << "Miro la posicion " << rotasion_loco << " " << j << " , en esta posicion hay un " << getDato(rotasion_loco,j)<< endl;

			if(getDato(rotasion_loco,j) == p){
				encadenadas++;
				//cout << "He encontrado una ficha " << endl;

				if(encadenadas > maximo_encontrado){
					maximo_encontrado = encadenadas;
					//cout << "Mi maximo por ahora es:  " << maximo_encontrado << endl;

				}
			}
			else{
				encadenadas = 0;
			}
			rotasion_loco--;
		}
	}

return maximo_encontrado;

}

void Tablero::setTurnoActual(){
	if(turno_actual==1){
		turno_actual++;
	}else{
		turno_actual--;
	}
}

void Tablero::VaciaTablero(){
	const int FICHA=0;
	for(int i=0; i<getFilas(); i++)
		for(int j=0; j<getColumnas(); j++)
			tablero.setElemento(i,j,FICHA);
	partida_finalizada = false;
	
	if(quien_empezo==1)
		turno_actual=2;
	else
		turno_actual=1;
	
	quien_empezo=turno_actual;
	
}

void Tablero::prettyPrint(ostream &out /*=cout*/){
	char letra='a';

	for(int i=-1; i<=getFilas(); i++){
		out <<"\n";
		if(i!=-1 && i!=getFilas())
			out << "|";
		if(i==getFilas())
			out << "=";
		for(int j=0; j<getColumnas(); j++){
			if(i==-1){
				out << " " <<letra;
				letra++;
			}else if (i==getFilas()){
				out << "==";
			}else{
				if(getDato(i,j)==0)
					out << " ";
				if(getDato(i,j)==1)
					out << "x";
				if(getDato(i,j)==2)
					out << "o";
				out <<"|";
			}
		}
	}
	out << "\n";
}

//OPERACIONES SET
void Tablero::setFil(int i){
	filas=i;
}

void Tablero::setCol(int j){
	columnas=j;
}

void Tablero::setFichas(int f){
	fichas_objetivo=f;
}

void Tablero::setFichasPorTurno(int i){
	fichas_por_turno=i;
}

void Tablero::setMatriz(Matriz m){
	tablero=m;
}

void Tablero::setPartidaFinalizada(bool b){
	partida_finalizada=b;
}

void Tablero::setTurno(int i){
	turno_actual=i;
}

void Tablero::setQuienEmpezo(int i){
	quien_empezo=i;
}

//SOBRECARGA DE OPERADORES
//TABLERO
ostream& operator<<(ostream& os, Tablero &t){
	int fil=t.getFilas();
	int col=t.getColumnas();
	Matriz m=t.getMatriz();

	os << fil << " " << col << "\n";
	os << t.getFichasObjetivo() << " " << t.getFichasPorTurno() << "\n";
	os << m << "\n";
	os << t.getPartidaFinalizada() << " " << t.getTurnoActual() << " " << t.getQuienEmpezo();

	return os;
}

istream& operator>>(istream& is, Tablero& t){
	int dato;
	Matriz m;
	bool b;

	is >> dato;
	t.setFil(dato);
	is >> dato;
	t.setCol(dato);
	is >> dato;
	t.setFichas(dato);
	is >> dato;
	t.setFichasPorTurno(dato);
	is >> m;
	t.setMatriz(m);
	is >> b;
	t.setPartidaFinalizada(b);
	is >> dato;
	t.setTurno(dato);
	is >> dato;
	t.setQuienEmpezo(dato);

	return is;
}

