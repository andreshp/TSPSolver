#include "TSPACO.h"

//Constructor de MapaFeromonas
MapaFeromonas::MapaFeromonas(TSPProblema *problema, double param_inicial, double param_evaporacion,
					double influencia_feromonas, double influencia_movimiento){
	this->problema = problema;
	this->num_ciudades = problema->numeroCiudades();
	feromonas = new double *[num_ciudades];
	probabilidades = new double *[num_ciudades];

	double prob_feromonas_inicio = pow(param_inicial,influencia_feromonas);

	//Creación de las matrices.
	for(int i = 0; i < num_ciudades; i++){
		feromonas[i] = new double[num_ciudades];
		probabilidades[i] = new double[num_ciudades];
		for(int j = 0; j < num_ciudades; j++){
			feromonas[i][j] = param_inicial;
			probabilidades[i][j] = prob_feromonas_inicio * pow(1.0/problema->elementoMatrizDistancias(i,j),influencia_movimiento);
		}
	}

	this->param_evaporacion = param_evaporacion;
	this->influencia_feromonas = influencia_feromonas;
	this->influencia_movimiento = influencia_movimiento;
	
}

//Método para añadir feromonas y ajustar las probabilidades.
void MapaFeromonas::aniadeFeromonas(int origen, int destino, double cantidad){
	feromonas[origen][destino] += cantidad;
	feromonas[destino][origen] = feromonas[origen][destino];
	probabilidades[origen][destino] = pow(feromonas[origen][destino] + cantidad,influencia_feromonas)
						* pow(1.0/problema->elementoMatrizDistancias(origen,destino),influencia_movimiento);
	probabilidades[destino][origen] = probabilidades[origen][destino];
}

//Método para evaporar las feromonas en las matrices simétricas.
void MapaFeromonas::evaporaSimetrico(){
	double cambio, prob;
	for(int i = 1; i < num_ciudades; i++){
		for(int j = 0; j < i; j++){
			cambio = feromonas[i][j]*(1-param_evaporacion);
			feromonas[j][i] = feromonas[i][j] = (cambio < umbral_ph)?umbral_ph:cambio;
		}
	}
}

//Destructor de MapaFeromonas
MapaFeromonas::~MapaFeromonas(){
	for(int i = 0; i < num_ciudades; i++){
		delete [] feromonas[i];
		delete [] probabilidades[i];
		feromonas[i] = NULL;
		probabilidades[i] = NULL;
	}

	delete [] feromonas;
	delete [] probabilidades;
	feromonas = NULL;
}

//Constructor por defecto de Hormiga
Hormiga::Hormiga()
:nombre_algoritmo(&nombre_aco)
{
	problema = NULL;
	feromonas = NULL;
	recorrido = NULL;
	visitadas = NULL;
	num_ciudades = 0;
	srand(time(NULL));
	coste = 0;
	total_recorrido = 0;
	recorrido_completo = false;
}

//Constructor e inicializador de hormiga.
Hormiga::Hormiga(TSPProblema *problema, MapaFeromonas *feromonas, int inicio, bool hembra)
:nombre_algoritmo(&nombre_aco)
{
	inicia(problema,feromonas,inicio);

	
	srand(time(NULL));
}

//Inicializador de hormiga.
void Hormiga::inicia(TSPProblema *problema, MapaFeromonas *feromonas, int inicio, bool hembra){
	inicia(problema,feromonas,hembra);

	recorrido = new int[num_ciudades];
	visitadas = new bool[num_ciudades];
	recorrido[0] = inicio;
	
	total_recorrido = 1;
	
	for(int i = 0; i < num_ciudades; i++){
		visitadas[i] = false;
	}
}

//Inicializador de hormiga sin empezar un recorrido.
void Hormiga::inicia(TSPProblema *problema, MapaFeromonas *feromonas, bool hembra){
	this->hembra = hembra;
	this->problema = problema;
	this->feromonas = feromonas;
	this->num_ciudades = problema->numeroCiudades();
	delete [] recorrido;
	delete [] visitadas;
	recorrido = NULL;
	visitadas = NULL;
	coste = 0.0;
	total_recorrido = 0;
	recorrido_completo = false;
}

double Hormiga::determinaProbabilidad(int origen, int destino){
	/* Método que determina la probabilidad de moverse de origen a destino.
	   Algoritmo:
	   - Los casos posibles se obtienen del elemento (origen,destino) de la matriz de probabilidades.
	   - Los casos posibles se obtienen de la suma de toda la fila (origen,x) de la matriz de probabilidad.
	*/
	double posibles = 0, favorables;
	
	favorables = feromonas->getProbabilidad(origen,destino);

	for(int i = 0; i < num_ciudades; i++){
		if(!visitadas[i]){
			posibles += feromonas->getProbabilidad(origen,i);
		}
	}

	return favorables / posibles;

}

int Hormiga::determinarSiguienteCiudad(){
	/*Algoritmo:
		Se considera la ciudad donde se encuentra la hormiga tras el último paso.
		Se genera un número aleatorio.
		Se recorren todas  las ciudades. Si no se ha visitado la ciudad, se determina su probabilidad.
		Se utiliza una variable que lleva la cuenta de las probabilidades acumuladas.
		Si el valor aleatorio se encuentra entre la probabilidad acumulada de las ciudades anteriores y la nueva, se elige dicha ciudad.
	*/

	int origen = recorrido[total_recorrido -1];
	double p = 0.0;
	if(num_ciudades > total_recorrido){
		double rnd = (rand()%100000)/(double)100000;
		int j = 0;
		bool elegido = false;
		int pos_encontrado;

		for(int i = 0; i < num_ciudades && ! elegido ; i++){
			if(!visitadas[i]){
				double p_i = determinaProbabilidad(origen,i);
				if(p + p_i >= rnd && p <= rnd){
					elegido = true;
					pos_encontrado = i;
				}
				else{
					p += p_i;
				}
			}
		}
		return pos_encontrado;
	}
	else{
		//En caso de haberse recorrido todo, la ciudad siguiente sería el regreso a la inicial.
		return recorrido[0];
	}
}

void Hormiga::avanza(int ciudad){
	/* Avanza a la ciudad dada por el índice. Algoritmo:
	   - Se añade la ciudad al array del recorrido.
	   - Se actualiza el array de visitados.
	   - Se añade el coste.
	   - Si la hormiga es hembra, se actualizan las feromonas.
	   - Se incrementa total_recorrido, y si alcanza el número de ciudades, se añaden los costes y feromonas necesarios
	     para regresar a la ciudad inicial.
	*/
	if(!recorrido_completo){
		recorrido[total_recorrido] = ciudad;
		visitadas[ciudad] = true;
		double add_coste = problema->elementoMatrizDistancias(recorrido[total_recorrido-1],ciudad);
		coste += add_coste;
		if(hembra){
			feromonas->evaporaSimetrico();
		}
		feromonas->aniadeFeromonas(recorrido[total_recorrido -1],ciudad,
					feromonasASoltar(recorrido[total_recorrido-1],ciudad));
		total_recorrido++;
		if(total_recorrido == problema->numeroCiudades()){
			recorrido_completo = true;
			coste += problema->elementoMatrizDistancias(recorrido[total_recorrido-1], recorrido[0]);
			if(hembra){
				feromonas->evaporaSimetrico();
			}
			feromonas->aniadeFeromonas(recorrido[total_recorrido-1],recorrido[0],
					feromonasASoltar(recorrido[total_recorrido-1],recorrido[0]));
		}
	}
	
}

//Avanza a la siguiente ciudad siguiendo las feromonas.
void Hormiga::avanzaNatural(){
	avanza(determinarSiguienteCiudad());
}

//Reinicia un recorrido comenzando por ka ciudad dada como parámetro.
void Hormiga::recomenzar(int ciudad){
	delete [] recorrido;
	recorrido = new int[num_ciudades];
	delete [] visitadas;
	visitadas = new bool[num_ciudades];
	recorrido[0] = ciudad;
	coste = 0.0;
	total_recorrido = 1;
	this->feromonas = feromonas;

	for(int i = 0; i < num_ciudades; i++){
		visitadas[i] = false;
	}
	visitadas[ciudad] = true;
	recorrido_completo = false;
}

//Compara el recorrido de dos hormigas.
bool Hormiga::mejorRecorrido(Hormiga *otra_hormiga){
	return (this->coste <= otra_hormiga->coste || otra_hormiga->total_recorrido < problema->numeroCiudades()) && this->total_recorrido == problema->numeroCiudades();
}

//Devuelve la solución correspondiente al recorrido de una hormiga.
TSPSolucion *Hormiga::recorridoHormiga(){
	TSPSolucion *solucion = new TSPSolucion(problema,recorrido,nombre_algoritmo);
	return solucion;
}

//Hace que la hormiga recorra el camino de una solución ya prefijada.
void Hormiga::recorre(TSPSolucion *solucion){
	//Se reinicia el recorrido
	delete [] recorrido;
	delete [] visitadas;
	recorrido = new int[num_ciudades];
	visitadas = new bool[num_ciudades];

	recorrido[0] = solucion->ciudadVisitada(0);
	visitadas[0] = true;

	//Se avanza las ciudades. Se prescinde la evaporación para mejorar la eficiencia y porque no influye demasiado.
	for(int i = 1; i < num_ciudades; i++){
		recorrido[i] = solucion->ciudadVisitada(i);
		visitadas[i] = true;
		feromonas->aniadeFeromonas(recorrido[i],recorrido[i-1],feromonasASoltar(recorrido[i],recorrido[i-1]));
	}	
}

//Destructor de hormiga
Hormiga::~Hormiga(){
	delete [] recorrido;
	delete [] visitadas;
	recorrido = NULL;
	visitadas = NULL;
}

//Constructor de la heurística ACOTSP
TSPACO::TSPACO(TSPProblema *problema)
:nombre_algoritmo(&nombre_aco)
{
	this->problema = problema;
	this->feromonas = NULL;
	this->colonia_m = NULL;
	this->colonia_h = NULL;
	this->solucion = NULL;

	//VALORES POR DEFECTO:
	this->pares_hormigas = 10;
	this->param_evaporacion = 0.6;
	this->influencia_feromonas = 0.1;
	this->influencia_movimiento = 6;
	this->porcentaje_mejoras = 95;
		
}

//Reserva el espacio para realizar el algoritmo con cierto número de hormigas.
void TSPACO::reservarEspacio(int num_hormigas){
	int num_ciudades = problema->numeroCiudades();
	feromonas = new MapaFeromonas(problema,1/problema->elementoMatrizDistancias(0,1), param_evaporacion,influencia_feromonas,influencia_movimiento);
	colonia_m = new Hormiga[num_hormigas];
	colonia_h = new Hormiga[num_hormigas];
	for(int i = 0; i < num_hormigas; i++){
		colonia_m[i].inicia(problema,feromonas,false);
		colonia_h[i].inicia(problema,feromonas,true);
	}
}

//Libera la memoria utilizada en el algoritmo.
void TSPACO::liberaEspacio(){
	delete feromonas;
	delete [] colonia_m;
	delete [] colonia_h;
	feromonas = NULL;
	colonia_m = NULL;
	colonia_h = NULL;
}

void TSPACO::resolver(int iteraciones){
	/* Obtiene una solución para el problema. Algoritmo:
		- Se reserva el espacio.
		- La colonia de machos hace un recorrido natural siguiendo las feromonas.
		- Al terminar, se obtiene su solución y con una cierta probabilidad que depende de porcentaje_mejoras,
		  se hace o no una mejora local.
		- Las hormigas hembra hacen el recorrido dado por las soluciones mejoradas y sueltan nuevas feromonas.
		- Se guarda el mejor recorrido.
		- El algoritmo se repite el valor dado por iteraciones.
		- Se libera la mamoria al acabar.
	*/
	int num_ciudades = problema->numeroCiudades();
	reservarEspacio(pares_hormigas);
	TSPLocalSearch mejora_local;
	delete solucion;
	solucion = NULL;

	
	int mejorar;
			
	int it = 0;	//Variable que cuenta las iteraciones.

	do{
		//Se decide si habrá mejora.
		mejorar = rand()%100;

		//Se sueltan las hormigas macho en una ciudad al azar.
		for(int i = 0; i < pares_hormigas; i++){
			colonia_m[i].recomenzar(rand()%num_ciudades);
		}

		//Hacen un recorrido de forma natural.
		for(int i = 0; i < num_ciudades; i++){
			for(int j = 0; j < pares_hormigas; j++){
				colonia_m[j].avanzaNatural();
			}
		}


		for(int i = 0; i < pares_hormigas; i++){
			//Se obtiene la solución y se mejora si así se ha decidido
			TSPSolucion *camino_hormiga(colonia_m[i].recorridoHormiga());
			if(mejorar <= porcentaje_mejoras){
				mejora_local.mejorarSolucionMejorIntercambio(camino_hormiga);
			}

			//Las hembras recorren la solución obtenida desprendiendo feromonas.
			colonia_h[i].recorre(camino_hormiga);

			//Se actualiza la solución si el coste es menor que el ya obtenido, o si es la primera obtenida.
			if(solucion == NULL || *camino_hormiga < *solucion){
				delete solucion;
				solucion = camino_hormiga;
			}
			else{
				delete camino_hormiga;
			}
		}

		it++;

	}while(it <= iteraciones);

	//Se libera la memoria.
	liberaEspacio();
}

//Devuelve la solución obtenida.
TSPSolucion *TSPACO::obtenerSolucion(int viajes){
	resolver(viajes);
	TSPSolucion *aco_solucion = new TSPSolucion(*solucion);
	delete solucion;
	solucion = NULL;
	return aco_solucion;
}
