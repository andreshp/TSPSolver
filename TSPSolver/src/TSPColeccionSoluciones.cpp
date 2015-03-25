# include "TSPColeccionSoluciones.h"

                    /* MÉTODOS PRIVADOS */

// Método que imprime la información de cierta solución sin comprobar si la posición dada es correcta.
// Se imprime el algoritmo que se ha utilizado, la mejora, el coste y si ha sido realizado un intercambio externo de ciudades.
void TSPColeccionSoluciones::imprimirInformacionSolucionPrivado(int posicion) const{
    cout << "Solución " << posicion + 1 << " -> Coste: " << soluciones[posicion]->distanciaTotal() << " | Algoritmo: " << soluciones[posicion]->getAlgoritmo() << " | Mejora: " << soluciones[posicion]->getMejora();

    if (soluciones[posicion]->getIntercambioCiudades()){
        cout << " | Se han intercambiado ciudades de forma externa.";
    }

    cout << endl;
}

// Método privado con el algoritmo recursivo quicksort que ordena de menor a mayor coste las soluciones:
void TSPColeccionSoluciones::quickSort(int lim_izda, int lim_dcha){
    // Declaración de variables y punteros:
    int izda = lim_izda;
    int dcha = lim_dcha;
    int pos_pivote = (izda+dcha)/2;
    
    TSPSolucion *pivote = soluciones[pos_pivote];
    TSPSolucion *temporal;

    do{
        // Aumenta izda hasta que llegue a una solución de coste mayor que el pivote:
        while(*soluciones[izda] < *pivote && izda < lim_dcha){
            izda++;
        }
        // Disminuye izda hasta que llegue a una solución de coste menor que el pivote:
        while(*pivote < *soluciones[dcha] && dcha > lim_izda){
            dcha--;
        }

        // Si todavía no se han cruzado izda y dcha, intercambiamos las soluciones a las que apuntan:
        if(izda <= dcha){
            temporal = soluciones[izda];
            soluciones[izda]=soluciones[dcha];
            soluciones[dcha]=temporal;

            izda++;
            dcha--;
        }
 
    }while(izda <= dcha);

    // Llamamos recursivamente a quicksort en las dos mitades en las que ha quedado dividido 
    // por pivote el subconjunto de soluciones en el que trabajábamos:
    if(lim_izda < dcha)
        quickSort(lim_izda, dcha);
    if(lim_dcha > izda)
        quickSort(izda, lim_dcha);
}            

                    /* MÉTODOS PÚBLICOS */

// Constructor de la clase:
TSPColeccionSoluciones::TSPColeccionSoluciones(TSPProblema *problema, TSPGRASP *heuristica_grasp, int num_soluciones)
    :problema(problema),  soluciones_almacenadas(0), heuristica_grasp(heuristica_grasp)
{
    capacidad = num_soluciones + 1 / (num_soluciones + 1);
    soluciones = new TSPSolucion *[capacidad];
}

// Destructor de la clase:
TSPColeccionSoluciones::~TSPColeccionSoluciones(){
    liberarEspacio();    
}

// Constructor de copia de la clase:
TSPColeccionSoluciones::TSPColeccionSoluciones(const TSPColeccionSoluciones & otra_coleccion){
    // Se copian los siguientes datos miembros:
    this->problema = otra_coleccion.problema;
    this->soluciones_almacenadas = otra_coleccion.soluciones_almacenadas; 
    this->heuristica_grasp = otra_coleccion.heuristica_grasp;
    this->capacidad = otra_coleccion.capacidad;

    // Se crea un array en el heap para soluciones y se copian los objetos de la clase TSPSolucion:
    this->soluciones = new TSPSolucion *[capacidad];
    for (int i = 0; i < soluciones_almacenadas; i++){
        this->soluciones[i] = new TSPSolucion(*(otra_coleccion.soluciones[i]));
    }
}

// Método que elimina todas las soluciones menos las n primeras.
void TSPColeccionSoluciones::eliminarSolucionesMenos(int primeras){
    if (primeras >= 0){
        for (int i = soluciones_almacenadas-1; i >= primeras; i--){
            delete soluciones[i];
        }
        soluciones_almacenadas = primeras;
    }
    else{
        throw logic_error("Debe introducir un número mayor o igual que 0.\n");
    }
}       

// Método que imprime la información de cierta solución de posición dada:
void TSPColeccionSoluciones::imprimirInformacionSolucion(int posicion) const{
    if (posicion <= soluciones_almacenadas && posicion > 0){
        imprimirInformacionSolucionPrivado(posicion - 1);
        cout << "Recorrido de la solución:\n";
        soluciones[posicion-1]->imprimirSolucion();
    }   
    else if (soluciones_almacenadas == 0){
        throw logic_error("No hay soluciones en el historial.\n");
    } 
    else{
        throw logic_error("La posición debe estar entre 1 y " + static_cast<ostringstream*>(&(ostringstream() << soluciones_almacenadas))->str() + "\n");

    }
}

//Método que imprime la información de todas las soluciones.
// Se imprime el algoritmo que se ha utilizado, la mejora y el coste de cada solución ordenadas de menor a mayor coste:
void TSPColeccionSoluciones::imprimirHistorial() const{
    if (soluciones_almacenadas > 0){
        cout << "HISTORIAL DE SOLUCIONES:\n";
        for (int i = 0; i < soluciones_almacenadas; i++){
            imprimirInformacionSolucionPrivado(i);
        }
    }
    else{
        throw logic_error("No hay soluciones en el historial.\n");    
    }

    cout << endl;
}

// Método que inserta una nueva solución a la colección en función de su coste:
void TSPColeccionSoluciones::insertarSolucion(TSPSolucion *solucion){
    // Se añade la solución y se ordena según su coste:
    pushSolucion(solucion);

    int i;
    for (i = soluciones_almacenadas - 1; i >= 1 && *solucion < *soluciones[i-1]; i--){
        soluciones[i] = soluciones[i-1];
    }

    soluciones[i] = solucion;   
}

// Método que añade una nueva solución a la coleción:
void TSPColeccionSoluciones::pushSolucion(TSPSolucion *solucion){
    // Si hay espacio se añade. En caso contrario, se crea un nuevo array con uno más de capacidad.
    if (soluciones_almacenadas < capacidad){
        soluciones[soluciones_almacenadas] = solucion;
        soluciones_almacenadas++;
    }
    else{
        capacidad++;
        TSPSolucion **nuevas_soluciones = new TSPSolucion *[capacidad];
        
        for (int i = 0; i < soluciones_almacenadas; i++){
            nuevas_soluciones[i] = soluciones[i];
        }
        delete [] soluciones;
        soluciones = nuevas_soluciones;
        
        pushSolucion(solucion);
    }
}

// Método que devuelve un puntero a la solución de posición dada:
TSPSolucion *TSPColeccionSoluciones::solucionPosicion(int posicion) const{
    if (posicion <= soluciones_almacenadas && posicion > 0){
        return soluciones[posicion - 1];
    }   
    else if (soluciones_almacenadas == 0){
        throw logic_error("No hay soluciones en el historial.\n");
    }
    else{
        throw logic_error("La posición debe estar entre 1 y " + static_cast<ostringstream*>(&(ostringstream() << soluciones_almacenadas))->str());
    }
}

// Método que elige aleatoriamente num_candidatos soluciones de la colección y devuelve la mejor de entre las elegidas:
TSPSolucion *TSPColeccionSoluciones::seleccionPorTorneo(const int num_candidatos) const{
    TSPSolucion *mejor_elegido = soluciones[rand() % soluciones_almacenadas];
    TSPSolucion *nuevo_elegido;

    for (int i = 1; i < num_candidatos; i++){
        nuevo_elegido = soluciones[rand() % soluciones_almacenadas];
        if (*nuevo_elegido < *mejor_elegido){
            mejor_elegido = nuevo_elegido;
        }
    }
    return mejor_elegido;
}

// Método que devuelve la posición que ocupa la mejor solución del historial:
int TSPColeccionSoluciones::buscarMejor() const{
    int mejor_solucion = 0;

    for (int i = 1; i < soluciones_almacenadas; i++){
        if (*soluciones[i] < *soluciones[mejor_solucion]){
            mejor_solucion = i;
        }
    }

    return mejor_solucion;
}

// Método que devuelve la posición que ocupa la peor solución del historial:
int TSPColeccionSoluciones::buscarPeor() const{
    int peor_solucion = 0;

    for (int i = 1; i < soluciones_almacenadas; i++){
        if (*soluciones[peor_solucion] < *soluciones[i]){
            peor_solucion = i;
        }
    }

    return peor_solucion;
}

// Método que realiza una iterración del algoritmo genético, evolucionando la población en una generación:
void TSPColeccionSoluciones::evolucionar(const double & probabilidad_mutacion, const double & probabilidad_cruce, const int & num_candidatos){
    
    /* Algoritmo:
            - Genera una nueva_generación de igual número de elementos de la anterior.
                - Cada elemento es hijo de la mejor solución con otra aleatoria.
                - Si se da cierta probabilidad de mutación entonces se realiza esta.
            - Se elimina la peor solución de nueva_generación y se añade la mejor solución de la anterior generación.
            - Se ordenan las soluciones por coste.
            - Si hay dos soluciones iguales se elimina una de estas y se añaden nuevas soluciones mediante GRASP.
            - Se libera la memoria y se asigna la nueva generación a la actual.
    */

    TSPColeccionSoluciones nueva_generacion(problema, heuristica_grasp, soluciones_almacenadas); 
    
    TSPSolucion *padre1, *padre2, *hijo;

    // Se crea la nueva generación:
    int posicion_peor_solucion, posicion_mejor_solucion;

    while (nueva_generacion.soluciones_almacenadas < soluciones_almacenadas){
        padre1 = seleccionPorTorneo(num_candidatos);
        padre2 = seleccionPorTorneo(num_candidatos);

        if (rand() / (double) RAND_MAX <= probabilidad_cruce){
            hijo = new TSPSolucion(problema, 0);
            hijo->generarHijo(padre1, padre2);
            if (rand() / (double) RAND_MAX <= probabilidad_mutacion){
                hijo->mutacionIntercambio();
            }
            nueva_generacion.pushSolucion(hijo);
            
            hijo = new TSPSolucion(problema, 0);
            hijo->generarHijo(padre2, padre1);
            if (rand() / (double) RAND_MAX <= probabilidad_mutacion){
                hijo->mutacionIntercambio();
            }
            nueva_generacion.pushSolucion(hijo);
        }
        else{
            hijo = new TSPSolucion(*padre1);
            if (rand() / (double) RAND_MAX <= probabilidad_mutacion){
                hijo->mutacionIntercambio();
            }
            nueva_generacion.pushSolucion(hijo);
            hijo = new TSPSolucion(*padre2);
            if (rand() / (double) RAND_MAX <= probabilidad_mutacion){
                hijo->mutacionIntercambio();
            }
            nueva_generacion.pushSolucion(hijo);   
        }
    }

    // Se cambia la peor solución por la antigua mejor:
    posicion_mejor_solucion = buscarMejor();
    posicion_peor_solucion = nueva_generacion.buscarPeor();
    delete nueva_generacion.soluciones[posicion_peor_solucion];
    nueva_generacion.soluciones[posicion_peor_solucion] = new TSPSolucion(*(soluciones[posicion_mejor_solucion]));

    // Eliminamos la antigua generación:
    liberarEspacio();

    // Asignamos la nueva generación y ponemos su numero de individuos a 0 (para que no se eliminen las soluciones al finalizar)
    this->soluciones = nueva_generacion.soluciones;
    nueva_generacion.soluciones = 0;
    nueva_generacion.soluciones_almacenadas = 0;
}

// Método que realiza una iterración del algoritmo genético, evolucionando la población en una generación:
void TSPColeccionSoluciones::evolucionarSnug(const double & probabilidad_mutacion, const int & num_candidatos){

    TSPColeccionSoluciones nueva_generacion(problema, heuristica_grasp, soluciones_almacenadas); 
    
    // Se reordenan aleatoriamente las soluciones de la generación actual; 
    random_shuffle(soluciones, soluciones+soluciones_almacenadas);

    // Los vecinos se cruzan para generar hijos: Operador de Seleccion creado por mi
    for (int i = 0; i < soluciones_almacenadas; i++){
        nueva_generacion.soluciones[i] = new TSPSolucion(problema, 0);
        nueva_generacion.soluciones[i]->generarHijo(soluciones[i], soluciones[(i+1)%soluciones_almacenadas]);
    }

    // Se comparan padres con hijos:
    for (int i = 0; i < soluciones_almacenadas; i++){
        if (*soluciones[i] < *nueva_generacion.soluciones[i]){
            delete nueva_generacion.soluciones[i];
        }
        else{
            delete soluciones[i];
            soluciones[i] = nueva_generacion.soluciones[i];
        }
    }

    // Ponemos el número de individuos de nueva_generación a 0 (para que no se eliminen las soluciones al finalizar)
    nueva_generacion.soluciones_almacenadas = 0;

    // Diversificación de la población
    ordena();
    for (int i = soluciones_almacenadas-1; i > 0; i--){
        if (*soluciones[i] == *soluciones[i-1]){
            delete soluciones[i];
            soluciones[i] = heuristica_grasp->buscarSolucion();
        }
    }
}