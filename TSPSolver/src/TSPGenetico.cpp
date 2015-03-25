# include "TSPGenetico.h"

                        /* MÉTODOS PÚBLICOS */ 

// Constructor de la clase:
TSPGenetico::TSPGenetico(TSPProblema *nuevo_problema, TSPRandom *generador_aleatorio, TSPGRASP *heuristica_grasp, TSPLocalSearch *mejora_local)
    :nombre_algoritmo("Compact Genetic"), problema(nuevo_problema), generador_aleatorio(generador_aleatorio), heuristica_grasp(heuristica_grasp), mejora_local(mejora_local), probabilidad_cruce(1), probabilidad_mutacion(0.1), numero_individuos(8), num_candidatos(2), poblacion(0)
{}

// Método que aplicando Genetico devuelve un puntero a una nueva solución:
TSPSolucion *TSPGenetico::buscarSolucion(int num_generaciones){

    // Se crea la población:
    poblacion = new TSPColeccionSoluciones(problema, heuristica_grasp, numero_individuos);
    TSPSolucion *nueva_solucion;
    for (int i = 0; i < numero_individuos; i++){
        nueva_solucion = generador_aleatorio->solucionAleatoria();
        poblacion->pushSolucion(nueva_solucion);
    }

    // Se evoluciona la población:
    for (int i = 0; i < num_generaciones; i++){
        poblacion->evolucionar(probabilidad_mutacion, 0.7, num_candidatos);
    }

    TSPSolucion * mejor_individuo = new TSPSolucion(*(poblacion->solucionPosicion(1+poblacion->buscarMejor())));

    mejor_individuo->setAlgoritmo(&nombre_algoritmo);

    delete poblacion;

    return mejor_individuo;
}

// Método que aplicando Genetico devuelve un puntero a una nueva solución:
TSPSolucion *TSPGenetico::buscarSolucionSnug(int num_generaciones){
    
    /* Algoritmo: 
            - Se crea una población de número de indviduos dado donde la mitad son generados por GRASP y los demás son aleatorios.
            - Se calcula el mejor de la población y se copia en mejor_individuo.
            - Se evoluciona la población un número de generaciones dado de la siguiente forma:
                - Cada mil generaciones se toma el mejor de la poblacion, se copia, 
                   se le aplica a mejora local a la copia y si es mejor que meor_individuo se asigna a este.
            - Se elimina a población.
            - Se devuelve mejor_individuo.
    */

    // Se crea la población:
    poblacion = new TSPColeccionSoluciones(problema, heuristica_grasp, numero_individuos);
    TSPSolucion *nueva_solucion;
    for (int i = 0; i < numero_individuos; i++){
        nueva_solucion = generador_aleatorio->solucionAleatoria();
        poblacion->pushSolucion(nueva_solucion);
    }

    // Se evoluciona la población:
    for (int i = 0; i < num_generaciones; i++){
        poblacion->evolucionarSnug(probabilidad_mutacion, num_candidatos);
    }
    TSPSolucion * mejor_individuo = new TSPSolucion(*(poblacion->solucionPosicion(1+poblacion->buscarMejor())));
    
    mejor_individuo->setAlgoritmo(&nombre_algoritmo);

    delete poblacion;

    return mejor_individuo;
}

// Método que cambia la probabilidad de cruce:
void TSPGenetico::setProbabilidadCruce(double nueva_probabilidad){
    if (nueva_probabilidad >= 0){
        probabilidad_cruce = nueva_probabilidad;
    }
    else{
        throw logic_error("La probabilidad debe ser mayor o igual que 0.\n");
    }
}

// Método que cambia la probabilidad de mutación:
void TSPGenetico::setProbabilidadMutacion(double nueva_probabilidad){
    if (nueva_probabilidad >= 0){
        probabilidad_mutacion = nueva_probabilidad;
    }
    else{
        throw logic_error("La probabilidad debe ser mayor o igual que 0.\n");
    }
}

// Método que cambia el número de individuos de la población:
void TSPGenetico::setNumeroIndividuos(double numero_individuos){
    if (numero_individuos > 0){
        this->numero_individuos = numero_individuos;
    }
    else{
        throw logic_error("Debe haber al menos un individuo.\n");
    }
}