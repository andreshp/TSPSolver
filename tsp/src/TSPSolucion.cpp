# include "TSPSolucion.h"

                    /* MÉTODOS PRIVADOS */

// Método privado que inserta una ciudad de índice dado en la posición indicada.
// Se asume que los datos son correctos no realizando, por tanto, las comprobaciones oportunas.
void TSPSolucion::insertarCiudadPrivado(int indice_ciudad, int posicion){
    // Algoritmo de inserción:
    for (int i = num_visitadas; i > posicion; i--){
        orden_ciudades[i] = orden_ciudades[i -1];
    }

    orden_ciudades[posicion] = indice_ciudad;
    
    // Cambios en los datos miembro:
    ciudades_visitadas[indice_ciudad] = true;
    num_visitadas++;
}

// Método que devuelve el coste de recorrer las ciudades si se insertara la ciudad indice_ciudad en la posición indicada:
double TSPSolucion::nuevoCosteInsercion(int indice_ciudad, int posicion) const{    
    /* Algoritmo:
        - Se crea una variable distancia con el coste actual.
        - Se calculan las dos ciudades entre las cuales estará la ciudad a insertar. Estas son:
            - La ciudad en el lugar posicion.
            - La ciudad en el lugar posicion - 1 (si posicion > 0). En caso de que posicion = 0, la segunda ciudad vecina está en num_visitadas - 1; 
        - Se resta la distancia entre las dos ciudades anteriores a la distancia total.
        - Se suma la distancia de cada una de las dos ciudades anteriores a la ciudad a insertar.
    */

    double distancia = coste;
    int pos_insercion1 = posicion, pos_insercion2;

    pos_insercion2 = (num_visitadas + posicion - 1) % num_visitadas;
    
    distancia -= problema->elementoMatrizDistancias(orden_ciudades[pos_insercion1], orden_ciudades[pos_insercion2]);
    distancia += problema->elementoMatrizDistancias(indice_ciudad, orden_ciudades[pos_insercion1]);
    distancia += problema->elementoMatrizDistancias(indice_ciudad, orden_ciudades[pos_insercion2]);
    
    return distancia;
}

// Método que calcula el coste de una posible nueva solución que sería el resultado de intercambiar dos ciudades de posición en orden_ciudades dada.
double TSPSolucion::nuevoCosteIntercambio(int posicion1, int posicion2) const{
    /* Algoritmo:
        - Se crea una variable distancia con el coste actual.
        - Se calculan las dos ciudades vecinas a cada una de las 2 ciudades dadas, posicion_i + 1 y posicion_i - 1. 
          (Si posicion_i = 0 o posicion_i = num_visitadas - 1, la vecina estará en el extremo opuesto del array).
        - Se resta la distancia que hay entre cada ciudad dada y sus 2 vecinas a distancia.
        - Se suma la distancia que hay entre cada ciudad dada y sus 2 nuevas vecinas a distancia.
    */

    double distancia = coste;

    // Posiciones de las ciudades contiguas a las dos dadas:
    int posicion1_dcha = (posicion1 + 1) % num_visitadas;
    int posicion1_izda = (posicion1 - 1 + num_visitadas)  % num_visitadas;
    int posicion2_dcha = (posicion2 + 1) % num_visitadas;
    int posicion2_izda = (posicion2 - 1 + num_visitadas)  % num_visitadas;

    // Se restan las distancias de los lados que se eliminan (los que tienen como vértices a las ciudades a intercambiar):
    distancia -= (problema->elementoMatrizDistancias(orden_ciudades[posicion1],orden_ciudades[posicion1_izda])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion1],orden_ciudades[posicion1_dcha])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion2],orden_ciudades[posicion2_izda])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion2],orden_ciudades[posicion2_dcha]));

    // Se suman las distancias de los nuevos lados:
    distancia += (problema->elementoMatrizDistancias(orden_ciudades[posicion1],orden_ciudades[posicion2_izda])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion1],orden_ciudades[posicion2_dcha])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion2],orden_ciudades[posicion1_izda])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion2],orden_ciudades[posicion1_dcha]));
    
    /* Si la separación en orden_ciudades de ambas ciudades es 1 (num_visitadas - 1 en caso de ser la primera y la última ciudad) 
        se ha restado dos veces la distancia entre ellas y se ha sumado 0 dos veces (la distancia entre una ciudad y ella misma). 
        Por ello debemos sumar de nuevo la distancia entre ambas ciudades 2 veces: */
    int separacion = abs(posicion1 - posicion2);
    if (separacion == 1 || separacion == num_visitadas - 1){
        distancia += 2*problema->elementoMatrizDistancias(orden_ciudades[posicion1], orden_ciudades[posicion2]);
    }

    return distancia; 
}

// Método que recalcula el coste de la solución asignándole 0 y sumándole posteriormente todas las distancias:
void TSPSolucion::recalcularCoste(){
    coste = 0;
    for (int i = 1; i < num_visitadas; i++){
        coste += problema->elementoMatrizDistancias(orden_ciudades[i], orden_ciudades[i-1]);
    }

    coste += problema->elementoMatrizDistancias(orden_ciudades[0], orden_ciudades[num_visitadas - 1]);
}

// Método que reserva el espacio para todos los datos miembro:
void TSPSolucion::reservarEspacio(){
    // Se reserva el espacio para orden_ciudades y ciudades_visitadas:
    orden_ciudades = new int [num_ciudades];
    ciudades_visitadas = new bool [num_ciudades];
    
    // Se inicializan las componentes de ciudades visitadas a false:
    for (int i = 0; i < num_ciudades; i++){
        ciudades_visitadas[i] = false;      
    }
}

                        /* MÉTODOS PÚBLICOS */

// Constructor de la clase:
TSPSolucion::TSPSolucion(TSPProblema *problema, const string *algoritmo){
    //  Inicializamos algunos datos miembro y llamamos a reservarEspacio(): 
    this->problema = problema;
    this->num_ciudades = problema->numeroCiudades();
    num_visitadas = 0;
    coste = 0;
    mejora = "Ninguna";
    this->algoritmo = algoritmo; 
    this->intercambio_ciudades = false;
    
    reservarEspacio();
}

// Constructor de copia redefinido:
TSPSolucion::TSPSolucion(const TSPSolucion &solucion){
    // Copiamos todos los datos miembro y creamos los arrays necesarios en el heap, copiando las componentes de la solución dada: 
    this->problema = solucion.problema;
    this->num_ciudades = solucion.num_ciudades;
    this->num_visitadas = solucion.num_visitadas;
    this->coste = solucion.coste;
    this->mejora = solucion.mejora;
    this->algoritmo = solucion.algoritmo;
    this->intercambio_ciudades = solucion.intercambio_ciudades;
    reservarEspacio();

    for(int i = 0; i < num_ciudades; i++){
        this->orden_ciudades[i] = solucion.orden_ciudades[i];
        this->ciudades_visitadas[i] = solucion.ciudades_visitadas[i];
    }
}

TSPSolucion::TSPSolucion(TSPProblema *problema, int *recorrido, const string *algoritmo, string mejora, bool intercambio_ciudades){
    this->problema = problema;
    this->num_ciudades = problema->numeroCiudades();
    num_visitadas = num_ciudades;
    this->mejora = mejora;;
    this->algoritmo = algoritmo; 
    this->intercambio_ciudades = intercambio_ciudades;
    
    this->orden_ciudades = new int[num_ciudades];
    this->ciudades_visitadas = new bool[num_ciudades];

    for(int i = 0; i < num_ciudades; i++){
        orden_ciudades[i] = recorrido[i];
        ciudades_visitadas[i] = true;
    }

    recalcularCoste();
}

// Destructor de la clase:
TSPSolucion::~TSPSolucion(){
    delete [] orden_ciudades;
    delete [] ciudades_visitadas;
}

// Método que devuelve el índice de la ciudad visitada en la n-ésima posición:
int TSPSolucion::ciudadVisitada(int posicion) const {
    if (0 <= posicion && posicion < num_ciudades){
        return orden_ciudades[posicion];
    }
    else{
        throw logic_error("Las ciudades están ordenadas de 0 a " 
            + static_cast<ostringstream*>(&(ostringstream() << num_ciudades-1))->str());          
    }
}

// Método que determina la mejor inserción posible:
void TSPSolucion::determinarMejorInsercion(){
    /* Algoritmo:
        - Se comprueba que quedan ciudades por visitar y que ya se ha añadido la primera.
        - Se encuentra la primera ciudad no visitada y se calcula el coste de insertar la misma en la posicion 0 asignándolo a mejor_coste_insercion.
             - Empezando en la ciudad anterior, se recorren todas las ciudades hasta la ciudad de índice num_ciudades - 1:
                 - Si la ciudad actual no ha sido visitada:
                     - Se calcula el coste de insertarla en cada una de las posiciones. Si alguno de estos es menor que mejor_coste_insercion  
                        se asgina el nuevo coste a este y se hace lo propio con ciudad_mejor_insercion y mejor_posicion.
            - Se inserta ciudad_mejor_insercion en mejor_posicion y se asigna a coste el coste_mejor_insercion.
    */

    if (num_visitadas < num_ciudades && num_visitadas >= 1){
        
        // Declaración de variables:
        int ciudad_mejor_insercion, ciudad_actual, pos_actual, mejor_posicion = 0; 
        double coste_actual; 
        bool inicializado = false;

        // Inicialización:
        for (ciudad_actual = 0; ciudad_actual < num_ciudades && ! inicializado; ciudad_actual++){
            if ( ! ciudades_visitadas[ciudad_actual] ){
                ciudad_mejor_insercion = ciudad_actual;
                inicializado = true;
            }
        }

        double coste_mejor_insercion = nuevoCosteInsercion(ciudad_mejor_insercion, mejor_posicion);

        // Cálculo de la mejor insercción:
        for (ciudad_actual = ciudad_mejor_insercion; ciudad_actual < num_ciudades; ciudad_actual++){
            
            if ( ! ciudades_visitadas[ciudad_actual] ){

                for (pos_actual = 0;  pos_actual < num_visitadas; pos_actual++){
                    
                    coste_actual = nuevoCosteInsercion(ciudad_actual, pos_actual);
    
                    if (coste_actual < coste_mejor_insercion){
                        ciudad_mejor_insercion = ciudad_actual;
                        mejor_posicion = pos_actual;
                        coste_mejor_insercion = coste_actual;
                    }
                }
            }
        }
        
        insertarCiudadPrivado(ciudad_mejor_insercion, mejor_posicion);
        this->coste = coste_mejor_insercion;
    }
}

// Método que determina un intercambio de ciudades que mejore la solución. 
// Devuelve true si se ha realizado un intercambio y false si no hay un intercambio que mejore la solución:
bool TSPSolucion::determinarMejorIntercambio(){
    /* Algoritmo:
            - Se inicializa mejor_coste con el coste actual.
            - Se inicializa cambio a false.
            - Se comprueba el coste que tendría la nueva solución al intercambiar los elementos de cada una de las parejas de ciudades.
                - Si dicho coste es menor que mejor_coste, se le asigna este nuevo coste y se hace lo propio con posicion_mejor_coste i y j. 
                  Cambio pasa a true.
            - Si hay algún cambio factible (cambio==true) se hace al final.
            - Se devuelve si se ha realizado un intercambio de ciudades (return cambio).
    */

    // Declaración de variables:
    double nuevo_coste, mejor_coste = coste;
    bool cambio = false;
    int posicion_mejor_coste_i, posicion_mejor_coste_j;

    // Cálculo del mejor intercambio posible:
    for (int i = 0; i < num_visitadas; i++){
        for (int j = i + 1; j < num_visitadas; j++){  
            
            nuevo_coste = nuevoCosteIntercambio(i, j);      
            
            if (nuevo_coste < mejor_coste){
                posicion_mejor_coste_i = i;
                posicion_mejor_coste_j =  j;
                mejor_coste = nuevo_coste;
                cambio = true;
            }
        }
    }

    // Se realiza el intercambio calculado en caso de haber alguno que mejore la solución:
    if (cambio == true){
        intercambiarCiudadesPrivado(posicion_mejor_coste_i, posicion_mejor_coste_j);
        coste = mejor_coste;
    }

    return cambio;
}

// Método que determina el primer intercambio de ciudades que mejora la solución y lo realiza. 
// Devuelve true si se ha realizado un intercambio y false si no hay un intercambio que mejore la solución:
bool TSPSolucion::determinarPrimerMejorIntercambio(){
    /* Algoritmo:
            - Se inicializa cambio a false.
            - Se comprueba el coste que tendría la nueva solución al intercambiar los elementos de cada una de las parejas de ciudades.
                - Si dicho coste es menor que el coste actual se realiza el intercambio y se actualiza el coste. 
                  Cambio pasa a true y se sale del bucle.
            - Se devuelve si se ha realizado un intercambio de ciudades (return cambio).
    */

    // Declaración de variables:
    double nuevo_coste;
    bool cambio = false;

    // Si se encuentra algún intercambio que mejore la solución se realiza:
    for (int i = 0; i < num_visitadas && ! cambio; i++){
        for (int j = i + 1; j < num_visitadas && ! cambio; j++){  
            
            nuevo_coste = nuevoCosteIntercambio(i, j);      
            
            if (nuevo_coste < coste){
                intercambiarCiudadesPrivado(i, j);
                coste = nuevo_coste;
                cambio = true;
            }
        }
    }

    return cambio;
}

// Método que determina la siguiente ciudad a añadir según el criterio del vecino más cercano y la añade.
// Si la solución ya contiene a todas las ciudades no se hace nada.
void TSPSolucion::determinarVecinoMasCercano(){
    
    /* Algoritmo:
            - Se comprueba que quedan ciudades por visitar y que ya se ha añadido la primera.
            - En caso afirmativo, se toma la última ciudad añadida y la primera ciudad no visitada, que inicializará vecino más cercano.
                - Por cada ciudad no visitada se comprueba si la distancia entre esta y la última ciudad añadida es menor que la de vecino_mas_cercano.
                    - En caso afirmativo, se le asigna esta ciudad a vecino más cercano.
            - Se añade vecino más cercano y se modifica el coste de la solución.
    */

    if (num_visitadas < num_ciudades && num_visitadas >= 1){
        
        // Declaración de variables:
        int ultima_ciudad = orden_ciudades[num_visitadas - 1];
        double nueva_distancia;
        int vecino_mas_cercano = -1;

        // Inicialización de vecino_mas_cercano:
        for (int i = 0; vecino_mas_cercano == -1; i++){
            if (ciudades_visitadas[i] == false){
                vecino_mas_cercano = i;
            }
        }

        // Inicialización de menor_distancia:
        double menor_distancia = problema->elementoMatrizDistancias(ultima_ciudad, vecino_mas_cercano);
        
        // Se comprueba cuál es el vecino_mas_cercano:
        for (int i = vecino_mas_cercano; i < num_ciudades; i++){
            if (ciudades_visitadas[i] == false){
                nueva_distancia =  problema->elementoMatrizDistancias(ultima_ciudad, i);
                if (nueva_distancia < menor_distancia){
                    vecino_mas_cercano = i;
                    menor_distancia = nueva_distancia;
                }
            }
        }
        
        // Se recalcula el coste:
        coste += menor_distancia;
        coste -= problema->elementoMatrizDistancias(ultima_ciudad, orden_ciudades[0]);
        coste += problema->elementoMatrizDistancias(vecino_mas_cercano, orden_ciudades[0]);
        // Se añade la ciudad al recorrido:
        insertarCiudadPrivado(vecino_mas_cercano, num_visitadas);
    }
}

// Método que determina la siguiente ciudad a añadir (y la añade) de forma aleatoria entre las 5 ciudades más cercanas a la última añadida.
// Si la solución ya contiene a todas las ciudades no se hace nada.
void TSPSolucion::determinarVecinoGRASP(const double indice_validez){
    
    /* Algoritmo:
            - Se comprueba que quedan ciudades por visitar y que ya se ha añadido la primera.
            - En caso afirmativo, se toma la última ciudad añadida como ultima_ciudad. 
              Hablaremos en términos de distancias a esta ciudad:
                - Se inicializa lista_mas_cercanos la primera ciudad no visitada y su distancia inicializa distancia_tope.
                - Por cada ciudad no visitada se inserta en lista_mas_cercanos si tiene distancia menor que distancia tope.
                    - Si se inserta una ciudad, distancia tope se inicializa como indice_validez por la mejor distancia actual.
                - Se eliminan las ciudades de lista_mas_cercanos que hayan entrado pero ahora no entren dentro de distancia_tope.
                - Se escoge aleatoriamente una ciudad de lista_mas_cercanos, añadiéndose a la solución y modificándose el coste de la misma.
    */

    if (num_visitadas < num_ciudades && num_visitadas >= 1){
        
        // Declaración de variables:
        int ultima_ciudad = orden_ciudades[num_visitadas - 1];
        double nueva_distancia, distancia_tope;
        int *lista_mas_cercanos = new int [num_ciudades - num_visitadas];
        int vecino, j, elementos_lista = 0;

        // Inicialización de lista_mas_cercanos:
        for (vecino = 0; elementos_lista < 1 && vecino < num_ciudades; vecino++){
            if (ciudades_visitadas[vecino] == false){
                lista_mas_cercanos[0] = vecino;
                elementos_lista++;             
            }
        }

        distancia_tope = problema->elementoMatrizDistancias(lista_mas_cercanos[0], ultima_ciudad);

        // Rellenamos lista_mas_cercanos:
        for (; vecino < num_ciudades; vecino++){
            
            if (ciudades_visitadas[vecino] == false){
                
                nueva_distancia = problema->elementoMatrizDistancias(vecino, ultima_ciudad);
                
                if (nueva_distancia < distancia_tope){

                    for(j = elementos_lista; j > 0 && nueva_distancia < 
                        problema->elementoMatrizDistancias(lista_mas_cercanos[j-1], ultima_ciudad); j--){
                        lista_mas_cercanos[j] = lista_mas_cercanos[j-1];
                    }
    
                    lista_mas_cercanos[j] = vecino;
                    elementos_lista++;             
                    distancia_tope = indice_validez * problema->elementoMatrizDistancias(lista_mas_cercanos[0], ultima_ciudad);
                }
            }
        }

        // Se toman solo las ciudades dentro del rango de distancia_tope. Así se evitan los arcos largos.
        // Si hay un arco mucho mejor que los demás siempre se cogerá.
        // Solo se aplicará la aleatoriedad en el caso de que haya muchos arcos en un intervalo aceptable. 
        for (;problema->elementoMatrizDistancias(lista_mas_cercanos[elementos_lista-1], ultima_ciudad) > distancia_tope; elementos_lista--);
        
        // Se escoge una solución aleatoria entre las soluciones de lista_mas_cercanos y se añade a la solución:
        int elegido = lista_mas_cercanos[rand() % elementos_lista];
        
        coste -= problema->elementoMatrizDistancias(ultima_ciudad, orden_ciudades[0]);
        coste += problema->elementoMatrizDistancias(ultima_ciudad, elegido);
        coste += problema->elementoMatrizDistancias(elegido, orden_ciudades[0]);
        insertarCiudadPrivado(elegido, num_visitadas);
        delete [] lista_mas_cercanos;
    }
}

// Método que realiza un número de iteraciones dado del algoritmo simulated annealing a cierta temperatura dada.
void TSPSolucion::realizarIteracionesSA(const double temperatura, const int num_iteraciones, const int max_exitos){
    /* Algoritmo: 
        - Se realizan num_iteraciones del siguiente proceso (o hasta que exitos sea max_exitos):    
            - Se calcula el coste de un vecino aleatorio de la solución (intercambiar dos ciudades de posición).
            - Si dicho coste es menor que el actual se acepta el vecino (se realiza el cambio) y exitos++.
            - En caso contrario, se calcula la probabilidad de que sea aceptado como la exponencial de la diferencia de costes de la solución actual y su vecino entre la temperatura.
            - Si un número aleatorio entre 0 y 1 es menor que dicha probabilidad entonces se acepta el vecino como solución actual y exitos++.
    */ 
    int exitos = 0;
    for (int i = 0; i < num_iteraciones && exitos < max_exitos; i++){
        // Se calcula el coste de un vecino aleatorio:
        int pos1 = rand() % num_ciudades;
        int pos2 = rand() % num_ciudades;
        double nuevo_coste = nuevoCosteIntercambio(pos1, pos2);
            
        // Se decide si se acepta dicho vecino o no:
        if (nuevo_coste < coste || rand()/(double)RAND_MAX <=  exp((coste - nuevo_coste) / temperatura)){
            intercambiarCiudadesPrivado(pos1, pos2);
            coste = nuevo_coste;
            exitos++;   
        }
    }
}

// Método que si quedan ciudades por visitar añade una de ellas aleatoriamente:
void TSPSolucion::pushCiudadAleatoria(){
    
    if (num_visitadas < num_ciudades){
        int i = rand()%num_ciudades;
    
        for (; ciudades_visitadas[i] == true; i = (i+1)%num_ciudades);

        ciudades_visitadas[i] = true;
        orden_ciudades[num_visitadas] = i;
        num_visitadas++;
    }
}

// Método que construye la solución a partir de los padres mediante el algoritmo de cruce OX:
void TSPSolucion::generarHijo(TSPSolucion *padre1, TSPSolucion *padre2){

    int i = rand() % num_ciudades;
    int j = rand() % num_ciudades;
    int k = i;

    // Se añade una subcadena aleatoria de padre1 al inicio de la solución:
    for (; k != j; k = (k+1)%num_ciudades){
        this->orden_ciudades[num_visitadas] = padre1->orden_ciudades[k];
        this->ciudades_visitadas[this->orden_ciudades[num_visitadas]] = true;
        this->num_visitadas++;
    }

    this->orden_ciudades[num_visitadas] = padre1->orden_ciudades[j];
    this->ciudades_visitadas[this->orden_ciudades[num_visitadas]] = true;
    this->num_visitadas++;

    // Encontramos orden_ciudades[j] en padre2:
    for (k = 0; padre2->orden_ciudades[k] != padre1->orden_ciudades[j]; k++);

    // Rellenamos la solución con las ciudades no visitadas en el orden en el que se encuentran a partir de k en padre2:
    for (k = (k+1) % num_ciudades; num_visitadas < num_ciudades; k = (k+1) % num_ciudades){
        
        if (! this->ciudades_visitadas[padre2->orden_ciudades[k]]){

            this->ciudades_visitadas[padre2->orden_ciudades[k]] = true;
            this->orden_ciudades[num_visitadas] = padre2->orden_ciudades[k];
            num_visitadas++;
        }
    }

    this->algoritmo = padre1->algoritmo;
    recalcularCoste();
}

// Método que produce una mutación aleatoria en la solución dada intercambiando dos ciudades:
void TSPSolucion::mutacionIntercambio(){
    int i = rand() % num_ciudades;
    int j = (i + (1 + rand() % (num_ciudades-1))) % num_ciudades; // j != i
    
    this->coste = nuevoCosteIntercambio(i, j);
    intercambiarCiudadesPrivado(i, j);
}

// Método que produce una mutación aleatoria en la solución dada insertando una ciudad de orden_ciudades en otra posición:
void TSPSolucion::mutacionInsercion(){
    int i = rand() % num_ciudades;
    int j = (i + (1 + rand() % (num_ciudades-2))) % num_ciudades; // j != i y j!= i -1
    int ciudad_insertar = orden_ciudades[i];
    
    // Posiciones de las ciudades contiguas a las dos dadas:
    int posicion1_dcha = (i + 1) % num_visitadas;
    int posicion1_izda = (i - 1 + num_visitadas)  % num_visitadas;
    int posicion2_dcha = (j + 1) % num_visitadas;
    int posicion2_izda = (j - 1 + num_visitadas)  % num_visitadas;
    
    int separacion = i-j;
    
    if (separacion != -1){
        // Se restan las distancias de los lados que se eliminan (los que tienen como vértices a las ciudades a intercambiar):
        coste -= (problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[posicion1_izda])
                + problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[posicion1_dcha])
                + problema->elementoMatrizDistancias(orden_ciudades[j],orden_ciudades[posicion2_dcha]));

        // Se suman las distancias de los nuevos lados:
        coste += (problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[j])
                + problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[posicion2_dcha])
                + problema->elementoMatrizDistancias(orden_ciudades[posicion1_izda],orden_ciudades[posicion1_dcha]));    
    }
    else{
        // Se restan las distancias de los lados que se eliminan (los que tienen como vértices a las ciudades a intercambiar):
        coste -= (problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[posicion1_izda])
                + problema->elementoMatrizDistancias(orden_ciudades[j],orden_ciudades[posicion2_dcha]));

        // Se suman las distancias de los nuevos lados:
        coste += (problema->elementoMatrizDistancias(ciudad_insertar, orden_ciudades[posicion2_dcha])
                + problema->elementoMatrizDistancias(orden_ciudades[j], orden_ciudades[posicion1_izda])); 
    }

    int siguiente = i;

    for (int k = i; k != j; k = siguiente){
        siguiente = (siguiente + 1) % num_ciudades;
        orden_ciudades[k] = orden_ciudades[siguiente];
    }
    
    orden_ciudades[j] =  ciudad_insertar;
}

// Método que produce una mutación aleatoria en la solución dada:
void TSPSolucion::mutacion(){
    int i = rand() % num_ciudades;
    int j = (i + (1 + rand() % (num_ciudades-1))) % num_ciudades; // j != i
    int posicion_intercambio, diferencia;

    // Se utiizan módulos sin depender del signo para que laa mutacion pueda afectar a los 2 extremos del array:
    if (j < i){
        diferencia = num_ciudades - abs(i - j) + 1;    
    }
    else{
        diferencia = abs(i - j) + 1;
    }

    // Reordenamos aleatoriamente los elementos entre i y j:
    for (int k = i; k != j; k = (k+1)%num_ciudades){
        posicion_intercambio = (i + (rand() % diferencia)) % num_ciudades;
        intercambiarCiudadesPrivado(k, posicion_intercambio); 
    }

    recalcularCoste();
}

// Método público que inserta una ciudad de índice dado en la posición indicada:
// Se comprueba que los datos son correctos:
void TSPSolucion::insertarCiudad(int indice_ciudad, int posicion){

    /* Si posicion satisface las condiciones necesarias (es mayor o igual que 0 y es menor o igual que num_visitadas), 
       el índice es correcto y hay espacio para insertar (num_visitadas < num_ciudades) entonces llamamos al método 
       privado que inserta una ciudad. En caso contrario se lanza una excepción: 
    */
    if (num_visitadas > 0 && num_visitadas < num_ciudades && 0 <= indice_ciudad && indice_ciudad < num_ciudades &&  
        0 <= posicion && posicion < num_ciudades){

        coste = nuevoCosteInsercion(indice_ciudad, posicion);
        insertarCiudadPrivado(indice_ciudad, posicion);
    }
    else if (num_visitadas == 0 && posicion == 0){
        
        orden_ciudades[posicion] = indice_ciudad;
        num_visitadas++;
        ciudades_visitadas[indice_ciudad] = true;
    }
    else{
        throw logic_error("Posición de inserción errónea (debe ser entre 0 y " 
            + static_cast<ostringstream*>(&(ostringstream() << num_visitadas))->str() + ")");
    }
}

// Método público que devuelve una nueva solución en la que están intercambiadas dos ciudades de posición dada en orden_ciudades.
// Se comprueba que los datos son correctos:
TSPSolucion *TSPSolucion::intercambiarCiudades(int posicion1, int posicion2){

    if (posicion1 >= 0 && posicion2 >= 0 && posicion1 < num_ciudades && posicion2 < num_ciudades){      

        // Se crea una nueva solución copia de la actual:
        TSPSolucion *nueva_solucion = new TSPSolucion(*this);
        // Se intercambian las ciudades y se asigna el nuevo coste.
        nueva_solucion->coste = nuevoCosteIntercambio(posicion1, posicion2);
        nueva_solucion->intercambiarCiudadesPrivado(posicion1, posicion2);
        nueva_solucion->intercambio_ciudades = true;
        return nueva_solucion;
    }
    else{
        throw logic_error("No se pueden intercambiar las ciudades, las posiciones deben estar entre 0 y " 
            + static_cast<ostringstream*>(&(ostringstream() << num_visitadas - 1))->str() + ".\n");
    }
}


// Método que imprime los índices de las ciudades en el orden propuesto por solucion.
void TSPSolucion::imprimirSolucion() const{
    // Se recorren todas las ciudades:
    for (int i = 0; i < num_ciudades; i++){
        cout  << orden_ciudades[i] << " ";
    }
    
    cout << endl;
}