#include "TSPPlot.h"

// Método privado que crea el fichero con las coordenadas ordenadas para el recorrido.
void TSPPlot::creaFicheroCoordenadas(TSPSolucion *solucion) const{
	ofstream fichero(nombre_archivo.c_str());

	int num_ciudades = problema->numeroCiudades();
	int ciudad_recorrido;
	double coordX, coordY;

	// El bucle realiza num_ciudades + 1 iteraciones para regresar a la ciudad inicial.
	for(int i = 0; i <= num_ciudades; i++){
		ciudad_recorrido = solucion->ciudadVisitada(i % num_ciudades);
		coordX = getCoordenadaX(ciudad_recorrido);
		coordY = getCoordenadaY(ciudad_recorrido);
		fichero << coordX << " " << coordY << "\n";
	}
}

// Método privado que devuelve la coordenada X de una ciudad.
double TSPPlot::getCoordenadaX(int indice_ciudad) const{
	return problema->ciudad(indice_ciudad).getX();
}

// Método privado que devuelve la coordenada Y de una ciudad.
double TSPPlot::getCoordenadaY(int indice_ciudad) const{
	return problema->ciudad(indice_ciudad).getY();
}

// Constructor de la clase.
TSPPlot::TSPPlot(TSPProblema *problema){
	this->problema = problema; // Asignación del problema
	// El fichero con el que se dibujará cambia la extensión .tsp por .sol
	string nombre_archivo = problema->nombreProblema();
	nombre_archivo.replace(nombre_archivo.size(),4, ".sol");
	// Se añade la dirección del directorio ./sol
	nombre_archivo = "./sol/" + nombre_archivo;
	this->nombre_archivo = nombre_archivo; // Asignación del nombre del archivo.
	cout << nombre_archivo << endl;
}

// Método encargado de llamar al programa que dibuja la solución.
void TSPPlot::plot(TSPSolucion *solucion) const{
	// Se crea el fichero con las coordenadas a partir del cual se realizará el dibujo.
	creaFicheroCoordenadas(solucion);
	// Nombre de la orden que se ha de ejecutar para llamar a GNUPlot.
	string nombre_orden = 
	"gnuplot --persist -e \"plot '" + nombre_archivo + "' with linespoints\" 2> /dev/null" + 
	" || gnuplot -persist -e \"plot '" + nombre_archivo + "' with linespoints\" 2> /dev/null" + 
	" || echo \"Error: No se ha podido dibujar la solución. Compruebe si tiene instalada la versión adecuada de gnuplot. Inténtelo (en Ubuntu) con 'sudo apt-get install gnuplot rlwrap', 'sudo apt-get install gnuplot-nox' o 'sudo apt-get install gnuplot'\"";
	// Se ejecuta la orden.
	system(nombre_orden.c_str());
}

