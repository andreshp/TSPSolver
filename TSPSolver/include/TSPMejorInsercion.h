# ifndef TSPMEJORINSERCION_H
# define TSPMEJORINSERCION_H

    # include "TSPSolucion.h"
    # include "TSPProblema.h"
    
    using namespace std;
    
    /**
    * @brief Clase que contiene los métodos necesarios para calcular una solución al probema del Viajante de Comercio
    * mediante el algoritmo heurístico de inserción.
    */
    
    class TSPMejorInsercion {
        private:
                                /* DATOS MIEMBRO */
            /**
            * @brief Puntero a un objeto de la clase TSPProblema.
            * @brief Se inicializa en el constructor mediante un puntero que se pasa como parámetro.
            */
            TSPProblema *problema;

            /**
            * @brief Puntero a un objeto de la clase TSPSolucion.
            * @brief Se asigna un puntero a una solución en el método resolver().
            */
            TSPSolucion *solucion;
            
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
            * @brief Inicializa problema.
            * @param problema Puntero a un objeto de la clase TSPProblema con el problema a resolver.
            */
            TSPMejorInsercion(TSPProblema *problema);
            
            /**
            * @brief Método que calcula una solución mediante el método heurístico inserción empezando en una ciudad dada.
            * @brief Utiliza el método determinarMejorInserción de la clase TSPSolucion.
            * @param inicio Índice de la ciudad incial a partir de la cual se insertan las demás.
            * @return Puntero a un objeto de la clase TSPSolución con la solución calculada.
            */
            TSPSolucion *resolver(int inicio) const;
            
            /*
            * @brief Método que calcula una solución utilizando el método anterior en cada una de las ciudades.
            */
            void resolver();
            
            /**
            * @brief Método que obtiene una solución llamando a resolver() y devuelve un puntero a la misma.
            * @return Objeto de la clase TSPSolución con una solución al problema.
            */
            TSPSolucion *obtenerSolucion();
    };

# endif