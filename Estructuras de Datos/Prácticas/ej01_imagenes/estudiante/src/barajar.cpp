// Fichero: barajar.cpp
// Lee una imagen, la baraja tantas veces como se le indique y la guarda en un nuevo fichero
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <image.h>

using namespace std;

int main (int argc, char *argv[]) {

    char *fich_orig, *fich_rdo; // nombres de los ficheros

    Image image;
    unsigned t0, t1;

    t0 = clock();
    // Comprobar validez de la llamada
    if (argc != 3) {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: barajar <FichImagenOriginal> <FichImagenDestino>\n";
        exit(1);
    }

    // Asignamos a cada parámetro el correspondiente argumento introducido
    fich_orig = argv[1];
    fich_rdo = argv[2];


    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Barajamos las filas

    image.ShuffleRows();

    // Guardar la imagen resultado en el fichero indicado

    if (image.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    t1 = clock();

    // Calculamos tiempo de ejecución

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    return 0;

}