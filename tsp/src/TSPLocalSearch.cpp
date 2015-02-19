#include "TSPLocalSearch.h"

// Constructor de la clase:
TSPLocalSearch::TSPLocalSearch(TSPProblema *nuevo_problema)
    :nombre_mejora("2-OPT"), problema(nuevo_problema)
{}

// Método que mejora la solucion dada:
void TSPLocalSearch::mejorarSolucionMejorIntercambio(TSPSolucion *solucion) const{
    
    solucion->setMejora(nombre_mejora);

    /* Algoritmo:
            Realiza un intercambio que mejore la solución si este existe. Cuando no se realice ningún intercambio para.
    */
    bool hay_mejora = true;

    while (hay_mejora){
        hay_mejora = solucion->determinarMejorIntercambio();
    }
}

// Método que mejora la solucion dada:
void TSPLocalSearch::mejorarSolucionPrimerIntercambio(TSPSolucion *solucion) const{
    
    solucion->setMejora(nombre_mejora);

    /* Algoritmo:
            Realiza un intercambio que mejore la solución si este existe. Cuando no se realice ningún intercambio para.
    */
    bool hay_mejora = true;

    while (hay_mejora){
        hay_mejora = solucion->determinarPrimerMejorIntercambio();
    }
}

// Método que, dada una solución, devuelve una mejora de la misma:
TSPSolucion *TSPLocalSearch::obtenerSolucionMejorada(TSPSolucion *solucion){
    
    TSPSolucion *solucion_mejorada = new TSPSolucion(*solucion);
    
    mejorarSolucionMejorIntercambio(solucion_mejorada);

    return solucion_mejorada;
}