# ifndef TSPSOLUCION_H
# define TSPSOLUCION_H

    # include <string>
    # include <stdexcept>
    # include <sstream>
    # include <iostream>
    # include <stdlib.h>
    # include "TSPProblema.h"
    # include <vector>
    
    using namespace std ;
    
    /**
    * @brief Clase que representa la solución a un problema del Viajante de Comercio dado por un objeto de la clase TSPProblema.
    */
    
    class TSPSolucion {
        private:
                                             /* DATOS MIEMBRO */
            /**
            * @brief Puntero a un objeto de la clase problema.
            * @brief Se inicializa en el constructor.
            */
            TSPProblema *problema;
            
            /**
            * @brief Puntero que contiene la dirección de memoria de un array con el orden en el que se visitan las ciudades. 
            * @brief Se crea el array (inicializando el puntero) en el método privado reservarEspacio().
            * Se inicializan las componentes mientras se va creando la solución mediante una clase externa.
            */
            int *orden_ciudades;
            
            /**
            * @brief Puntero que contiene la dirección de memoria de un array de bools donde la componente i indica si la ciudad i ha sido visitada o no.
            * @brief Se crea el array, inicializando el puntero y las componentes a false, en el método privado reservarEspacio().
            */
            bool *ciudades_visitadas;
            
            /**
            * @brief Número de ciudades con las que se trabaja.
            * @brief Se obtiene de problema.
            */
            int num_ciudades;
            
            /**
            * @brief Número de ciudades que han sido visitadas.
            * @brief Se inicializa a 0 en el constructor.
            */
            int num_visitadas;
            
            /**
            * @brief Variable que indica el coste total en distancias de realizar el recorrido propuesto como solución.
            * @brief Se inicializa a 0 en el constructor. Aumenta mientras se construye la solución hasta representar el coste final.
            */
            int coste;
      
            /** 
            * @brief Puntero a una string constante con el nombre del algoritmo que se ha utilizado para calcular la solución.
            * @brief Se inicializa en el constructor. El método setAlgoritmo modifica dicho puntero.
            */
            const string *algoritmo;

            /** 
            * @brief String que indica si se ha utilizado algún algoritmo para mejorar la solución y cuál es su nombre apuntando al mismo..
            * @brief Se inicializa apuntando a una string "Ninguna" en el constructor. Hay un método para modificarla.
            */
            string mejora;

            /**
            * @brief Bool que indica si se han intercambiado dos ciudades de la solución de forma extrena.
            * @brief Se inicializa a false en el constructor.
            */
            bool intercambio_ciudades;

                                          /* MÉTODOS PRIVADOS */
           
            /**
            * @brief Método privado que inserta una ciudad de índice dado en la posición indicada de orden_ciudades.
            * @brief Se asume que los datos son correctos, no realizando, por tanto, las comprobaciones oportunas.
            * @param indice_ciudad índice característico de la ciudad a insertar.
            * @param posicion Lugar de orden_ciudades donde se insertará la ciudad
            */
            void insertarCiudadPrivado(int indice_ciudad, int posicion);        
            
            /**
            * @brief Método privado que intercambia dos ciudades de posición dada en orden_ciudades.
            * @brief Se asume que los datos son correctos, no realizando, por tanto, las comprobaciones oportunas.
            * @param posicion1 Posición en orden_ciudades de la primera ciudad a intercambiar.
            * @param posicion2 Posición en orden_ciudades de la segunda ciudad a intercambiar.
            */
            inline void intercambiarCiudadesPrivado(int posicion1, int posicion2){
                  int intercambio;
                  
                  intercambio = orden_ciudades[posicion1]; 
                  orden_ciudades[posicion1] = orden_ciudades[posicion2];
                  orden_ciudades[posicion2] = intercambio;
            }

            /**
            * @brief Método que calcula el coste de una posible nueva solución con la ciudad de índice dado insertada en la posición indicada.
            * @param indice_ciudad Índice de la ciudad que se añadirá a la solución.
            * @param posicion Lugar de orden_ciudades en el que se situará la ciudad anterior.
            * @return Coste de la posible nueva solución.
            */
            int nuevoCosteInsercion(int indice_ciudad, int posicion) const;
    
            /**
            * @brief Método que calcula el coste de una posible nueva solución que resulta de intercambiar dos ciudades de posición.
            * @param posicion1 Posición en orden_ciudades de la primera ciudad a intercambiar.
            * @param posicion2 Posición en orden_ciudades de la segunda ciudad a intercambiar.
            * @return Coste de la posible nueva solución.
            */
            int nuevoCosteIntercambio(int posicion1, int posicion2) const;

            /**
            * @brief Método privado que reserva el espacio de varios datos miembro.
            * @brief Crea un array de enteros para orden_ciudades y otro array de bools para ciudades_visitadas.
            * Este último lo inicializa a false.
            */
            void reservarEspacio();
    
        public:
            
                                     /* MÉTODOS PÚBLICOS */
            /**
            * @brief Constructor de la clase.
            * @brief Inicializa problema, num_ciudades, num_visitadas, coste, mejora, algoritmo, intercambio_ciudades y se llama a reservarEspacio().
            * @param problema Puntero a un objeto de la clase TSPProblema con el problema a resolver.
            * @param algoritmo Puntero a una string con el nombre del algoritmo que se ha utilizado para construir la solución.
            */
            TSPSolucion(TSPProblema *problema, const string *algoritmo);
            
            /**
            * @brief Redefinición del constructor de copia.
            * @brief Se copian todos los datos miembro de una solución en otra nueva que se desea crear.
            * @param solucion Referencia a la solución que se desea copiar.
            */
            TSPSolucion(const TSPSolucion &solucion);

            /**
            * @brief Constructor de la clase. Crea una solución a partir de un array con el recorrido.
            * @brief No se hacen comprobaciones. Se asume que el puntero al array es correcto.
            * @param problema Puntero al problema con el que se trabaja.
            * @param recorrido Puntero al array con el recorrido de la solución.
            * @param algoritmo Puntero a una cadena con el nombre del algoritmo que se ha utilizado para obtener la solución.
            * @param mejora Cadena con el nombre de la mejora que se ja utilizado. Por defecto, no hay ninguna mejora.
            * @param intercambio_ciudades Valor booleano que indica si ha habido intercambio de ciudades. Por defecto, no hay intercambio.
            */
            TSPSolucion(TSPProblema *problema, int *recorrido, const string *algoritmo, string mejora = "Ninguna", bool intercambio_ciudades = false);

            /**
            * @brief Destructor de la clase.
            * @brief Se encarga de eliminar orden_ciudades  y ciudades_visitadas del heap además de las funciones propias del destructor.
            */
            ~TSPSolucion();


            /**
            * @brief Sobrecarga del operador <.
            * @brief Devuelve true si this->solucion tiene menor coste que otra solucion dada.
            */
            inline bool operator<(const TSPSolucion &otra_solucion) const{
                  return (this->coste < otra_solucion.coste);
            }

            /**
            * @brief Sobrecarga del operador >.
            * @brief Devuelve true si this->solucion tiene mayor coste que otra solucion dada.
            */
            inline bool operator>(const TSPSolucion &otra_solucion) const{
                  return (this->coste > otra_solucion.coste);
            }

            /**   
            * @brief Método que devuelve el índice de la ciudad que es visitada en la posicion dada.
            * @param posicion Entero que indica la posicion-ésima ciudad visitada.
            * @return índice de la ciudad en la posición dada en orden_ciudades.
            */
            int ciudadVisitada(int posicion) const;
            
            /**
            * @brief Método que devuelve la distancia total de trayecto.
            * @return coste
            */
            inline int distanciaTotal() const{
                  return coste;
            }        
    
            /**
            * @brief Método que calcula y realiza la mejor inserción posible para la solución actual.
            * @brief Si la solución ya contiene a todas las ciudades no hace nada.
            * Utiliza insertarCiudadPrivado() y nuevoCosteInsercion(). 
            */
            void determinarMejorInsercion();
            
            /**
            * @brief Método que calcula y realiza el mejor intercambio de ciudades posible para mejorar la solución actual.
            * @brief De no encontrar un intercambio que mejore el coste actual la solución permanece intacta.
            * Utiliza intercambiarCiudadPrivado() y nuevoCosteIntercambio().
            * @return Bool que indica si se ha realizado un intercambio o no. 
            */
            bool determinarMejorIntercambio();

            /**
            * @brief Método realiza el primer intercambio de ciudades que mejore la solución actual que encuentre.
            * @brief De no encontrar un intercambio que mejore el coste actual, la solución permanece intacta.
            * Utiliza intercambiarCiudadPrivado() y nuevoCosteIntercambio().
            * @return Bool que indica si se ha realizado un intercambio o no. 
            */
            bool determinarPrimerMejorIntercambio();


            /**
            * @brief Método que determina la siguiente ciudad a añadir (y la añade) según el criterio del vecino más cercano.
            * @brief Si la solución ya contiene a todas las ciudades no hace nada.
            */
            void determinarVecinoMasCercano();

            /**
            * @brief Método que determina la siguiente ciudad a añadir (y la añade) mediante el algoritmo  GRASP.
            * @brief Genera una lista de candidatos con las ciudades más cercanas a la que ocupa la última posición de la solución.
            * Se elige aleatoriamente una solución de esta lista y se añade actualizando coste.
            * Si la solución ya contiene a todas las ciudades no se hace nada.
            */
            void determinarVecinoGRASP(const double indice_validez);
            
            /**
            * @brief Método realiza una iteración de la mejora local Lin-Kernighan.
            * @brief De no encontrar un intercambio que mejore el coste actual, la solución permanece intacta.
            * @return Bool que indica si se ha realizado un intercambio o no. 
            */
            bool iteracionLinKernighan(int ciudad);
            
            /**
            * @brief Método recursivo que prueba un camino de la mejora local Lin-Kernighan.
            */
            void mejorarCamino(int *camino, int coste_camino, int iteracion, vector <bool> vertices_libres);

            /**
            * @brief Método que realiza un número de iteraciones dado del algoritmo simulated annealing a cierta temperatura dada.
            * @param temperatura Temperatura del proceso durante las iteraciones. A más temperatura, mayor probabilidad de aceptar una solución peor.
            * @param num_iteraciones Número de veces que se realiza el proceso.
            * @param max_exitos Número máximo de veces que se aceptará un vecino durante el agoritmo.
            */
            void realizarIteracionesSA(const double temperatura, const int num_iteraciones, const int max_exitos);
            
            /**
            * @brief Método que si quedan ciudades por visitar añade una de ellas aleatoriamente.
            */
            void pushCiudadAleatoria();

            /**
            * @brief Método que construye la solución a partir de los padres mediante el algoritmo de cruce OX.
            * @brief Se toma una subcadena del padre1.
            */            
            void generarHijo(TSPSolucion *padre1, TSPSolucion *padre2);
           
            /**
            * @brief Método que produce una mutación aleatoria en la solución itercambiando dos ciudades.
            * @brief Utiliza los métodos intercambiarCiudadPrivado() y nuevoCosteIntercambio();
            */
            void mutacionIntercambio();

            /**
            * @brief Método que produce una mutación aleatoria en la solución cambiando una ciudad de posición insertándola aleatoriamente.
            */
            void mutacionInsercion();

            /**
            * @brief Método que produce una mutación aleatoria en la solución.
            * @brief Elige una subcadena de la solución y los reordena pseudoaleatoriamente.
            */
            void mutacion();

            /**
            * @brief Método que recalcula el coste de la solución.
            * @brief Suma de nuevo todas las distancias del recorrido.
            */
            void recalcularCoste();

            /**
            * @brief Método que inserta el índice de una ciudad en la posición dada de *orden_ciudades. 
            * @brief Se comprueba que los datos son correctos.
            * @param indice_ciudad índice característico de la ciudad a insertar.
            * @param posicion Lugar de orden_ciudades donde se insertará la ciudad.
            */
            void insertarCiudad(int indice_ciudad, int posicion);
            
            /**
            * @brief Método que intercambia las ciudades dadas por las posiciones de los índices devolviendo una nueva solución.
            * @brief Se comprueba que los datos son correctos.
            * @param posicion1 Posición en orden_ciudades de la primera ciudad a intercambiar.
            * @param posicion2 Posición en orden_ciudades de la segunda ciudad a intercambiar.
            * @return Puntero a una nueva solución con las ciudades intercambiadas.
            */
            TSPSolucion *intercambiarCiudades(int indice_ciudad1, int indice_ciudad2);

            /**
            * @brief Método que imprime en la consola el orden en el que se visitarán las ciudades según la solución actual.
            */
            void imprimirSolucion() const;
    
            /**
            * @brief Método que asigna una nueva cadena al dato miembro mejora.
            */
            void setMejora(string mejora){
                this->mejora = mejora;
            }

            /**
            * @brief Método que asigna una nueva dirección de memoria con el nombre del algoritmo utilizado al dato miembro algoritmo.
            */
            void setAlgoritmo(const string *algoritmo){
                this->algoritmo = algoritmo;
            }

            /**
            * @brief Método que devuelve el nombre del algoritmo utilizado para construir la solución.
            * @return string con el nombre del algoritmo.
            */
            inline string getAlgoritmo() const{
                return *algoritmo;
            
            }

            /**
            * @brief Método que devuelve el nombre de la mejora utilizada para construir la solución.
            * @return string con el nombre de la mejora.
            */
            inline string getMejora() const{
                  return mejora;
            }

            /**
            * @brief Método que devuelve una copia del dato miembro intercambio_ciudades.
            */
            inline bool getIntercambioCiudades() const{
                  return intercambio_ciudades;
            }
    };

# endif