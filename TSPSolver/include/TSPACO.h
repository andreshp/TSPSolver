#ifndef TSPACO_H
#define TSPACO_H

#include "TSPProblema.h"
#include "TSPSolucion.h"
#include "TSPLocalSearch.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Cronometro.h" //For trace.


using namespace std;

/**
* @brief Nombre del algoritmo. Las clases que lo utilicen lo tomarán apuntando aquí.
*/
static const string nombre_aco = "ACOTSP";

/**
* @brief Clase que almacena una matriz con la cantidad de feromonas
* entre dos ciudades de un problema. Además, determina las probabilidades
* a partir de dichas feromonas.
*/
class MapaFeromonas;

/**
* @brief Clase cuyos objetos se encargan de moverse por un mapa de feromonas
* siguiendo ciertas ecuaciones de probabilidad y liberan más feromonas con la
* finalidad de encontrar un recorrido óptimo.
*/
class Hormiga;

/**
* @brief Clase encargada de dirigir una colonia de hormigas a través de un mapa
* de feromonas para determinar una buena solución al problema del TSP.
*/
class TSPACO;


class MapaFeromonas{
private:
	/**
	* @brief Puntero al problema que se asociará al mapa.
	*/
	TSPProblema *problema;

	/**
	* @brief Puntero a la matriz que almacenará las feromonas.
	*/
	double **feromonas;

	/**
	* @brief Puntero a la matriz que almacenará las probabilidades.
	* @brief La matriz de probabilidades se construye a partir de la de feromonas.
	*/
	double **probabilidades;

	/**
	* @brief Parámetro que marca el ritmo de evaporación de las feromonas.
	* @brief Debe estar entre 0 y 1.
	*/
	double param_evaporacion;

	/**
	* @brief Número de ciudades del mapa de feromonas.
	*/
	int num_ciudades;

	/**
	* @brief Parámetro que indica la influencia que tendrán las feromonas
	* en el cálculo de las probabilidades.
	*/
	double influencia_feromonas;

	/**
	* @brief Parámetro que indica la influencia que tendrá la distancia entre
	* las ciudades o cualquier otra heurística que se pudiera elegir para el
	* cálculo de las  probabilidades.
	*/
	double influencia_movimiento;

	/**
	* @brief Valor mínimo que pueden tener las feromonas para evitar valores incorrectos
	* de la probabilidad y evitar errores en tiempo de ejecución.
	*/
	static const double umbral_ph = 1E-10;

	
public:

	/**
	* @brief Constructor de la clase.
	* @param num_ciudades Número de ciudades que se desean utilizar en la matriz.
	* @param param_inicial Valores iniciales para la matriz de feromonas.
	* @param param_evaporacion Ritmo de evaporación que se desea para las feromonas.
	* @param influencia_feromonas Influencia que se desea para las feromonas en el cálculo de la probabilidad.
	* @param influencia_movimiento Influencia que se desea para la heurística en el cálculo de la probabilidad.
	*/
	MapaFeromonas(TSPProblema *problema, double param_inicial = 0.1, double param_evaporacion = 0.6, double influencia_feromonas = 0.1, double influencia_movimiento = 6);

	/**
	* @brief Método encargado de añadir feromonas en un camino entre dos ciudades.
	* @param origen Ciudad de salida.
	* @param destino Ciudad de llegada.
	* @param cantidad Cantidad de feromonas a añadir.
	*/
	void aniadeFeromonas(int origen, int destino, double cantidad);
	
	/**
	* @brief Método que evapora las feromonas de la matriz en un cierto porcentaje
	* dado por el parámetro de evaporación.
	* @brief Este método es solo válido para problemas simétricos.
	*/
	void evaporaSimetrico();

	/**
	* @brief devuelve la cantidad de feromonas que hay entre dos ciudades.
	* @param origen Ciudad de salida.
	* @param destino Ciudad de llegada.
	* @return Cantidad de feromonas entre origen y destino.
	*/
	inline double getFeromonas(int origen, int destino){
		return feromonas[origen][destino];
	}

	/**
	* @brief Devuelve el número de ciudades que forman el mapa.
	* @return Número de ciudades.
	*/
	inline int numeroCiudades(){
		return this->num_ciudades;
	}

	/**
	* @brief Devuelve la probabilidad de desplazarse de una ciudad a otra.
	* @param origen Ciudad de salida.
	* @param destino Ciudad de llegada.
	* @return Probabilidad de ir de origen a destino.
	*/
	inline double getProbabilidad(int origen, int destino){
		return probabilidades[origen][destino];
	}
	
	/**
	* @brief Destructor de la clase.
	*/
	~MapaFeromonas();
};



class Hormiga{
private:
	/**
	* @brief Puntero al problema sobre el que se desplazan las hormigas.
	*/
	TSPProblema *problema;

	/**
	* @brief Puntero al mapa de feromonas sobre el que se desplazan las hormigas.
	*/
	MapaFeromonas *feromonas;

	/**
	* @brief Puntero al array con el recorrido que lleva la hormiga.
	*/
	int *recorrido;

	/**
	* @brief Puntero a un array de bool que indica si la ciudad i-ésima está visitada.
	*/
	bool *visitadas;

	/**
	* @brief Variable con el coste del recorrido que lleva la hormiga.
	*/
	double coste;

	/**
	* @brief Variable con las ciudades recorridas por la hormiga.
	*/
	int total_recorrido;

	/**
	* @brief Variable que se hace verdadera solo cuando la hormiga ha terminado un recorrido.
	*/
	bool recorrido_completo;

	/**
	* @brief Puntero a una cadena con el nombre del algoritmo.
	* @brief Se inicializa en el constructor.
	*/
	const string *nombre_algoritmo;

	/**
	* @brief Variable booleana que indica el género de la hormiga.
	* @brief La diferencia en el género afecta al desprendimiento de feromonas.
	* @brief Solo las hembras sueltan feromonas. Esto permite mayor control sobre los recorridos.
	*/
	bool hembra;
	
	/**
	* @brief Total de  ciudades del mapa donde se mueve la hormiga.
	*/
	int num_ciudades;	

	/**
	* @brief Método privado que determina la probabilidad de ir de una ciudad a otra.
	* @param origen Ciudad de salida.
	* @param destino Ciudad de llegada.
	* @return valor de la probabilidad entre origen y destino.
	*/
	double determinaProbabilidad(int origen, int destino);

	
public:
	/**
	* @brief Constructor por defecto.
	* @brief Útil para crear una colonia dinámica de hormigas.
	* @brief Requiere algún método inicia para ponerse en marcha.
	*/
	Hormiga();

	/**
	+ @brief Constructor e inicializador para la hormiga.
	* @param problema Puntero al problema con el que se trabaja.
	* @param feromonas Puntero al mapa con las feromonas con las que se guía la hormiga.
	* @param inicio Ciudad inicial donde se suelta la hormiga.
	* @param hembra Indica el género de la hormiga. true=hembra, false=macho
	*/
	Hormiga(TSPProblema *problema, MapaFeromonas *feromonas, int inicio, bool hembra);

	/**
	* @brief Inicializa la hormiga y la suelta en una ciudad.
	* @param problema Puntero al problema con el que se trabaja.
	* @param feromonas Puntero al mapa con las feromonas con las que se guía la hormiga.
	* @paran inicio Ciudad inicial donde se suelta la hormiga.
	* @param hembra Indica el género de la hormiga. true=hembra, false=macho
	*/
	void inicia(TSPProblema *problema, MapaFeromonas *feromonas, int inicio, bool hembra);
	
	/**
	* @brief Inicializa la hormiga sin llegar a soltarla aún en ningún sitio.
	* @brief Requiere del método recomenzar para iniciar el movimiento.
	* @param problema Puntero al problema con el que se trabaja.
	* @param feromonas Puntero al mapa con las feromonas con las que se guía la hormiga.
	* @param hembra Indica el género de la hormiga. true=hembra, false=macho
	*/
	void inicia(TSPProblema *problema, MapaFeromonas *feromonas,bool hembra);

	/**
	* @brief Método que determina según las feromonas la siguiente ciudad a visitar por la hormiga.
	* @return Siguiente ciudad a visitar.
	*/
	int determinarSiguienteCiudad();

	/**
	* @brief Método que adelanta la hormiga a la ciudad dada como parámetro.
	* @param ciudad Ciudad a la que se desea avanzar.
	*/
	void avanza(int ciudad);

	/**
	* @brief Método que avanza de forma natural a la hormiga, siguiendo las probabilidades
	* de las feromonas.
	*/
	void avanzaNatural();

	/**
	* @brief Método que empieza un nuevo recorrido para la hormiga.
	* @param ciudad Ciudad desde la que comenzará la hormiga.
	*/
	void recomenzar(int ciudad);

	/**
	* @brief Método que compara los recorridos de dos hormigas.
	* @param otra_hormiga Puntero a la hormiga con la que se compara.
	* @return True si el recorrido de la primera hormiga es mejor,
	* false si lo es el de la segunda.
	*/
	bool mejorRecorrido(Hormiga *otra_hormiga);

	/**
	* @brief Método que accede a una ciudad del recorrido.
	* @param posicion Posición del recorrido a la que se desea acceder.
	* @return Ciudad visitada en dicha posición.
	*/
	inline int ciudadVisitada(int posicion){
		return recorrido[posicion];
	}

	/**
	* @brief Crea una solución a partir del recorrido de la hormiga.
	* @return Objeto de TSPSolucion generado por la hormiga.
	*/
	TSPSolucion *recorridoHormiga();

	/**
	* @brief Hace que la hormiga recorra un camino dado por una solución.
	* @param solucion Camino de TSPSolucion que recorrerá la hormiga.
	*/
	void recorre(TSPSolucion *solucion);

	/**
	* @brief Indica la cantidad de feromonas que se han de soltar en el avance de la hormiga.
	* @param origen Ciudad de salida.
	* @param destino Ciudad de llegada.
	* @return Cantidad de feromonas a soltar.
	*/
	inline double feromonasASoltar(int origen, int destino){
		return (hembra)?(1/problema->elementoMatrizDistancias(origen,destino)):0;
	}

	/**
	* @brief Destructor de la clase.
	*/
	~Hormiga();
};

class TSPACO{
private:

	/**
	* @brief Puntero al problema con el que se trabaja.
	*/
	TSPProblema *problema;

	/**
	* @brief Puntero a las distintas soluciones que genere el algoritmo.
	*/
	TSPSolucion *solucion;

	/**
	* @brief Puntero al nombre del algoritmo. Se inicializa en el constructor.
	*/
	const string *nombre_algoritmo;

	/**
	* @brief Colonia de hormigas macho.
	*/
	Hormiga *colonia_m;

	/**
	* @brief Colonia de hormigas hembra.
	*/
	Hormiga *colonia_h;

	/**
	* @brief Puntero al mapa de feromonas sobre el que se trabajará.
	*/
	MapaFeromonas *feromonas;

	/**
	* @brief Parámetro que indica el número de hormigas que se soltarán en el problema.
	*/
	int pares_hormigas;

	/**
	* @brief Parámetro que indica el ritmo de evaporación de las feromonas.
	*/
	double param_evaporacion;

	/**
	* @brief Parámetro que indica la influencia de las feromonas al determinar la probabilidad.
	*/
	double influencia_feromonas;

	/**
	* @brief Parámetro que indica la influencia de la heurística al determinar la probabilidad.
	*/
	double influencia_movimiento;

	/**
	* @brief Número de mejoras locales de las soluciones a realizar cada 100 iteraciones.
	* @brief Puede proporcionar variabilidad en recorridos que suelen estancarse en óptimos locales.
	* @brief Debe estar entre 0 y 100.
	*/
	int porcentaje_mejoras;

	/**
	* @brief Método privado con el algoritmo de resolución del problema.
	* @param iteraciones Número de iteraciones que se da al problema.
	*/
	void resolver(int iteraciones);

	/**
	* @brief Método privado que reserva el espacio para abordar el problema.
	* @param num_hormigas Pares de hormigas (macho y hembra) para los que se reservará el espacio.
	*/
	void reservarEspacio(int num_hormigas);

	/**
	* @brief Método privado que libera de la memoria todas las herramientas
	* utilizadas para obtener la solución.
	*/
	void liberaEspacio();

public:

	/**
	* @brief Constructor de la clase.
	* @param problema Puntero al problema con el que se desea trabajar.
	*/
	TSPACO(TSPProblema *problema);
	
	/**
	* @brief Resuelve el problema y obtiene una solución.
	* @param viajes Número de veces que harán el recorrido las hormigas.
	* @return Objeto de TSPSolucion como solución del problema.
	*/
	TSPSolucion *obtenerSolucion(int viajes);	

	/**
	* @return Valor actual del parámetro "parejas de hormigas".
	*/
	inline int getParesHormigas(){
		return this->pares_hormigas;
	}

	/**
	* @brief Modifica el valor del parámetro "parejas de hormigas".
	* @param pares_hormigas Nuevo valor del parámetro.
	*/
	inline void setParesHormigas(int pares_hormigas){
		this->pares_hormigas = (pares_hormigas <= 0)?10:pares_hormigas;
	}

	/**
	* @return Valor actual del parámetro de evaporación.
	*/
	inline double getParamEvaporacion(){
		return this->param_evaporacion;
	}

	/**
	* @brief Modifica el parámetro de evaporación.
	* @param param_evaporacion Nuevo valor del parámetro.
	*/
	inline void setParamEvaporacion(double param_evaporacion){
		this->param_evaporacion = (param_evaporacion < 0 || param_evaporacion >= 1)?0.6:param_evaporacion;
	}

	/**
	* @return Valor actual del parámetro "Influencia de las feromonas".
	*/
	inline double getInfFeromonas(){
		return this->influencia_feromonas;
	}

	/**
	* @brief Modifica el parámetro "Influencia de las feromonas".
	* @param influencia_feromonas Nuevo valor del parámetro.
	*/
	inline void setInfFeromonas(double influencia_feromonas){
		this->influencia_feromonas = (influencia_feromonas <= 0)?0.1:influencia_feromonas;
	}

	/**
	* @return Valor actual del parámetro "Influencia del movimiento o heurísitca".
	*/
	inline double getInfMovimiento(){
		return this->influencia_movimiento;
	}

	/**
	* @brief Modifica el parámetro "Influencia del movimiento o heurística".
	* @param influencia_movimiento Nuevo valor del parámetro.
	*/
	inline void setInfMovimiento(double influencia_movimiento){
		this->influencia_movimiento = (influencia_movimiento <= 0)?6:influencia_movimiento;
	}
	/**
	* @return Valor del parámetro "Porcentaje de mejoras".
	*/
	inline int getNumMejoras(){
		return this->porcentaje_mejoras;
	}

	/**
	* @brief Modifica el parámetro "Porcentaje de mejoras".
	* @param porcentaje_mejoras Nuevo valor del parámetro.
	*/
	inline void setNumMejoras(int porcentaje_mejoras){
		this->porcentaje_mejoras = (0 > porcentaje_mejoras || porcentaje_mejoras > 100)?100:porcentaje_mejoras;
	}

};

#endif
