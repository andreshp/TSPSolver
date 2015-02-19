#include "ioTSP.h"

//Lector de una solución.
void IO_TSP::leeSolucion(istream &in){
	string cabeceras, *algoritmo = new string, mejora;
	int *recorrido = new int[problema->numeroCiudades()];
	bool intercambio;

	in >> cabeceras; //cabecera RECORRIDO
	for(int i = 0; i < problema->numeroCiudades(); i++){
		in >> recorrido[i];
	}

	in >> cabeceras; //cabecera COSTE
	in >> cabeceras; //valor del coste. No se usa porque TSPSolucion se encarga de calcularlo.
	in >> cabeceras; //cabecera ALGORITMO
	getline(in,*algoritmo); //lectura de algoritmo
	in >> cabeceras; //cabecera MEJORA
	getline(in,mejora); //lectura de la mejora
	in >> cabeceras; //cabecera INTERCAMBIO
	in >> intercambio; //lectura del intercambio;

	TSPSolucion *solucion = new TSPSolucion(problema,recorrido,algoritmo,mejora,intercambio);
	soluciones->pushSolucion(solucion);
}

//Lector de lista de soluciones.
void IO_TSP::leeListaSoluciones(istream &in){
	string cabeceras;
	int num_soluciones;

	in >> cabeceras; //cabecera [
	in >> num_soluciones; //lectura de las soluciones a añadir.
	in >> cabeceras; //cabecera ]

	for(int i = 0; i < num_soluciones; i++){
		in >> cabeceras; //cabecera SOLUCION
		in >> cabeceras; //cabecera número de la solucion
		leeSolucion(in);

	}

}

//Escritura de una solución.
void IO_TSP::imprimeSolucion(TSPSolucion *solucion, ostream &out){
	out << "RECORRIDO: " << endl;

	for(int i = 0; i < problema->numeroCiudades(); i++){
		out << solucion->ciudadVisitada(i) << " ";
	}

	out << endl;

	out << "COSTE: " << solucion->distanciaTotal() << endl;
	out << "ALGORITMO: " << solucion->getAlgoritmo() << endl;
	out << "MEJORA: " << solucion->getMejora() << endl;
	out << "INTERCAMBIO: " << solucion->getIntercambioCiudades() << endl;
}

//Constructor de la clase.
IO_TSP::IO_TSP(TSPProblema *problema, TSPColeccionSoluciones *soluciones){
	this->problema = problema;
	this->soluciones = soluciones;
}

//Creación de un fichero para su posterior escritura de la solución.
void IO_TSP::print(TSPSolucion *solucion, string file_name){
	ofstream out(file_name.c_str());
	if(!out){
		throw logic_error("No es posible crear el fichero en el lugar indicado.");
	}
	out << "SOLUCION AL PROBLEMA: " << problema->nombreProblema() << endl;
		
	imprimeSolucion(solucion,out);
}

//Creación de un fichero para imprimir ahí una lista de soluciones.
void IO_TSP::print_all(string file_name){
	ofstream out(file_name.c_str());
	if(!out){
		throw logic_error("No es posible crear el fichero en el lugar indicado.");
	}

	int size = soluciones->numeroSoluciones();

	out << "SOLUCIONES AL PROBLEMA: " << problema->nombreProblema() << " [ " << size << " ] " << endl;

	for(int i = 1; i <= size; i++){
		out << "SOLUCION " << i << ":\n";
		imprimeSolucion(soluciones->solucionPosicion(i),out);
		out << endl;
	}
}	

//Acceso a un fichero para la lectura de las soluciones:
void IO_TSP::load(string file_name){
	ifstream in(file_name.c_str());
	if(!in){
		throw logic_error("No existe el archivo o directorio.");
	}
	string cabecera, adicional, nombre_problema; //Lectura del título del archivo.
	in >> cabecera;
	in >> adicional;
	in >> adicional;
	in >> nombre_problema;

	if(nombre_problema != problema->nombreProblema()){
		throw logic_error("El fichero no corresponde al problema con el que se trabaja.");
	}

	if(cabecera == "SOLUCION"){	//Se lee solución única.
		leeSolucion(in);
	}
	else if(cabecera == "SOLUCIONES"){	//Se lee la lista de soluciones.
		leeListaSoluciones(in);
	}
	else{
		throw logic_error("El archivo está corrupto.");
	}
	soluciones->ordena();
}