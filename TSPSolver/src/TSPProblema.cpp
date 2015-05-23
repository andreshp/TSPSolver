# include "TSPProblema.h"
# include <limits>

using namespace std;

                    /* MÉTODOS PRIVADOS */

// Método privado que lee los datos del archivo indicado en nombre_archivo:
void TSPProblema::leerDatosArchivo(){
    // Declaración de variables:
    string cabecera;
    double x,y;
    string idCiudad;

    // Inicia la lectura del archivo indicado por nombre_archivo. Si no existe se produce un error de ejecución:
    ifstream archivo(nombre_archivo.c_str());
    if (!archivo){
        throw runtime_error("No existe el archivo " + nombre_archivo);
    }

    // Se lee el nombre del problema:
    archivo >> cabecera;
    archivo >> nombre_problema;

    // Lee la cabecera del archivo y el número de ciudades con las que se trabajará (inicializando num_ciudades):
    do{
        archivo >> cabecera;
    }while(cabecera != "DIMENSION:");
    archivo >> num_ciudades;
    archivo >> cabecera;
    archivo >> distancia_optima;
    do{
        archivo >> cabecera;
    }while(cabecera != "1");

    // Reserva espacio en memoria para la matriz de distancias y las ciudades:
    reservarEspacio();

    archivo >> x;
    archivo >> y;
    ciudades[0].setCoordenadas(x, y);

    // Lee las coordenadas de las ciudades:
    for (int i = 1; i < num_ciudades; i++){
        archivo >> idCiudad;
        archivo >> x;
        archivo >> y;
        ciudades[i].setCoordenadas(x, y);
    }
}

// Método que reserva el espacio para ciudades y matriz_distancias:
void TSPProblema::reservarEspacio(){
    // Se crea un array al que apuntará ciudades:
    ciudades = new TSPPunto [num_ciudades];

    // Se reserva el espacio para matriz_distancias:
    matriz_distancias = new int *[num_ciudades];
    for (int i = 0; i < num_ciudades; i++){
        matriz_distancias[i] = new int [num_ciudades];
    }
}

// Método privado que calcula la matriz de distancias:
void TSPProblema::calcularMatrizDistancias(){
    // Como la matriz es simétrica, solo se calcula la mitad superior:
    for (int i = 0; i < num_ciudades; i++){
        
        for (int j = i+1; j < num_ciudades; j++){
            matriz_distancias[i][j] = ciudades[i].distanciaHasta(ciudades[j]);
            matriz_distancias[j][i] = matriz_distancias[i][j];
        }

        matriz_distancias[i][i] = 0;
    }
}

                 /* MÉTODOS PÚBLICOS */

// Constructor de la clase:
TSPProblema::TSPProblema(string nombre_archivo){
    this->nombre_archivo = nombre_archivo;
    leerDatosArchivo();
    calcularMatrizDistancias();
}

// Destructor de la clase:
TSPProblema::~TSPProblema(){
    delete [] ciudades;
    for (int i = 0; i < num_ciudades; i++){
        delete [] matriz_distancias[i];
    }
    delete [] matriz_distancias;
}


// Constructor de copia de la clase:
TSPProblema::TSPProblema(const TSPProblema &otro){
    this->nombre_archivo = otro.nombre_archivo;
    this->num_ciudades = otro.num_ciudades;
    reservarEspacio();
    for (int i = 0; i < num_ciudades; i++){
        this->ciudades[i] = otro.ciudades[i];
    }
    for (int i = 0; i < num_ciudades; i++){
        for (int j = 0; j < num_ciudades; j++){
            this->matriz_distancias[i][j] = otro.matriz_distancias[i][j];
        }
    }
}

//Método que devuelve la ciudad dada por indice.
TSPPunto TSPProblema::ciudad(int indice) const{
    if(indice < num_ciudades && indice >= 0){
        return ciudades[indice];
    }
    else{
        throw logic_error("Las ciudades están enumeradas de 0 a " 
            + static_cast<ostringstream*>(&(ostringstream() << num_ciudades-1))->str());
    }
}
