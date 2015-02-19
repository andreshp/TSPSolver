# ifndef TSPRANDOM_H
# define TSPRANDOM_H

    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular solución aleatoria al probema del Viajante de Comercio.
    */

    class TSPRandom{
        private:
                        /* DATOS MIEMBRO */
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

            /**
            * @brief Cadena de caracteres con el nombre del algoritmo.
            * @brief Se inicializa en el constructor de la clase.
            * Al crear una solución con TSPRandom su dato miembro algoritmo apunta a esta string.
            */
            const string nombre_algoritmo;
            
            
        public:

                        /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa nombre_mejora y problema.
            * @param nuevo_xproblema Puntero a un objeto de la clase TSPProblema.
            */
            TSPRandom(TSPProblema *nuevo_problema);

            /**
            * @brief Método que crea una solución mediante el algoritmo Random.
            * @brief Utiliza el método determinarVecinoRandom de TSPSolucion.
            * @return Puntero a la solución generada.
            */
            TSPSolucion *solucionAleatoria();
        };

#endif