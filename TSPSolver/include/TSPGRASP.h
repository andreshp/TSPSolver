# ifndef TSPGRASP_H
# define TSPGRASP_H

    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    # include "TSPLocalSearch.h"
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular solución al probema del Viajante de Comercio 
    * mediante el algoritmo heurístico GRASP (Greedy Randomized Adaptative Search Process).
    */

    class TSPGRASP{
        private:
                        /* DATOS MIEMBRO */
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

            /**
            * @brief Puntero a un objeto de la clase TSPLocalSearch para mejorar las soluciones.
            * @brief Se inicializa en el constructor de la clase.
            */
            TSPLocalSearch *mejora_local;

            /**
            * @brief Variable double que contendrá un valor mayor que 1 utilizado para crear la lista de candidatos RLC.
            * @brief Una ciudad entra en la lista de candidatos si su distancia a la ciudad referente es menor que 
            * indice_validez * mejor distancia actual. Esto permite elegir una ciudad aleatoria solo cuando hay varias ciudades cuyas
            * distancias a la ciudad referente están en un intervalo aceptable.
            */
            double indice_validez;

            /**
            * @brief Cadena de caracteres con el nombre del algoritmo.
            * @brief Se inicializa en el constructor de la clase.
            * Al crear una solución con TSPGRASP su dato miembro algoritmo apunta a esta string.
            */
            string nombre_algoritmo;
            
            
        public:

                        /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa nombre_mejora y problema.
            * @param nuevo_problema Puntero a un objeto de la clase TSPProblema.
            */
            TSPGRASP(TSPProblema *nuevo_problema, TSPLocalSearch *mejora_local);
            
            /**
            * @brief Constructor de copia de la clase.
            * @param otro Objeto de la clase TSPGRASP que se desea copiar.
            */
            TSPGRASP(const TSPGRASP & otro);
            
            /**
            * @brief Método que crea una solución mediante el algoritmo GRASP.
            * @brief Utiliza el método determinarVecinoGRASP de TSPSolucion.
            * @return Puntero a la solución generada.
            */
            TSPSolucion *buscarSolucion() const;
            
            /**
            * @brief Método que crea una solución mediante el algoritmo GRASP.
            * @brief Utiliza el método determinarVecinoGRASP de TSPSolucion. Además, le aplica Local Search a la solución.
            * @return Puntero a la solución generada.
            */
            TSPSolucion *buscarSolucionLocalSearch() const;


            /**
            * @brief Método que cambia el índice de validez utilizado en el algoritmo GRASP.
            * @param nuevo_indice Variable real con el nuevo índice. Se comprueba si es mayor o igual que 1.
            */
            void setIndiceValidez(double nuevo_indice);

            /**
            * @brief Método que devuelve el índice de validez utilizado en el algoritmo GRASP.
            */
            inline double getIndiceValidez(){
                return indice_validez;
            }
        };

#endif