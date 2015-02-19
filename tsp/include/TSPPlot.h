#ifndef TSPPLOT_H
#define TSPPLOT_H

# include <fstream>
# include <iostream>
# include <string>
# include <stdlib.h>

# include "TSPPunto.h" 
# include "TSPProblema.h"
# include "TSPSolucion.h"

using namespace std;

/**
* @brief Clase que proporciona funcionalidades para representar los recorridos obtenidos como solución del TSP.
* @brief Requiere el uso del programa externo GNUPlot.
*/

class TSPPlot{

private:
	/* DATOS MIEMBRO */

	/**
	 * @brief Puntero al objeto de la clase TSPProblema con el que se está trabajando.
	 */
	TSPProblema *problema;

	/**
	 * @brief Cadena de caracteres con el nombre que se asignará al archivo con los datos para la representación.
	 */
	string nombre_archivo;

	/* MÉTODOS PRIVADOS */
	/**
	 * @brief Genera un archivo donde se guardan las coordenadas de las ciudades ordenadas según
	 * el recorrido de la solución.
	 * @param solucion Puntero a la solución que se desea representar.
	 */ 
	void creaFicheroCoordenadas(TSPSolucion *solucion) const;

	/**
	 * @brief Obtiene la coordenada X de la ciudad dada por el índice.
	 * @param indice_ciudad Índice de la ciudad deseada.
	 * @return Coordenada X de la ciudad.
	 */
	double getCoordenadaX(int indice_ciudad) const;

	/**
	 * @brief Obtiene la coordenada Y de la ciudad dada por el índice.
	 * @param indice_ciudad Índice de la ciudad deseada.
	 * @return Coordenada Y de la ciudad.
	 */
	double getCoordenadaY(int indice_ciudad) const;

public:
	/**
	 * @brief Constructor de la clase.
	 * @brief Recibe los datos del problema para poder dibujar posteriormente los recorridos.
	 * @param problema Puntero al problema con el que se está trabajando.
	 */
	TSPPlot(TSPProblema *problema);

	/* MÉTODO PÚBLICO */

	/**
	 * @brief Método principal de la clase.
	 * @brief Genera el fichero con las coordenadas para después realizar el dibujo con la llamada a GNUPLot.
	 * @param solucion Puntero a la solución que se desea dibujar.
	 */
	void plot(TSPSolucion *solucion) const;

};

#endif