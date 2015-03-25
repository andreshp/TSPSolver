# include <iostream>
# include "TSPProblema.h"
# include "Menu.h"

using namespace std;

int main(int argc, char **argv){
    
    // Se comprueba que los argumentos son correctos:
    if  (argc != 2){
        cout << "Uso de programa: tsp archivo" << endl;
        exit(-1);
    }

    // Cuerpo del programa:
    try{

        // Declaración de variables y objetos:
	    int opcion;	

	    TSPProblema problema(argv[1]);
   	    Menu menu(&problema);
        
        // Mensaje de bienvenida:        
        menu.presentacion(23,79,'*',"Bienvenido a TSPSolver");

        // Se repite el programa mientras no se haya introducido la opción -1:
        do{
            try{
                // Se ejecuta el menú correspondiente:
        		menu.showOptions();
        		opcion = menu.readOption();
            }
            catch(logic_error excepcion){
                cout << "\nERROR LÓGICO: " << excepcion.what() << endl;
            }  
            if(opcion != -1)
                menu.pause();     

        } while (opcion != -1);

        // Mensaje de despedida:
        menu.presentacion(23,79,'*',"Hasta luego, le estaremos esperando");
        cout << "\n          Autores: Juan Luis Suárez Díaz y Andrés Herrera Poyatos.\n";
        cout << "                 Este software se encuentra bajo licencia MIT.\n\n";
        //delete &menu;
        //delete &problema;
    
    }
    catch(runtime_error excepcion){
        cout << "ERROR DE EJECUCIÓN: " << excepcion.what() << endl;
        exit(-1);
    }

    return 0;
}
