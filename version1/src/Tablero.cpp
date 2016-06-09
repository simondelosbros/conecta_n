#include <iostream>
#include <stdlib.h> //Para system("clear");
#include "Tablero.h"
#include "Matriz.h"

using namespace std;

Tablero::Tablero(int nfichas, int fil, int col){
	filas = fil;
	columnas = col;
	partida_finalizada = false;
	fichas_objetivo=nfichas;

	tablero.init(fil,col);

	turno_actual=1;
}

int Tablero::getFilas(){
	return tablero.Filas();
}

int Tablero::getColumnas(){
	return tablero.Columnas();
}

int Tablero::getFichasObjetivo(){
	return fichas_objetivo;
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

void Tablero::CompruebaPartida(int p){
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

void Tablero::setTurnoActual(){
	if(turno_actual==1){
		turno_actual++;
	}else{
		turno_actual--;
	}
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

void Tablero::VaciaTablero(){
	const int FICHA=0;
	for(int i=0; i<getFilas(); i++)
		for(int j=0; j<getColumnas(); j++)
			tablero.setElemento(i,j,FICHA);
	partida_finalizada = false;
}

void Tablero::prettyPrint(){
	char letra='a';

	for(int i=-1; i<=getFilas(); i++){
		cout <<"\n";
		if(i!=-1 && i!=getFilas())
			cout << "|";
		if(i==getFilas())
			cout << "=";
		for(int j=0; j<getColumnas(); j++){
			if(i==-1){
				cout << " " <<letra;
				letra++;
			}else if (i==getFilas()){
				cout << "==";
			}else{
				if(getDato(i,j)==0)
					cout << " ";
				if(getDato(i,j)==1)
					cout << "x";
				if(getDato(i,j)==2)
					cout << "o";
				cout <<"|";
			}
		}
	}
	cout << "\n";
}

