#ifndef IOTSP_H
#define IOTSP_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "TSPProblema.h"
#include "TSPSolucion.h"
#include "TSPColeccionSoluciones.h"

using namespace std;

class IO_TSP{

   /**
   * @brief Clase que proporciona distintos métodos para la lectura, escritura,
   * carga y guardado de las soluciones mediante ficheros.
   */
private:

   /* MÉTODOS PRIVADOS */

   /**
   * @brief Puntero al problema con el que se está trabajando.
   */
	TSPProblema *problema;

   /**
   * @brief Puntero a la colección con las soluciones almacenadas del problema.
   */
	TSPColeccionSoluciones *soluciones;

   /**
   * @brief Método privado que se encarga de leer una solución
   * y cargarla en la colección.
   * @brief El fichero de lectura está estandarizado y el método lee
   * siguiendo el modelo del fichero.
   * @param in Lector del fichero.
   */
	void leeSolucion(istream &in);

   /**
   * @brief Método privado que lee una lista de soluciones y las carga
   * en la colección. El fichero de lectura tiene que seguir un modelo concreto.
   * @param in Lector del fichero.
   */
	void leeListaSoluciones(istream &in);

   /**
   * @brief Método privado encargado de imprimir los datos de una solución.
   * @param solucion Puntero a la solución que se desea imprimir.
   * @param out Escritor del fichero.
   */
	void imprimeSolucion(TSPSolucion *solucion, ostream &out);

public:

   /**
   * @brief Constructor de la clase.
   * @param problema Puntero al problema con el que se desa trabajar.
   * @param soluciones Puntero a la colección donde se almacenan las soluciones.
   */
	IO_TSP(TSPProblema *problema, TSPColeccionSoluciones *soluciones);

   /**
   * @brief Método que genera el fichero de información para una solución.
   * @param solucion Puntero a la solución que se desea guardar.
   * @param file_name Cadena con el nombre que se desea asignar al archivo.
   */
	void print(TSPSolucion *solucion, string file_name);

   /**
   * @brief Método que genera un fichero con toda una lista de soluciones.
   * @param file_name Cadena con el nombre que se desea asignar al archivo.
   */
	void print_all(string file_name);

   /**
   * @brief Método encargado de cargar una o varias soluciones a partir de un fichero.
   * @brief Reconoce si el fichero es válido y si tiene una o varias soluciones y llama a los métodos privados correspondientes.
   * @param file_name Cadena con el nombre del fichero que se desea cargar.
   */
	void load(string file_name);

};


#endif