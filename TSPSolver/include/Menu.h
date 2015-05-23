#ifndef MENU_H
#define MENU_H

	# include <iostream>
	# include <string>
    # include <stdexcept>
	# include "TSPProblema.h"
	# include "TSPSolucion.h"
	# include "TSPMejorInsercion.h"
	# include "TSPGRASP.h"
	# include "TSPLocalSearch.h"
	# include "TSPILS.h"
	# include "TSPSA.h"
	# include "TSPVecinoMasCercano.h"
	# include "TSPRandom.h"
	# include "TSPGenetico.h"
	# include "TSPColeccionSoluciones.h"
	# include "TSPACO.h"
	# include "Cronometro.h"
	# include "TSPPlot.h"
	# include "ioTSP.h"
	# include "TSPBranchAndBound.h"
	# include "TSPBacktracking.h"

	using namespace std;
		
	/**
	* @brief Clase menú que contiene todos los métodos necesarios para controlar la interfaz del main así como las operaciones habilitadas en el mismo.
	*/
	

	class Menu{
	private:
		
		/**
		 * @brief Nivel del menú con el que se trabajará. Dependerá de las opciones escogidas.
		 */
		unsigned int nivel;

		/** 
		* @brief Puntero al objeto de la clase problema sobre el que se va a trabajar.
		*/
		TSPProblema *problema;
	
		/**
		* @brief Objeto para obtener soluciones mediante la heurística de la mejor inserción.
		*/		
		TSPMejorInsercion heuristica_insercion;

		/**
		* @brief Objeto para obtener soluciones mediante la heurística del vecino más cercano.
		*/		
	    TSPVecinoMasCercano heuristica_vecino;

	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística del GRASP.
	    */
	    TSPGRASP heuristica_grasp;

	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística Iterative Local Search.
	    */
	    TSPILS heuristica_ils;

	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística Simulated Annealing.
	    */
	    TSPSA simulated_annealing;

	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística Simulated Annealing.
	    */
	    TSPRandom generador_aleatorio;
	    
	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística Simulated Annealing.
	    */
	    TSPGenetico heuristica_genetico;
	    
	    /**
	    * @brief Objeto para mejorar soluciones localmente.
	    */
	    TSPLocalSearch mejora_local;

	    /**
	    * @brief Objeto para obtener soluciones mediante la heurística de la Optimización de la Colonia de Hormigas.
	    */
	    TSPACO heuristica_hormiga;
	
		/**
		* @brief Puntero a la última solución obtenida o a aquella que ha sido llamada desde Mis Soluciones.
		*/
	    TSPSolucion *solucion_actual;
		
		/**
		* @brief Objeto que guarda la lista con las soluciones obtenidas.
		*/
		TSPColeccionSoluciones soluciones;

		/**
		* @brief Objeto que permite la evaluación del tiempo que requieren los distintos algoritmos.
		*/
		Cronometro crono;

		/**
		* @brief Objeto cuya función es representar las distintas soluciones obtenidas.
		*/
		TSPPlot plotter;

		/**
		* @brief Objeto encargado de la representación y lectura de ficheros.
		*/
		IO_TSP iotsp;

		TSPBranchAndBound solucion_bb;

		TSPBacktracking solucion_back;

		/* MÉTODOS PRIVADOS */

		/**
		 * @brief Comprueba si un valor introducido como opción es un número.
		 * @param opcion Cadena que se desea comprobar si es numérica.
		 * @return Valor que corresponde a la cadena. Si la cadena no es válida, lanza excepción.
		 */
		double compruebaOpcion(string opcion);
		
		
	public:
		/**
		 * @brief Constructor de la clase. Inicializa nivel a un valor válido.
		 */
		Menu(TSPProblema *nuevo_problema);
		
		/**
		 * @brief Método que imprime las opciones del nivel del menú en el que se encuentra.
		 */
		void showOptions() const;
	
		/**
		 * @brief Método que lee una opción y realiza el trabajo correspondiente.
		 * @brief Llama a los métodos realizarOpcion.
		 * @return Valor de la opción introducida.
		 */
		int readOption();

		/**
		 * @brief Método que, dada una opción, realiza el trabajo correspondiente a la misma en el menú principal.
		 * @brief Llama a los diferentes algoritmos según la opción y se accede a los distintos menús.
		 * @param opcion Índice que le corresponde a la opción introducida.
		 */
		void realizarOpcionMenuPrincipal(int opcion);
		
		/**
		 * @brief Método que, dada una opción, realiza el trabajo correspondiente a la misma en el historial.
		 * @brief Llama a las diferentes operaciones de TSPColeccionSoluciones y se accede a los distintos menús.
		 * @param opcion Índice que le corresponde a la opción introducida.
		 */
		void realizarOpcionHistorial(int opcion);
		
		/**
		 * @brief Método que, dada una opción, realiza el trabajo correspondiente a la misma en el menú individual para una solución actual.
		 * @brief Llama a la mejora local o distintas operaciones según la opción y se accede a los distintos menús.
		 * @param opcion Índice que le corresponde a la opción introducida.
		 */
		void realizarOpcionMenuIndividual(int opcion);
		
		/**
		 * @brief Método que, dada una opción, realiza el trabajo correspondiente a la misma en el menú de ajuste de los parámetros de los algoritmos.
		 * @brief Se informa de los parámetros de los diferentes algoritmos según la opción 
		 * y se permite cambiarlos.
		 * @param opcion Índice que le corresponde a la opción introducida.
		 */
		void realizarOpcionMenuAjusteParametros(int opcion);
	
		/**
		 * @brief Imprime en consola una presentación rectangular.
		 * @param filas Filas que ocupa el rectángulo.
		 * @param columnas Columnas que ocupa el rectángulo.
		 * @param simbolo Carácter que rellena el rectángulo.
		 * @param mensaje Mensaje que se imprimirá en el centro del rectángulo.
		 */
		void presentacion(int filas,  int columnas, char simbolo, string mensaje = "") const;
	
		/**
		 * @brief Detiene el programa hasta que se pulse intro para que se pueda visualizar la información.
		 */
		void pause() const;
	};

#endif