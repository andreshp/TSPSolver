#include "TSPILS.h"

                /* MÉTODOS PÚBLICOS */ 

// Constructor de la clase:
TSPILS::TSPILS(TSPProblema *nuevo_problema, TSPLocalSearch *mejora_local)
    :nombre_algoritmo("ILS"), problema(nuevo_problema), mejora_local(mejora_local)
{}

// Método que aplicando ILS encuentra una solución mejor a la dada asignándosela al dato miembro mejor_solucion:
void TSPILS::buscarSolucion(TSPSolucion *solucion, int iteraciones){
    /* Algoritmo:
        - Se copia la solución dada, apuntando mejor_solucion a la copia.
        - Se aplica la mejora local a mejor_solucion.
        - Por cada iteración pedida:
            - Se copia mejor_solucion en solucion_actual.
            - Se realiza una mutacion en solucion_actual.
            - Se aplica la mejora local a solucion_actual.
            - Si solucion_actual tiene menor coste que mejor_solucion se le asigna a esta.
    */ 
    
    // Se copia la solución dada, apuntando mejor_solucion a la copia:
    mejor_solucion = new TSPSolucion(*solucion);
    mejor_solucion->setAlgoritmo(&nombre_algoritmo);

    // Se aplica la mejora local a la solución:
    mejora_local->mejorarSolucionPrimerIntercambio(mejor_solucion);

    TSPSolucion *solucion_actual;

    // Iteraciones de ILS:
    for (int i = 0; i < iteraciones; i++){

        solucion_actual = new TSPSolucion(*mejor_solucion);
        solucion_actual->mutacion();
        mejora_local->mejorarSolucionPrimerIntercambio(solucion_actual);
        
        if (*solucion_actual < *mejor_solucion){
            delete mejor_solucion;
            mejor_solucion = solucion_actual;
        }
        else{
            delete solucion_actual;
        }
    }
}

// Método que dada una solución, aplica ILS devolviendo una solución mejor:
TSPSolucion *TSPILS::obtenerSolucion(TSPSolucion *solucion, int iteraciones){
    buscarSolucion(solucion, iteraciones);
    return mejor_solucion;
}
