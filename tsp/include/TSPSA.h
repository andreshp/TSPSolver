# ifndef TSPSA_H
# define TSPSA_H
    
    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular solución al probema del Viajante de Comercio 
    * mediante el algoritmo heurístico SA (Simulated Annealing).
    * @brief Esta clase es amiga de TSPSolucion.
    */

    class TSPSA{
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
            * @brief Indice que penaliza a los vecinos de la solución con peor coste durante la ejecución del algoritmo.
            * @brief Se inicializa a 0.2 pero hay un método para cambiarlo: setIndiceValidez();
            */
            double indice_validez;
            
            /**
            * @brief Probabilidad de aceptar un vecino con peor coste al iniciar el algoritmo.
            * @brief Se inicializa a 0.3 pero hay un método para cambiarla: setProbabilidadInicial();
            */
            double probabilidad_inicial;
            
            /**
            * @brief Iteraciones del algoritmo en cada temperatura.
            * @brief Se inicializa a 1000 pero hay un método para cambiarlas.
            */
            double iteraciones_temp;

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
            * @brief Inicializa nombre_algoritmo y problema.
            * @param nuevo_problema Puntero a un objeto de la clase TSPProblema.
            */
            TSPSA(TSPProblema *nuevo_problema);

            /**
            * @brief Método que dada una solución, aplica SA para encontrar una solución mejor a la dada.
            * @brief El resultado depende de los parámetros que se tienen como datos miembro. Se accede a métodos privados y datos miembros de la clase TSPSolucion.
            * @param solucion Puntero a un objeto de la clase TSPSolucion a la que se le aplicará SA.
            * @param iteraciones Número de veces que se aplicará el proceso. 
            */
            void buscarSolucion(TSPSolucion *solucion, int iteraciones);

            /**
            * @brief Método que dada una solución, aplica SA devolviendo una solución mejor.
            * @param solucion Puntero a un objeto de la clase TSPSolucion a la que se le aplicará SA.
            * @param iteraciones Número de veces que se aplicará el proceso.
            * @return Solución obtenida. 
            */
            TSPSolucion *obtenerSolucion(TSPSolucion *solucion, int iteraciones);
            
            /**
            * @brief Método que cambia el índice de validez utilizado en el algoritmo.
            * @brief Se comprueba que es mayor que 0.
            * @param nuevo_indice Variable real con el nuevo índice.
            */
            void setIndiceValidez(double nuevo_indice);

            /**
            * @brief Método que cambia la probabilidad inicial del Simulated Annealing.
            * @brief Se comprueba que es mayor o igual que 0 y menor o igual que 1.
            * @param nueva_probabilidad Variable real con la nueva probabilidad inicial. 
            */
            void setProbabilidadInicial(double nueva_probabilidad);
            
            /**
            * @brief Método que cambia el número de iteraciones del algoritmo en cada temperatura.
            * @brief Se comprueba que es mayor que 1.
            * @param iteraciones_temp Variable real con el nuevo número de iteraciones deseado.
            */
            void setIteracionesPorTemperatura(int iteraciones_temp);

            /**
            * @brief Método que devuelve el índice de validez utilizado en el algoritmo.
            */
            inline double getIndiceValidez(){
                return indice_validez;
            }

            /**
            * @brief Método que devuelve la probabilidad inicial del Simulated Annealing.
            */
            inline double getProbabilidadInicial(){
                return probabilidad_inicial;
            }
        
            /**
            * @brief Método que devuelve el número de iteraciones del algoritmo en cada temperatura.
            */
            inline int getIteracionesPorTemperatura(){
                return iteraciones_temp;
            }
    
    };

#endif