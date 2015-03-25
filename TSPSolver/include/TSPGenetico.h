# ifndef TSPGENETICO_H
# define TSPGENETICO_H

    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    # include "TSPColeccionSoluciones.h"
    # include "TSPRandom.h"
    # include "TSPGRASP.h"
    # include "TSPLocalSearch.h"
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular solución al probema del Viajante de Comercio 
    * mediante un algoritmo genético adaptado al problema.
    */

    class TSPGenetico{
        private:
                        /* DATOS MIEMBRO */
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

            /**
            * @brief Puntero a un objeto de la clase TSPColeccionSoluciones que reppresentará nuestra población.
            * @brief Se inicializa en el constructor.
            */
            TSPColeccionSoluciones *poblacion;

            /**
            * @brief Puntero a un objeto de la clase TSPRandom que inicializará aleatoriamente los individuos.
            * @brief Se inicializa en el constructor.
            */
            TSPRandom *generador_aleatorio;

            /**
            * @brief Puntero a un objeto de la clase TSPGRASP que se utilizará en la clase TSPColeccioSoluciones (objeto poblacion).
            * @brief Se inicializa en el constructor.
            */
            TSPGRASP *heuristica_grasp;

            /**
            * @brief Puntero a un objeto de la clase TSPLocalSearch que se utilizará para mejorar soluciones.
            * @brief Se inicializa en el constructor.
            */
            TSPLocalSearch *mejora_local;

            /**
            * @brief Número de inviduos de la población.
            * @brief Se inicializa en el constructor. Hay un método set para modificarlo y otro get para obtenerlo.
            */
            int numero_individuos;

            /**
            * @brief Probabilidad de que dos soluciones se crucen.
            * @brief Se inicializa en el constructor. Hay un método set para modificarlo y otro get para obtenerlo.
            */
            double probabilidad_cruce; 

            /**
            * @brief Probabilidad de que haya una mutación en una nueva solución.
            * @brief Se inicializa en el constructor. Hay un método set para modificarlo y otro get para obtenerlo.
            */
            double probabilidad_mutacion;
            
            /**
            * @brief Número de candidatos en la selección por torneo.
            * @brief Se inicializa en el constructor. Hay un método set para modificarlo y otro get para obtenerlo.
            */
            int num_candidatos;
            
            /**
            * @brief Cadena de caracteres con el nombre del algoritmo.
            * @brief Se inicializa en el constructor de la clase.
            * Al crear una solución con TSPGenetico su dato miembro algoritmo apunta a esta string.
            */
            const string nombre_algoritmo;
            
            
        public:

                        /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa nombre_mejora y problema.
            * @param nuevo_problema Puntero a un objeto de la clase TSPProblema.
            */
            TSPGenetico(TSPProblema *nuevo_problema, TSPRandom *generador_aleatorio, TSPGRASP *heuristica_grasp, TSPLocalSearch *mejora_local);

            /**
            * @brief Método que crea una solución mediante el algoritmo Genetico.
            * @brief Utiliza el método determinarVecinoGRASP de TSPSolucion.
            * @return Puntero a la solución generada.
            */
            TSPSolucion *buscarSolucion(int num_generaciones);

            /**
            * @brief Método que crea una solución mediante el algoritmo Genetico.
            * @brief Utiliza el método determinarVecinoGRASP de TSPSolucion.
            * @return Puntero a la solución generada.
            */
            TSPSolucion *buscarSolucionSnug(int num_generaciones);
            
            /**
            * @brief Método que cambia la probabilidad de reproducción utilizada en el algoritmo genético.
            * @param nueva_probabilidad Variable real con la nueva probabilidad de reproducción. Se comprueba si es mayor o igual que 0 (mayor que 1 se considera 1).
            */
            void setProbabilidadCruce(double nueva_probabilidad);

            /**
            * @brief Método que cambia la probabilidad de reproducción utilizada en el algoritmo genético.
            * @param nueva_probabilidad Variable real con la nueva probabilidad de mutación. Se comprueba si es mayor o igual que 0 (mayor que 1 se considera 1).
            */
            void setProbabilidadMutacion(double nueva_probabilidad);
        
            /**
            * @brief Método que cambia el número de individuos de la población.
            * @param numero_individuos Variable real el nuevo número de individuos de la poblacion. Se comprueba si es mayor que 0.
            */
            void setNumeroIndividuos(double numero_individuos);

            /**
            * @brief Método que devuelve la probabilidad de cruce utilizada en el algoritmo.
            */
            inline double getProbabilidadCruce(){
                return probabilidad_cruce;
            }

            /**
            * @brief Método que devuelve la probabilidad de mutación utilizada en el algoritmo.
            */
            inline double getProbabilidadMutacion(){
                return probabilidad_mutacion;
            }
        
            /**
            * @brief Método que devuelve el número de individuos de la población.
            */
            inline int getNumeroIndividuos(){
                return numero_individuos;
            }
        };

#endif