#include "Menu.h"

                /* MÉTODOS PÚBLICOS */

//Constructor de la clase:
Menu::Menu(TSPProblema *nuevo_problema)
    :heuristica_insercion(nuevo_problema), heuristica_vecino(nuevo_problema),
    heuristica_grasp(nuevo_problema, &mejora_local), heuristica_ils(nuevo_problema, &mejora_local), simulated_annealing(nuevo_problema), 
    generador_aleatorio(nuevo_problema), heuristica_genetico(nuevo_problema, &generador_aleatorio, &heuristica_grasp, &mejora_local),
    heuristica_hormiga(nuevo_problema), soluciones(nuevo_problema, &heuristica_grasp),
    problema(nuevo_problema), plotter(nuevo_problema), iotsp(nuevo_problema,&soluciones), nivel(1),solucion_bb(nuevo_problema)
{}
    
//Método para comprobar la validez del valor introducido.
double Menu::compruebaOpcion(string opcion){
    bool negativo = false;
    bool es_correcto = true;
    bool es_decimal = false;
    int i = 0;
    double valor = 0;
    int size = opcion.size();
    int pos_decimal = 0;

    //Se comprueba el signo del valor introducido.
    if(opcion[0] == '-'){
        negativo = true;
        i++;
    }

    //Se comprueba que todas las cifras son numéricas, y en su caso, se va formando el número con dichas cifras.
    for(; es_correcto && i < size; i++){
        

        es_correcto = (opcion[i] >= '0' && opcion[i] <= '9');
        
        if(es_correcto){
            if(!es_decimal){
                valor = valor * 10 + (int)(opcion[i] - '0');
            }
            else{
                valor  = valor + (opcion[i]-'0')*pow(10,pos_decimal);
            }
        }

        if(!es_correcto){
            es_correcto = es_decimal = opcion[i] == '.' && !es_decimal;
        }
        if(es_decimal){
            pos_decimal--;
        }
    }

    //Se añade el signo.
    if(negativo){
        valor = -valor;
    }

    //Si se encontró un carácter incorrecto se lanza una excepción.
    if(!es_correcto){
        throw logic_error("Se esperaba un valor entero.\n");
    }

    return valor;
}

// Método para imprimir los distintos menús.
void Menu::showOptions() const{
	switch(nivel){
        case 1:
        {
            cout << "\nElija el algoritmo que desea utilizar para construir su solución:"
             << "\n1. Algoritmo heurístico de Mejor Inserción."
             << "\n2. Algoritmo heurístico del Vecino más Cercano."
             << "\n3. Búsqueda exhaustiva. Todos los algoritmos anteriores empezando en todas las ciudades y sus correspondientes mejoras."
             << "\n4. GRASP (Greedy Randomized Adaptative Search Process)."
             << "\n5. ILS (Iterative Local Search)"
             << "\n6. SA (Simulated Annealing)"
             << "\n7. GA (Genetic Algorithm y Snug Genetic Algorithm)."
             << "\n8. ACOTSP (Ants Colony Optimization, Optimización de la Colonia de Hormigas simplificado)."
             << "\n9. Mis soluciones."
             << "\n10. Información."
             << "\n11. Ajuste de parámetros de los algoritmos."
             << "\n12. ¡NEW! Resolución Branch and Bound (β 1.0)"
             << "\n-1. Salir del programa."
             << "\n\n";
            break;
        }
        case 2:
	    {
		    cout << "\nElija la operación que desea utilizar sobre la solución obtenida:"
		     << "\n1. Ver el recorrido de la solución."
             << "\n2. Ver la distancia total del recorrido."
		     << "\n3. Mejora local de la solución con el algoritmo 2-Opt."
		     << "\n4. Intercambiar ciudades en el recorrido."
             << "\n5. Dibujar solución."
		     << "\n0. Volver al inicio."
		     << "\n-1. Salir del programa"
		     << "\n\n";
	        break;
        }

        case 3:
        {
            cout << "\nElija la opción que desea realizar sobre las soluciones ya obtenidas:"
             << "\n1. Ver historial de soluciones."
             << "\n2. Obtener información sobre una solución."
             << "\n3. Acceder a una solución."
             << "\n4. Acceder a la mejor solución."
             << "\n5. Eliminar todas las soluciones menos las n primeras."
             << "\n6. Dibujar una solución."
             << "\n7. Imprimir una solución."
             << "\n8. Imprimir la lista de soluciones."
             << "\n9. Cargar soluciones."
             << "\n0. Volver al inicio."
             << "\n-1. Salir del programa."
             << "\n\n";
            break;
        }
        case 4:
        {
            cout << "\nIntroduzca el índice del algoritmo del que desea ver su información y ajustar sus parámetros:" 
             << "\n1. Algoritmo heurístico de Mejor Inserción."
             << "\n2. Algoritmo heurístico del Vecino más Cercano."
             << "\n3. Local Search."
             << "\n4. GRASP (Greedy Randomized Adaptative Search Process)."
             << "\n5. ILS (Iterative Local Search)."
             << "\n6. SA (Simulated Annealing)."
             << "\n7. GA (Genetic Algorithm y Snug Genetic Algorithm)."
             << "\n8. ACOTSP (Ants Colony Optimization)."
             << "\n0. Volver al inicio."
             << "\n-1. Salir del programa."
             << "\n\n";
            break;
        }
    }
}

// Método para leer la opción deseada de los distintos menús y ejecutarla:
int Menu::readOption(){
	cout << "Introduzca la opción deseada: ";
    string cadena_entrada;
    int opcion;
	cin >> cadena_entrada;
    opcion = compruebaOpcion(cadena_entrada);

    switch(nivel){
        case 1:
        {
            realizarOpcionMenuPrincipal(opcion);
            break;
        }
        case 2:
        {
            realizarOpcionMenuIndividual(opcion);
            break;
        }
        case 3:
        {
            realizarOpcionHistorial(opcion);
            break;
        }
        case 4:
        {
            realizarOpcionMenuAjusteParametros(opcion);
            break;
        }
    }

    // Se devuelve la opción que se ha escogido (para poder salir del bucle en caso de -1):
    return opcion;
}

// Método que ejecuta una opción del menú principal:
void Menu::realizarOpcionMenuPrincipal(int opcion){
    string cadena_entrada;
    switch(opcion){
        case 1:
        {   // Se calcula la solución mediante la clase TSPMejorInsercion:
            crono.start();
            solucion_actual = heuristica_insercion.obtenerSolucion();
            soluciones.insertarSolucion(solucion_actual);
            
            // Se imprime la solución calculada:
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;
            
            break;
        }
        case 2:
        {   // Se calcula la solución mediante la clase TSPVecinoMasCercano:
            crono.start();                
            solucion_actual = heuristica_vecino.obtenerSolucion();
            soluciones.insertarSolucion(solucion_actual);
            
            // Se imprime la solución calculada:
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;

            break;
        }
        case 3:
        {   // Se calculan todas las soluciones posibles con nuestros algoritmos y sus mejoras:
            crono.start();
            int num_ciudades = problema->numeroCiudades();
            
            // Soluciones mediante insercción:
            for (int i = 0; i < num_ciudades; i++){
                solucion_actual = heuristica_insercion.resolver(i);
                soluciones.pushSolucion(solucion_actual);
                solucion_actual = mejora_local.obtenerSolucionMejorada(solucion_actual);
                soluciones.pushSolucion(solucion_actual);
            }

            // Soluciones mediante vecino más cercano:
            for (int i = 0; i < num_ciudades; i++){
                solucion_actual = heuristica_vecino.resolver(i);
                soluciones.pushSolucion(solucion_actual);
                solucion_actual = mejora_local.obtenerSolucionMejorada(solucion_actual);
                soluciones.pushSolucion(solucion_actual);
            }
                
            soluciones.ordena();

            cout << "\nSe han añadido todas las soluciones calculadas a \"Mis Soluciones\". \n";
            crono.message();
            cout << endl;
            
            break;
        }
        case 4:
        {   // Se calcula varias solucies mediante la clase TSPGRASP:       
            // Se lee el número de soluciones:
            int num_soluciones;
            cout << "\nIntroduzca el número de soluciones a generar: ";
            cin >> cadena_entrada;
            num_soluciones = compruebaOpcion(cadena_entrada);
        
            crono.start();
    
            // Se calculan las soluciones y se añaden al historial:
            for (int i = 0; i < num_soluciones; i++){
                solucion_actual = heuristica_grasp.buscarSolucionLocalSearch();
                soluciones.pushSolucion(solucion_actual);
            }
            soluciones.ordena();
            
            cout << "\nSe han añadido todas las soluciones calculadas a \"Mis Soluciones\". \n";
            crono.message();
            cout << endl;
            
            break;
        }
        case 5:
        {   //Se obtiene una solución mediante la clase TSPILS
            cout << "\nIntroduzca el número de iteraciones deseadas: ";
            cin >> cadena_entrada;
            int iteraciones = compruebaOpcion(cadena_entrada);
            
            crono.start();
            
            if (soluciones.numeroSoluciones() == 0){
                solucion_actual = heuristica_vecino.obtenerSolucion();
                soluciones.pushSolucion(solucion_actual);
            }
            else{
                solucion_actual = soluciones.solucionPosicion(1);
            }
                    
            solucion_actual = heuristica_ils.obtenerSolucion(solucion_actual,iteraciones);
            soluciones.insertarSolucion(solucion_actual);
            
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;   
                    
            break;
        }
        case 6:
        {   //Se obtiene una solución mediante la clase TSPSA
            cout << "\nIntroduzca el número de iteraciones deseadas: ";
            cin >> cadena_entrada;
            int iteraciones = compruebaOpcion(cadena_entrada);
            
            crono.start();
    
            // Se toma una nueva solución o la mejor solución para pasarla como parámetro:
            if (soluciones.numeroSoluciones() == 0){
                solucion_actual = heuristica_vecino.obtenerSolucion();
                soluciones.pushSolucion(solucion_actual);
            }
            else{
                solucion_actual = soluciones.solucionPosicion(1);
            }
            
            // Se aplica Simulated Annealing para obtener una nueva solución:
            solucion_actual = simulated_annealing.obtenerSolucion(solucion_actual,iteraciones);
            soluciones.insertarSolucion(solucion_actual);
            
            // Imprimimos la solución, el tiempo que se ha tardado en encontrarla y accedemos al nivel que se encarga de dicha solucón:
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;   
            
            break;
        }
        case 7:
        {   // Ejecución del GA:
            cout << "\nIntroduzca 0 para ejecutar el GA tradicional.";
            cout << "Introduzca 1 para ejecutar Snug GA: ";
            cin >> cadena_entrada;
            int algoritmo = compruebaOpcion(cadena_entrada);
            cout << "\nIntroduzca el número de generaciones: ";
            cin >> cadena_entrada;
            int generaciones = compruebaOpcion(cadena_entrada);
            
            crono.start();
            
            if (algoritmo == 0){
                solucion_actual = heuristica_genetico.buscarSolucion(generaciones);                
            }    
            else{
                solucion_actual = heuristica_genetico.buscarSolucionSnug(generaciones);
            }

            soluciones.insertarSolucion(solucion_actual);
            
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;   
            
            break;
        }
        case 8:
        {
            //Se emplea el algoritmo de las hormigas para obtener una solución.
            cout << "\nIntroduzca el número de viajes a realizar por las hormigas: ";
            cin >> cadena_entrada;
            int iteraciones = compruebaOpcion(cadena_entrada);
    
            crono.start();
    
            solucion_actual = heuristica_hormiga.obtenerSolucion(iteraciones);
            soluciones.insertarSolucion(solucion_actual);
    
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
    
            crono.message();
            cout << endl;
            nivel++;
    
            break;
        }
        case 9:
        {   // Se accede a "Mis Soluciones":
            nivel = 3;
            cout << "\nAccediendo a Mis Soluciones...\n\n";
            
            break;
        }
        case 10:
        {    // Se da una serie de inormación sobre el programa:
            cout << "\nVersión del programa: 17.0\n";
            cout << "Se está ejecutando sobre el fichero: " << problema->nombreProblema() << endl << endl;
            cout << "  - Inserción: Algoritmo constructivo que va insertando las ciudades libres en la solución de forma óptima.\n";
            cout << "    La calidad de la solucíón dada depende del problema pero no suele ser muy buena.\n\n";
            cout << "  - Vecino Más Cercano: Algoritmo constructivo de tipo Greedy. Construye la solución eligiendo cada vez la\n";
            cout << "    ciudad no visitada más cercana a la última añadida. El problema es que no se puedeN elegir los dos últimos\n";
            cout << "    arcos, pudiendo dar en consecuencia una mala solución. Es muy rápido y un buen punto de partida sobre el\n";
            cout << "    que aplicar otros algoritmos.\n\n";
            cout << "  - Local Search: Algoritmo de mejora local que encuentra un óptimo cercano a la solución dada. Hemos implementado\n";
            cout << "    el algoritmo 2-OPT que comprueba si hay algún intercambio de ciudades que mejore la solución y lo realiza,\n";
            cout << "    repitiendo el proceso hasta que no sea posible mejorarla. El problema es que solo ejecuta movimientos que\n";
            cout << "    mejoren la solución y puede llegar a un punto donde para mejorar la solución haya antes que empeorarla.\n";
            cout << "    Además, en problemas con  muchas ciudades se vuelve muy lento, lo que influye en los algoritmos que lo usan.\n\n";
            cout << "  - GRASP: Algoritmo constructivo que a la hora de añadir la siguiente solución genera una lista con las ciudades\n";
            cout << "    más cercanas a la última añadida y elige de ahí una aleatoria. Posteriormente se mejora la solución con la\n";
            cout << "    Local Search. La idea es crear muchas soluciones de manera que alguna de ellas encuentre un óptimo local\n";
            cout << "    bastante bueno debido a que, por la aleatoriedad, estas se encuentran esparcidas en el espacio de soluciones.\n\n";
            cout << "  - ILS: Algoritmo que, dada una solución, le aplica una mutación y Local Search de forma iterativa.\n";
            cout << "    La mutación permite escapar del óptimo local y buscar así mejores soluciones. Funciona muy bien con problemas \n";
            cout << "    de alrededor de 50 ciudades pero a partir de 100 se vuelve muy lento. Se recomiendan 1000 iteraciones\n\n";
            cout << "  - SA: Algoritmo que simula el proceso de recocido en los metales para mejorar una solución dada.\n";
            cout << "    Aplica la misma idea de la Local Search pero introduce cierta probabilidad de aceptar soluciones peores.\n";
            cout << "    Así escapa de los óptimos locales. Dicha probabilidad disminuye con el tiempo. Su rendimiento depende mucho\n";
            cout << "    de los parámetros que rigen su funcionamiento. Se han establecido de forma que funcione con problemas de \n";
            cout << "    cualquier tamaño. Funciona mucho mejor que los anteriores cuando el problema tiene 100 o más ciudades.\n";
            cout << "    Se recomiendan entre 40000 y 100000 iteraciones.\n\n";
            cout << "  - GA: Algoritmo Genético. Genera una población de individuos y los evoluciona generacionalmente\n";
            cout << "    creando hijos con el OX1 crossover y aplicando una mutación aleatoria. Se proporciona además un modelo desarrollado\n";
            cout << "    por Andrés Herrera y Francisco Herrera que realiza una diversificación voraz de la población junto a un operador de\n";
            cout << "    cruce aleatorio y competición entre padres e hijos de Differential Evolution. La diversificación voraz se realiza\n";
            cout << "    sustituyendo las soluciones repetidas en la población por nuevas soluciones obtenidas mediante un algoritmo voraz aleatorizado.\n";
            cout << "  - ACOTSP: Optimización de la Colonia de Hormigas. Las hormigas se guían por feromonas, con unas ciertas probabilidades.\n";
            cout << "    Las feromonas se van evaporando mientras las hormigas siguen haciendo recorridos y soltando nuevas feromonas. De esta\n";
            cout << "    forma, van ganando importancia las feromonas de las hormigas que hacen los caminos más cortos mientras las demás van\n";
            cout << "    desapareciendo, convergiendo así a una solución óptima. Este algoritmo, aún en desarrollo, no es de los más rápidos,\n";
            cout << "    pero es bastante potente, consiguiendo en 1000 iteraciones soluciones muy buenas. Los parámetros permiten controlar\n";
            cout << "    el grado de aleatoriedad del movimiento de las hormigas, el número de hormigas y la posibilidad de hacer mejoras\n";
            cout << "    locales, pudiendo adaptarlo a diferentes problemas del TSP que suelen estancar las heurísticas en óptimos locales.\n\n";
            cout << "La opción 'Mis Soluciones' se encarga de gestionar las soluciones creadas y proporciona diferentes operaciones.\n";
            cout << "Se dispone, además, de un menú con opciones para una solución en particular. Se puede acceder a él al crear la\n";
            cout << "solución mediante un algoritmo o desde 'Mis Soluciones'.\n\n";
            cout << "Se utiliza GNUPlot para dibujar las soluciones. Instalar mediante la orden 'sudo apt-get install gnuplot rlwrap'.\n\n";
            cout << "                          Autores: Juan Luis Suárez Díaz  y Andrés Herrera Poyatos.\n";
            cout << "                                     Este software se encuentra bajo licencia MIT.\n\n";
                         
            cout << endl; 
            break;
        }
        case 11:
        {   
            cout << "\nAccediendo al menú correspondiente...\n\n";
            nivel = 4;
            break;
        }
        case 12:{
            crono.start();
            pair<long long, long long> recs = solucion_bb.resolver();
            solucion_actual = solucion_bb.obtenerSolucion();
            soluciones.insertarSolucion(solucion_actual);
            
            // Se imprime la solución calculada:
            cout << "\nNodos recorridos: " << recs.first << endl;
            cout << "\nSoluciones recorridas: " << recs.second << endl;
            cout << "\nSolución al problema:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;
            nivel++;
            
            break;
        }
        case -1:
        {   //Cierra el programa.
            break;
        }
        default:
        {   // Si no se ha elegido una opción dentro del rango dado:
            cout << "\nNo existe la opción elegida, pruebe de nuevo." << endl << endl;
            break;
        }
    }
}

// Método que ejecuta una opción del menú individual para una sola ciudad:
void Menu::realizarOpcionMenuIndividual(int opcion){
    string cadena_entrada;
    switch(opcion){
        case 1:
        {   //Se imprime el recorrido de la solución actual:
            cout << "\nSolución actual:\n";
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            break;
        }
        case 2:
        {   // Se imprime el coste de la solución actual:
            cout << "\nCoste de la solución actual: "<< solucion_actual->distanciaTotal() << endl << endl;
            
            break;
        }
        case 3:
        {   // Se mejora la solución:
            crono.start();

            // Se toma una nueva solución con la anterior mejorada:
            solucion_actual = mejora_local.obtenerSolucionMejorada(solucion_actual);
            soluciones.insertarSolucion(solucion_actual);
            
            // Se imprime la solución y el tiempo que se ha tardado:
            cout << "\nSolución Mejorada:" << endl;
            solucion_actual->imprimirSolucion();
            cout << endl;
            
            crono.message();
            cout << endl;

            break;
        }
        case 4:
        {   // Intercambiamos las dos ciudades dadas en solucion_actual:
            // Se leen las posiciones de las ciudades a intercambiar:
            int posicion1, posicion2;
            cout << "\nIntroduzca la posicion de la primera ciudad: ";
            cin >> cadena_entrada;
            posicion1 = compruebaOpcion(cadena_entrada);
            cout << "Introduzca la posicion de la segunda ciudad: ";
            cin >> cadena_entrada;
            posicion2 = compruebaOpcion(cadena_entrada);

            // Se crea una nueva solución con las ciuades intercambiadas:
            solucion_actual = solucion_actual->intercambiarCiudades(posicion1, posicion2);
            soluciones.insertarSolucion(solucion_actual);

            // Imprimimos la nueva solución:
            cout << "\nNueva solución: " << endl;
            solucion_actual->imprimirSolucion();
            
            break;
        }
        case 5:
        {   // Se dibuja la solución actual:
            plotter.plot(solucion_actual);
            
            break;
        }
        case 0:
        {   // Volvemos al nivel principal:
            cout << "\nVolviendo al menú principal... \n\n";
            nivel =  1;
            
            break;
        }
        case -1:
        {   //Cierra el programa.
            break;
        }
        default:
        {   // Si no se ha elegido una opción dentro del rango dado:
            cout << "\nNo existe la opción elegida, pruebe de nuevo." << endl << endl;
            
            break;
        }
    }
}

// Método que ejecuta una opción del historial:
void Menu::realizarOpcionHistorial(int opcion){
    string cadena_entrada;
    switch(opcion){
        case 1:
        {   //Se imprime la lista de soluciones obtenidas.
            cout << endl;
            soluciones.imprimirHistorial();
            
            break;
        }
        case 2:
        {   //Se imprime la información de una solución en concreto.
            int indice;
            cout << "\nIntroduzca la posición que ocupa la solución por su coste: ";
            cin >> cadena_entrada;
            indice = compruebaOpcion(cadena_entrada);

            soluciones.imprimirInformacionSolucion(indice);
            cout << endl;
            
            break;
        }
        case 3:
        {   //Se carga una solución para trabajar con ella en el menú de soluciones.
            // Se lee su índice correspondiente:
            int indice;
            cout << "\nIntroduzca la posición que ocupa la solución por su coste: ";
            cin >> cadena_entrada;
            indice = compruebaOpcion(cadena_entrada);
            
            // Se carga la solucion:
            solucion_actual = soluciones.solucionPosicion(indice);
            cout << "\nSe ha cargado la solución.\n\n";
            nivel = 2;
            
            break;
        }
        case 4:
        {   //Se accede a la mejor solución para trabajar con ella en el menú de soluciones.
            solucion_actual = soluciones.solucionPosicion(1);
            cout << "\nSe ha cargado la solución.\n\n";
            nivel = 2;
            
            break;
        }
        case 5:
        {   //Borra de la memoria todas las soluciones menos las n primeras que se deseen.
            int primeras;
            cout << "\nIntroduzca el número de ciudades que desea mantener: ";
            cin >> cadena_entrada;
            primeras = compruebaOpcion(cadena_entrada);
            
            soluciones.eliminarSolucionesMenos(primeras);
            cout << endl;
            
            break;
        }
        case 6:
        {   //Dibuja el recorrido de una solución.
            // Se lee el índice de la solución:
            int indice;
            cout << "\nIntroduzca la posición que ocupa la solución por su coste: ";
            cin >> cadena_entrada;
            indice = compruebaOpcion(cadena_entrada);
            
            // Se dibuja la solución:
            plotter.plot(soluciones.solucionPosicion(indice));
            
            break;
        }
        case 7:
        {   
            string name;
            int indice;
            cout << "\nIntroduzca el nombre (y en su caso la dirección) del fichero donde se guardará la solucion:\n";
            cin >> name;
            cout << "\nIntroduzca la posición de la solución que desea representar: ";
            cin >> indice;
            iotsp.print(soluciones.solucionPosicion(indice),name);
            cout << "\nSe ha creado el fichero correctamente.\n\n";
            break;
        }
        case 8:
        {
            string name;
            cout << "\nIntroduzca el nombre (y en su caso la dirección) del fichero donde se guardará las soluciones:\n";
            cin >> name;
            iotsp.print_all(name);
            cout << "\nSe ha creado el fichero correctamente.\n\n";
            break;
        }
        case 9:
        {
            string name;
            cout << "\nIntroduzca el nombre (y en su caso la dirección) del fichero de soluciones que desea cargar:\n";
            cin >> name;
            iotsp.load(name);
            cout << "\nSe han cargado las soluciones correctamente.\n\n";
            break;
        }
        case 0:
        {   //Se vuelve al menú principal.
            cout << "\nVolviendo al menú principal... \n\n";
            nivel = 1;
            
            break;
        }
        case -1:
        {   //Cierra el programa.
            break;
        }
        default:
        {   // Si no se ha elegido una opción dentro del rango dado:
            cout << "\nNo existe la opción elegida. Pruebe de nuevo.\n\n";
            
            break;
        }
    }
}

// Método que ejecuta una opción del menú de ajuste de los parámetros de los algoritmos:
void Menu::realizarOpcionMenuAjusteParametros(int opcion){
    string cadena_entrada;
    switch(opcion){
        case 1:
        {
            cout << "\nNo hay parámetros en este algoritmo.\n\n";
            break;
        }
        case 2:
        {
            cout << "\nNo hay parámetros en este algoritmo.\n\n";
            break;
        }
        case 3:
        {
            cout << "\nNo hay parámetros en este algoritmo.\n\n";
            break;
        }
        case 4:
        {
            cout << "\nGRASP (Greedy Randomized Adaptative Search):"
                 << "\n- Indice Validez: " << heuristica_grasp.getIndiceValidez() << endl
                 << "¿Desea modificarlo? (s/n): ";
            do{
               cin >> cadena_entrada;
            } while (cadena_entrada != "s" && cadena_entrada != "n");
            
            if (cadena_entrada == "s"){
               double nuevo_indice;
               cout << "\nIntroduzca el nuevo índice de validez: ";
               cin >> cadena_entrada;
                        nuevo_indice = compruebaOpcion(cadena_entrada);
               heuristica_grasp.setIndiceValidez(nuevo_indice);
               cout << "\nSe ha procesado el cambio.";
            }
            cout << endl << endl;
            break;
        }
        case 5:
        {
            cout << "\nNo hay parámetros en este algoritmo.\n\n";
            break;
        }
        
        case 6:
        {
            do{
                cout << "\nSA (Simulated Annealing):"
                     << "\n1. Indice Validez: " << simulated_annealing.getIndiceValidez()
                     << "\n2. Probabilidad Inicial: " << simulated_annealing.getProbabilidadInicial()
                     << "\n3. Número de Iteraciones Por Temperatura: " << simulated_annealing.getIteracionesPorTemperatura()
                     << "\nIntroduzca el índice del parámetro que desea modificar (0 para volver atrás): ";
                cin >> cadena_entrada;
                opcion = compruebaOpcion(cadena_entrada);
                
                double nueva_variable;
                    
                switch(opcion){
                    case 1:
                    {
                        cout << "\nIntroduzca el nuevo índice de validez: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        simulated_annealing.setIndiceValidez(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 2:
                    {
                        cout << "\nIntroduzca la nueva probabilidad inicial: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        simulated_annealing.setProbabilidadInicial(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 3:
                    {
                        cout << "\nIntroduzca el nuevo número de iteraciones por temperatura: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        simulated_annealing.setIteracionesPorTemperatura(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 0:
                    {   //Se vuelve al menú anterior:
                        cout << "\nVolviendo al menú aterior...";
                        
                        break;
                    }
                    default:
                    {   // Si no se ha elegido una opción dentro del rango dado:
                        cout << "\nNo existe la opción elegida. Pruebe de nuevo";
                        
                        break;
                    }
                }    
                
                cout << endl << endl;
            }while(opcion != 0);
            
            break;
        }
        case 7:
        {
            do{
                cout << "\nGA (Algoritmo Genético):"
                     << "\n1. Probabilidad de Cruce: " << heuristica_genetico.getProbabilidadCruce()
                     << "\n2. Probabilidad de Mutación: " << heuristica_genetico.getProbabilidadMutacion()
                     << "\n3. Número de Individuos de la Población: " << heuristica_genetico.getNumeroIndividuos()
                     << "\nIntroduzca el índice del parámetro que desea modificar (0 para volver atrás): ";
                cin >> cadena_entrada;
                opcion = compruebaOpcion(cadena_entrada);
                
                double nueva_variable;
                    
                switch(opcion){
                    case 1:
                    {
                        cout << "\nIntroduzca la nueva probabilidad de mutación: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_genetico.setProbabilidadMutacion(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 2:
                    {
                        cout << "\nIntroduzca el nuevo número de individuos de la población: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_genetico.setNumeroIndividuos(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 0:
                    {   //Se vuelve al menú anterior:
                        cout << "\nVolviendo al menú anterior...";
                        
                        break;
                    }
                    default:
                    {   // Si no se ha elegido una opción dentro del rango dado:
                        cout << "\nNo existe la opción elegida. Pruebe de nuevo";
                        
                        break;
                    }
                }    
                
                cout << endl << endl;
                if (opcion != 0)
                    pause();
            }while(opcion != 0);
            
            break;
        }
        case 8:
        {
            do{
                cout << "\nACOTSP (Optimización de la Colonia de Hormigas):"
                     << "\n1. Parejas de hormigas: " << heuristica_hormiga.getParesHormigas()
                     << "\n2. Parámetro de evaporación (rho): " << heuristica_hormiga.getParamEvaporacion()
                     << "\n3. Influencia de las feromonas (alpha): " << heuristica_hormiga.getInfFeromonas()
                     << "\n4. Influencia de la heurística (beta): " << heuristica_hormiga.getInfMovimiento()
                     << "\n5. Índice de mejoras locales (cada 100 iteraciones): " << heuristica_hormiga.getNumMejoras()
                     << "\nIntroduzca el índice del parámetro que desea modificar (0 para volver atrás): ";
                cin >> cadena_entrada;
                opcion = compruebaOpcion(cadena_entrada);

                double nueva_variable;

                switch(opcion){
                    case 1:
                    {
                        cout << "\nIntroduzca el número de parejas de hormigas que desea soltar durante el algoritmo: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_hormiga.setParesHormigas(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 2:
                    {
                        cout << "\nIntroduzca el valor (entre [0,1)) que desea para el ritmo de evaporación de las feromonas: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_hormiga.setParamEvaporacion(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 3:
                    {
                        cout << "\nIntroduzca el valor (mayor que 0), que desea para la influencia de las feromonas en el recorrido de la hormiga: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_hormiga.setInfFeromonas(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 4:
                    {
                        cout << "\nIntroduzca el valor (mayor que 0), que desea para la influencia de la heurística en el recorrido de la hormiga: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_hormiga.setInfMovimiento(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 5:
                    {
                        cout << "\nIntroduzca un entero entre 0 y 100 indicando el número de mejoras locales para cada 100 iteraciones: ";
                        cin >> cadena_entrada;
                        nueva_variable = compruebaOpcion(cadena_entrada);
                        heuristica_hormiga.setNumMejoras(nueva_variable);
                        cout << "\nSe ha procesado el cambio.";
                        break;
                    }
                    case 0:{
                        cout << "Volviendo al menú anterior...";
                        break;
                    }
                    default:
                        cout << "No existe la opción elegida. Pruebe de nuevo.";
                        break;

                }
                cout << endl << endl;

                if(opcion != 0){
                    pause();
                }
            }while(opcion != 0);
        }
        case 0:
        {   //Se vuelve al menú principal.
            cout << "\nVolviendo al menú principal... \n\n";
            nivel = 1;
            
            break;
        }
        case -1:
        {   //Cierra el programa.
            break;
        }
        default:
        {   // Si no se ha elegido una opción dentro del rango dado:
            cout << "\nNo existe la opción elegida. Pruebe de nuevo.\n\n";
            
            break;
        }
    }
}

//Imprime una presentación con un mensaje en el centro.
void Menu::presentacion(int filas, int columnas, char simbolo, string mensaje) const{
	cout << endl;
    int fila_central = filas / 2;
	int columna_central = (columnas - mensaje.size() -2) / 2; //Espacio para el mensaje (su longitud más dos espacios en blanco).
	int i = 0,j = 0;

    //Se imprime simbolo hasta que se alcanzan la fila y columna central.
    //En dicho momento, se imprime el mensaje.
	while(i < filas){
        int j = 0;    
		while(j < columnas){
			if(i == fila_central && j == columna_central){
				cout << " " << mensaje << " ";
				j += mensaje.size()+2;
			}
			else{
				cout << simbolo;
                j++;
			}
        }
		cout << "\n";
		i++;
	}
}

//Pausa el programa hasta que se presiona ENTER
void Menu::pause() const{
	char sobra;
	sobra = cin.get();   //Solo funciona si la última lectura no consumió el retorno de carro.

    cout << "Presione ENTER para continuar...";
	do{
		sobra = cin.get();
	}while(sobra != '\n');
}