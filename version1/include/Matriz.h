#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz{
private:
	static const int MAX_FIL = 20;
	static const int MAX_COL = 20;
	int filas;
	int columnas;
	int datos[MAX_FIL][MAX_COL];
public:
	Matriz();

	int Columnas();

	int Filas();

	int getElemento(int i ,int j);

	void setFilas(int i);
	
	void setColumnas(int j);

	void setElemento(int i,int j,int ficha);

	void init(int i, int j);
};


#endif
