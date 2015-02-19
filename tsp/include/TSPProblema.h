# ifndef TSPPROBLEMA_H
# define TSPPROBLEMA_H

    # include <fstream>
    # include <iostream>
    # include <stdlib.h>
    # include <string>
    # include <stdexcept>
    # include <sstream>
    # include "TSPPunto.h"
    
    using namespace std;
    
    /**
    * @brief Clase que representa el problema del Viajante de Comercio que se desea resolver.
    */

    class TSPProblema{
        private:       
                                /* DATOS MIEMBRO */
            /**
            * @brief Número de ciudades con las que se trabaja.
            * @brief Se inicializa mediante el método privado leerDatosArchivo().
            */
            int num_ciudades;
            
            /**
            * @brief Puntero que contiene la dirección de memoria de un array con las coordenadas (puntos) de las ciudades.
            * @brief Se inicializa el puntero mediante el método privado reservarEspacio().
            * Se inicializan las componentes mediante el método privado leerDatosArchivo(). 
            */
            TSPPunto *ciudades;
            
            /**
            * @brief Dato miembro que apunta a un array de punteros que apuntarán a su vez a un array con las distancias entre su ciudad correspondiente y las demás ciudades.
            * @brief Se inicializa el puntero, creándose los arrays, mediante el método privado reservarEspacio().
            * Se inicializan las componentes mediante el método privado leerDatosArchivo().
            */
            double **matriz_distancias;
            
            /**
            * @brief Dato miembro que contiene el nombre del archivo del cual se leerán los datos.
            * @brief Se inicializa en el constructor. (Se pasa como parámetro su valor).
            */
            string nombre_archivo;
        
        
                                        /* MÉTODOS PRIVADOS */
            /**
            * @brief Método privado que lee los datos del archivo indicado en nombre_archivo.
            * @brief Mediante la lectura de datos inicializa num_ciudades
            * Posteriormente llama al método privado reservarEspacio().
            * Lee del archivo las coordenadas de las ciudades.
            */
            void leerDatosArchivo();
        
            /**
            * @brief Método privado que reserva el espacio en memoria para ciertos datos miembro. 
            * @brief Crea el array de puntos para las ciudades y los arrays que requiere matriz_distancias.
            */
            void reservarEspacio();
            
            /**
            * @brief Método privado que calcula la matriz de distancias.
            */
            void calcularMatrizDistancias();
        
        
        public:
                                /* MÉTODOS PÚBLICOS */  
            /**
            * @brief Constructor de la clase.
            * @brief En él se llaman a los métodos privados leerDatosArchivo() y calcularMatrizDistancias.
            * @param nombre_archivo Cadena de caracteres con el nombre del archivo del cual se leerá el problema.
            */
            TSPProblema(string nombre_archivo);
            
            /**
            * @brief Destructor de la clase.
            * @brief En él se destruyen ciudades y matriz_distancias, además de las funciones usuales.
            */
            ~TSPProblema();

            /**
            * @brief Constructor de copia de la clase.
            * @param otro Objeto de la clase problema que se ddesea copiar.
            */
            TSPProblema(const TSPProblema &otro);

            /**
            * @brief Método público que devuelve el número de ciudades del problema.
            * @return num_ciudades
            */
            inline int numeroCiudades() const{
                return this->num_ciudades;
            }
        
            /**
            * @brief Método que devuelve el elemento (i,j) de la matriz de distancias.
            * @param (i,j) Índices del elemento de la matriz que se desea.
            * @return Elemento (i,j) de la matriz.
            */
            inline double elementoMatrizDistancias(int i, int j) const{
                return matriz_distancias[i][j];
            }

            /**
            * @brief Permite obtener el nombre del fichero del problema con el que se trabaja.
            * @return Cadena con el nombre del problema.
            */
            inline string nombreProblema() const{
                return this->nombre_archivo;
            }

            /**
             * @brief Permite obtener las coordenadas de una ciudad del problema.
             * @param indice Posición de la ciudad que se quiere obtener.
             * @return Punto con las coordenadas de la ciudad elegida.
             */
            TSPPunto ciudad(int indice) const;
    };

#endif