# include "TSPMejorInsercion.h"

using namespace std;

                       /* MÉTODOS PÚBLICOS */

// Constructor de la clase:
TSPMejorInsercion::TSPMejorInsercion(TSPProblema *problema)
    :nombre_algoritmo("Inserción"), problema(problema)
{}

// Método que encuentra una solución óptima al problema empezando en la ciudad inicio:
TSPSolucion *TSPMejorInsercion::resolver(int inicio) const{
    TSPSolucion *nueva_solucion = new TSPSolucion(problema, &nombre_algoritmo);
    
    nueva_solucion->insertarCiudad(inicio,0);
    int num_ciudades = problema->numeroCiudades();
    
    // Se añade una ciudad por cada iteracción:
    for (int i = 1; i < num_ciudades ; i++){
        nueva_solucion->determinarMejorInsercion();
    }

    return nueva_solucion;
}

// Método que resuelve el problema empezando en todas las ciudades y eligiendo la mejor solución de entre las anteriores:
void TSPMejorInsercion::resolver(){
    solucion = resolver(0);
    
    TSPSolucion *alternativa;
    int num_ciudades = problema->numeroCiudades();
    
    for (int i = 1; i < num_ciudades; i++){
        alternativa = resolver(i);
        if (*alternativa < *solucion){
            delete solucion;
            solucion = alternativa;
        }
        else{
            delete alternativa;
        }
    }
}

// Método que resuelve el problema y devuelve la solución obtenida:
TSPSolucion *TSPMejorInsercion::obtenerSolucion(){
    resolver();
    return solucion;
}
