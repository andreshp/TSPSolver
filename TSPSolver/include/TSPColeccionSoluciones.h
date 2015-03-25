# ifndef TSPCOLECCIONSOLUCIONES_H
# define TSPCOLECCIONSOLUCIONES_H

    # include "TSPSolucion.h"
    # include "TSPProblema.h"
    # include "TSPGRASP.h"
    # include "TSPLocalSearch.h"
    # include <stdlib.h>
    # include <vector>
    # include <algorithm>
      
    /**
    * @brief Clase que administra un conjunto de soluciones de un problema de TSP dado.
    */

    class TSPColeccionSoluciones{
        private:
                            /* DATOS MIEMBRO */
            /**
            * @brief Vector de punteros a objetos TSPSolucion.
            * @brief Estará ordenado de menor a mayor coste de la solución.
            */
            TSPSolucion  **soluciones;
            
            /**
            * @brief Entero con la capacidad máxima de soluciones de la colección.
            * @brief Se inicializa en el constructor y aumenta al añadir una solución si ya se ha ocupado toda la capacidad.
            */
            int capacidad;
            
            /**
            * @brief Entero con el número de soluciones almacenadas.
            * @brief Se inicializa a 0 en el constructor y se modifica al añadir o eliminar una solución.
            */
            int soluciones_almacenadas;
            
            /**
            * @brief Puntero a un objeto de la clase TSPGRASP que se utilizará en evoluciona().
            * @brief Se inicializa en el constructor.
            */
            TSPGRASP *heuristica_grasp;
            
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;

                            /* MÉTODOS PRIVADOS */

            /**
            * @brief Método que imprime la información de cierta solución sin comprobar si el índice dado es correcto.
            * @brief Se imprime el algoritmo que se ha utilizado, la mejora y el coste.
            * @param posicion Posición que ocupa la solución de la que se desea imprimir su información en soluciones.
            */
            void imprimirInformacionSolucionPrivado(int posicion) const;

            /**
            * @brief Método que libera el espacio de soluciones y cada solución que almacena.
            */
            inline void liberarEspacio(){
                for (int i = 0; i < soluciones_almacenadas; i++){
                    delete soluciones[i];
                }
                delete [] soluciones;
            }

            /**
            * @brief Método privado recursivo que ordena de menor a mayor coste las soluciones.
            * @brief Utiliza el algoritmo de quicksort trabajando, en cada llamada, entre los límites pasados como parámetro.
            * @param lim_izda Posición más a la izquierda de la colección que se va a ordenar.
            * @param lim_dcha Posición más a la derecha de la colección que se va a ordenar.
            */
            void quickSort(int lim_izda, int lim_dcha);

        public:

                            /* MÉTODOS PÚBLICOS */    
            /**
            * @brief Constructor de la clase.
            * @param problema Puntero al problema que resolverán las soluciones a almacenar.
            * @param num_soluciones Entero que indica que se debe reservar espacio para ese número de soluciones.
            */
            TSPColeccionSoluciones(TSPProblema *problema, TSPGRASP *heuristica_grasp, int = 0);

            /**
            * @brief Destructor de la clase.
            * @brief LLama a liberarEspacio().
            */
            ~TSPColeccionSoluciones();

            /**
            * @brief Constructor de copia de la clase.
            * @param otra_coleccion Objeto de la misma clase que se desea copiar.
            */
            TSPColeccionSoluciones(const TSPColeccionSoluciones & otra_coleccion);

            /**
            * @brief Método que elimina todas las soluciones menos las n primeras.
            * @param primeras Número que indica cuántas de las mejores soluciones no se borrarán.
            */
            void eliminarSolucionesMenos(int primeras);            

            /**
            * @brief Método que imprime la información de cierta solución.
            * @brief Se imprime el algoritmo que se ha utilizado, la mejora y el coste.
            * Se comprueba que la posición dada es correcta y se llama al método privado.
            * @param posicion Posición que ocupa la solución de la que se desea imprimir su información en soluciones.
            */
            void imprimirInformacionSolucion(int posicion) const;
            
            /**
            * @brief Método que imprime la información de todas las soluciones.
            * @brief Se imprime el algoritmo que se ha utilizado, la mejora y el coste de cada solución ordenadas de menor a mayor coste.
            */
            void imprimirHistorial() const;

            /**
            * @brief Método que inserta una nueva solución en la colección.
            * @brief Coloca la solución ordenada en función de su coste.
            * @param solucion Solución a insertar.
            */
            void insertarSolucion(TSPSolucion *solucion);

            /**
            * @brief Método que devuelve el número de soluciones almacenadas.
            */
            inline int numeroSoluciones() const{
                return soluciones_almacenadas;
            }

            /**
            * @brief Ordena la colección de soluciones de menor a mayor coste.
            * @brief Llama al método privado quicksort.
            */
            inline void ordena(){
                quickSort(0,soluciones_almacenadas -1);
            }

            /**
            * @brief Método que añade una nueva solución a la colección.
            * @brief Coloca la solución al final de la colección.
            * @param solucion Solución a añadir.
            */
            void pushSolucion(TSPSolucion *solucion);
            
            /**
            * @brief Método que devuelve un puntero a la solución de posición dada.
            * @brief Se comprueba que el parámetro es correcto.
            * @param posicion Posición que ocupa ĺa solución que se pide en la colección de soluciones.
            */
            TSPSolucion *solucionPosicion(int posicion) const;

            /**
            * @brief Método que elige aleatoriamente num_candidatos soluciones de la colección y devuelve la mejor.
            * @brief Es utilizado en el algoritmo genético.
            * @param num_candidatos Número de soluciones elegidas inicialmente para escoger la mejor entre ellas.
            * @return Puntero a la mejor solución entre las elegidas.
            */
            TSPSolucion *seleccionPorTorneo(const int num_candidatos) const;

            /**
            * @brief Método que devuelve la posición que ocupa la mejor solución del historial.
            * @brief Se utiliza en el algoritmo genético pues durante su ejecución las soluciones no estarán ordenadas por coste.
            */
            int buscarMejor() const;

            /**
            * @brief Método que devuelve la posición que ocupa la peor solución del historial.
            * @brief Se utiliza en el algoritmo genético pues durante su ejecución las soluciones no estarán ordenadas por coste.
            */
            int buscarPeor() const;

            /**
            * @brief Método que realiza una iterración del algoritmo genético, evolucionando la población en una generación.
            * @param probabilidad_mutacion Probabilidad de que se realice una mutación en la nueva solución.
            * @param num_candidatos Número de soluciones elegidas inicialmente para escoger la mejor entre ellas.
            */
            void evolucionar(const double & probabilidad_mutacion, const double & probabilidad_cruce, const int & num_candidatos);

            /**
            * @brief Método que realiza una iterración del algoritmo genético snug, evolucionando la población en una generación.
            * @param probabilidad_mutacion Probabilidad de que se realice una mutación en la nueva solución.
            * @param num_candidatos Número de soluciones elegidas inicialmente para escoger la mejor entre ellas.
            */
            void evolucionarSnug(const double & probabilidad_mutacion, const int & num_candidatos);

    };

#endif