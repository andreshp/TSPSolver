#include "TSPGRASP.h"

            /* MÉTODOS PÚBLICOS */ 

// Constructor de la clase:
TSPGRASP::TSPGRASP(TSPProblema *nuevo_problema, TSPLocalSearch *mejora_local)
    :nombre_algoritmo("GRASP"), problema(nuevo_problema), mejora_local(mejora_local), indice_validez(1.1)
{}

// Constructor de copia de la clase:
TSPGRASP::TSPGRASP(const TSPGRASP & otro){
    nombre_algoritmo = otro.nombre_algoritmo;
    problema = otro.problema;
    mejora_local = otro.mejora_local;
    indice_validez = otro.indice_validez;    
}

// Método que aplicando GRASP devuelve un puntero a una nueva solución:
TSPSolucion *TSPGRASP::buscarSolucion() const{
        
    TSPSolucion *nueva_solucion = new TSPSolucion(problema, &nombre_algoritmo);
    
    // Se determina la ciudad de inicio:
    int num_ciudades = problema->numeroCiudades();
    int inicio = rand() % num_ciudades;
    nueva_solucion->insertarCiudad(inicio, 0);

    // Construcción de la solución:
    for (int i = 1; i < num_ciudades; i++){
        nueva_solucion->determinarVecinoGRASP(indice_validez);
    }

    // Mejora local de la solución:
    //mejora_local->mejorarSolucionMejorIntercambio(nueva_solucion);
    
    return nueva_solucion;    
}

// Método que aplicando GRASP devuelve un puntero a una nueva solución:
TSPSolucion *TSPGRASP::buscarSolucionLocalSearch() const{
        
    TSPSolucion *nueva_solucion = buscarSolucion();
    
    // Mejora local de la solución:
    mejora_local->mejorarSolucionMejorIntercambio(nueva_solucion);
    
    return nueva_solucion;    
}

// Método que cambia el índice de validez utilizado en el algoritmo GRASP:
void TSPGRASP::setIndiceValidez(double nuevo_indice){
    if (nuevo_indice >= 1){
        indice_validez = nuevo_indice;
    }
    else{
        throw logic_error("El índice introducido debe ser mayor o igual que 1.\n");
    }
}