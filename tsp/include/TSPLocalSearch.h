# ifndef TSPLOCALSEARCH_H
# define TSPLOCALSEARCH_H

    # include "TSPSolucion.h"
    # include "TSPProblema.h"

    /**
    * @brief Clase que contiene los métodos necesarios para mejorar una solución del probema del Viajante de Comercio 
    * mediante el algoritmo 2-OPT.
    */

    class TSPLocalSearch{
        private:
                        /* DATOS MIEMBRO */
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

            /**
            * @brief Cadena de caracteres con el nombre de la mejora local.
            * @brief Se inicializa en el constructor de la clase.
            * Al crear una solución con TSPLocalSearch su dato miembro const string *mejora apuntará a nombre_mejora. 
            */
            const string nombre_mejora;
        
        public:

                        /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa nombre_mejora y problema.
            * @param nuevo_problema Puntero a un objeto de la clase TSPProblema.
            */
            TSPLocalSearch(TSPProblema *nuevo_problema);

            /**
            * @brief Método que mejora una solución dada.
            * @brief Utiliza el método determinarMejorIntercambio de la clase TSPSolucion.
            * @param solucion Puntero a un objeto de la clase TSPSolucion que se desea mejorar.
            */
            void mejorarSolucionMejorIntercambio(TSPSolucion *solucion) const;
            
            /**
            * @brief Método que mejora una solución dada.
            * @brief Utiliza el método determinarMejorIntercambio de la clase TSPSolucion.
            * @param solucion Puntero a un objeto de la clase TSPSolucion que se desea mejorar.
            */
            void mejorarSolucionPrimerIntercambio(TSPSolucion *solucion) const;

            /**
            * @brief Método, que dada una solución, devuelve una mejora de la misma.
            * @param solucion Puntero a un objeto de la clase TSPSolucion que se desea mejorar.
            * @return Puntero a la nueva solución mejorada.
            */
            TSPSolucion *obtenerSolucionMejorada(TSPSolucion *solucion);
};

#endif