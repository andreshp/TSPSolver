#include "TSPSA.h"

// Macro que se utilizará en el código del algoritmo cuando se modifique la solución:
#define aceptar_vecino  solucion_actual->intercambiarCiudadesPrivado(pos1, pos2); \
                        *coste_actual = nuevo_coste; \
                        exitos++;
                

                /* MÉTODOS PÚBLICOS */ 

// Constructor de la clase:
TSPSA::TSPSA(TSPProblema *nuevo_problema)
    :nombre_algoritmo("SA"), problema(nuevo_problema), indice_validez(0.1), probabilidad_inicial(0.1), iteraciones_temp(1000)
{}

// Método que aplicando SA encuentra una solución mejor a la dada asignándosela al dato miembro mejor_solucion:
void TSPSA::buscarSolucion(TSPSolucion *solucion, int iteraciones){
    /* Algoritmo:
        - Se copia la solución dada, apuntando mejor_solucion a la copia.
        - Se inicializa la temperatura inicial, final y la que variará durante el proceso de tal forma que se realicen el número de iteraciones pedidas.
        - Mientras temperatura sea mayor que la temperatura final:
            - Se realizan iteraciones_temp iteraciones del algoritmo llamando a realizarIteracionSA sobre solucion_actual.
            - Si solucion_actual tiene menor coste que mejor_solucion, se acepta.
            - Se actualiza la temperatura.
    */

    // Se copia la solución dada, apuntando mejor_solucion a la copia:
    mejor_solucion = new TSPSolucion(*solucion);
    mejor_solucion->setAlgoritmo(&nombre_algoritmo);

    // Solución sobre la que se harán los cambios:
    TSPSolucion *solucion_actual = new TSPSolucion(*mejor_solucion);
      
    // Se establece un máximo de éxitos (aceptar un vecino) por iteración:
    int num_ciudades = problema->numeroCiudades();
    int exitos, max_exitos = num_ciudades * 1.5;
    
    // Se inicializan las temperaturas:
    double temp_inicial = (indice_validez/-log(probabilidad_inicial)) * mejor_solucion->distanciaTotal();
    double temp_final = mejor_solucion->distanciaTotal() / 1000;
    double temperatura = temp_inicial;
    
    // Se cacula el ratio de enfriamiento que se utilizará para actualizar la temperatura del sistema:
    double ratio_enfriamiento = (temp_inicial - temp_final)/(iteraciones * temp_inicial * temp_final);
    
    int pos1, pos2;

    // Iteraciones de SA:
    while(temperatura > temp_final){

        // Se realizan iteraciones_temp iteraciones de SA;
        solucion_actual->realizarIteracionesSA(temperatura, iteraciones_temp, max_exitos);
        
        // Se comprueba si solucion_actual es mejor:
        if (*solucion_actual < *mejor_solucion){
            delete mejor_solucion;
            mejor_solucion = new TSPSolucion(*solucion_actual);
        }
        
        // Se actualiza la temperatura:
        temperatura = temperatura / (1 + ratio_enfriamiento * temperatura);
    }

    delete solucion_actual;
}

// Método que dada una solución, aplica SA devolviendo una solución mejor:
TSPSolucion *TSPSA::obtenerSolucion(TSPSolucion *solucion, int iteraciones){
    buscarSolucion(solucion, iteraciones);
    return mejor_solucion;
}

// Método que cambia el índice de validez utilizado en el algoritmo SA:
void TSPSA::setIndiceValidez(double nuevo_indice){
    if (nuevo_indice > 0){
        indice_validez = nuevo_indice;
    }
    else{
        throw logic_error("El índice introducido debe ser mayor que 0.\n");
    }
}

// Método que cambia la probabilidad inicial utilizada en el algoritmo SA:
void TSPSA::setProbabilidadInicial(double nueva_probabilidad){
    if (nueva_probabilidad >= 0 && nueva_probabilidad <= 1){
        probabilidad_inicial = nueva_probabilidad;
    }
    else{
        throw logic_error("La probabilidad introducida debe estar entre 0 y 1.\n");
    }
}

// Método que cambia el índice de validez utilizado en el algoritmo SA:
void TSPSA::setIteracionesPorTemperatura(int iteraciones){
    if (iteraciones > 0){
        iteraciones_temp = iteraciones;
    }
    else{
        throw logic_error("El número de iteraciones debe ser mayor que 0.\n");
    }
}