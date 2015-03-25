# include "TSPRandom.h"

                /* MÉTODOS PÚBLICOS */ 

// Constructor de la clase:
TSPRandom::TSPRandom(TSPProblema *nuevo_problema)
    :nombre_algoritmo("Random"), problema(nuevo_problema)
{}

// Método que devuelve un puntero a una solución aleatoria:
TSPSolucion *TSPRandom::solucionAleatoria(){
        
    TSPSolucion *nueva_solucion = new TSPSolucion(problema, &nombre_algoritmo);
    
    int num_ciudades = problema->numeroCiudades();

    // Construcción de la solución:
    for (int i = 0; i < num_ciudades; i++){
        nueva_solucion->pushCiudadAleatoria();
    }

    nueva_solucion->recalcularCoste();

    return nueva_solucion;    
}