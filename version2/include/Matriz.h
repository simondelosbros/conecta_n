#ifndef MATRIZ_H
#define MATRIZ_H
#include <fstream>

class Matriz{
private:
	static const int MAX_FIL = 20;
	static const int MAX_COL = 20;
	int filas;
	int columnas;
	int *datos;
public:
	Matriz();

	Matriz(const Matriz &m);

	Matriz& operator=(const Matriz &m);
/*	
	std::ostream& operator<<(std::ostream& os, const Matriz &m);

	std::istream& operator>>(std::istream& is, Matriz &m);
*/
	~Matriz();

	int Columnas();

	int Filas();

	int getElemento(int i ,int j);

	void setFilas(int i);
	
	void setColumnas(int j);

	void setElemento(int i,int j,int ficha);

	void crear();

	void destruir();

	void init(int i, int j);

	friend std::ostream& operator<<(std::ostream& os, Matriz &m);

	friend std::istream& operator>>(std::istream& is, Matriz &m);
};


#endif
