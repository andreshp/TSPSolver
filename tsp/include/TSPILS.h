# ifndef TSPILS_H
# define TSPILS_H
    
    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    # include "TSPLocalSearch.h"
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular solución al probema del Viajante de Comercio 
    * mediante el algoritmo heurístico ILS (Iterative Local Search).
    */

    class TSPILS{
        private:
                        /* DATOS MIEMBRO */
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

            /**
            * @brief Puntero a la mejor solución obtenida.
            * @brief Se inicializa en buscarSolucion.
            */
            TSPSolucion *mejor_solucion;

            /**
            * @brief Puntero a un objeto de la clase TSPLocalSearch para mejorar las soluciones.
            * @brief Se inicializa en el constructor de la clase.
            */
            TSPLocalSearch *mejora_local;

            /**
            * @brief Cadena de caracteres con el nombre del algoritmo.
            * @brief Se inicializa en el constructor de la clase.
            * Al crear una solución con TSPGRASP su dato miembro algoritmo apunta a esta string.
            */
            const string nombre_algoritmo;            
            
        public:

                        /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa nombre_algoritmo, problema y mejora_local.
            * @param nuevo_problema Puntero a un objeto de la clase TSPProblema.
            * @param mejora_local Puntero a un objeto de la clase TSPLocalSearch.
            */
            TSPILS(TSPProblema *nuevo_problema, TSPLocalSearch *mejora_local);

            /**
            * @brief Método que dada una solución, aplica ILS para encontrar una solución mejor a la dada.
            * @brief Utiliza 2-OPT y el método mutacion de la clase TSPSolucion.
            * @param solucion Puntero a un objeto de la clase TSPSolucion a la que se le aplicará ILS.
            * @param iteraciones Número de veces que se aplicará el proceso. 
            */
            void buscarSolucion(TSPSolucion *solucion, int iteraciones);

            /**
            * @brief Método que dada una solución, aplica ILS devolviendo una solución mejor.
            * @param solucion Puntero a un objeto de la clase TSPSolucion a la que se le aplicará ILS.
            * @param iteraciones Número de veces que se aplicará el proceso.
            * @return Solución obtenida. 
            */
            TSPSolucion *obtenerSolucion(TSPSolucion *solucion, int iteraciones);
    };

#endif