#include "TSPLocalSearch.h"

                /* MÉTODOS PÚBLICOS */

// Constructor de la clase:
TSPLocalSearch::TSPLocalSearch()
    :OPT_2("2-OPT"), lin_kernighan("Lin-Kernighan")
{}

// Método que mejora la solucion dada:
void TSPLocalSearch::mejorarSolucionMejorIntercambio(TSPSolucion *solucion) const
{
    solucion->setMejora(OPT_2);

    /* Algoritmo:
            Realiza un intercambio que mejore la solución si este existe. Cuando no se realice ningún intercambio para.
    */
    bool hay_mejora = true;

    while (hay_mejora){
        hay_mejora = solucion->determinarMejorIntercambio();
    }
}

// Método que mejora la solucion dada:
void TSPLocalSearch::mejorarSolucionPrimerIntercambio(TSPSolucion *solucion) const
{    
    solucion->setMejora(OPT_2);

    /* Algoritmo:
            Realiza un intercambio que mejore la solución si este existe. Cuando no se realice ningún intercambio para.
    */
    bool hay_mejora = true;

    while (hay_mejora){
        hay_mejora = solucion->determinarPrimerMejorIntercambio();
    }
}

// Método que mejora la solución actual mediante el algoritmo de Lin-Kernighan:
void TSPLocalSearch::LinKernighan(TSPSolucion *solucion, int num_ciudades){
    bool cambio = true;
    while(cambio){
        for (int i = 0; i < num_ciudades; i++){    
            cambio = solucion->iteracionLinKernighan(i);
            if (cambio == true)
                break;
        }
    }
    solucion->setMejora(lin_kernighan);
}

// Método que, dada una solución, devuelve una mejora de la misma:
TSPSolucion *TSPLocalSearch::obtenerSolucionMejorada(TSPSolucion *solucion)
{    
    TSPSolucion *solucion_mejorada = new TSPSolucion(*solucion);
    
    mejorarSolucionMejorIntercambio(solucion_mejorada);

    return solucion_mejorada;
}