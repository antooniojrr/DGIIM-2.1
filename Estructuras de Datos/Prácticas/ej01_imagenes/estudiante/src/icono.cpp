// Fichero: icono.cpp
// Genera una imagen nueva a partir de la reducción de otra en base a un factor de reducción
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]) {

    char *fich_orig, *fich_rdo; // nombres de los ficheros
    int factor; // factor de reducción. La imagen resultante tendrá floor(filas/factor) x floor(cols/factor)
    Image image;

    // Comprobar validez de la llamada
    if (argc != 4) {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: icono <FichImagenOriginal> <FichImagenDestino> <factor>\n";
        exit(1);
    }

    // Asignamos a cada parámetro el correspondiente argumento introducido
    fich_orig = argv[1];
    fich_rdo = argv[2];
    factor = stoi(argv[3]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;
    cout << "Factor de reducción a usar " << factor << endl;

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

    // Realizar el proceso de reducción

    Image result(image.Subsample(factor));

    // Guardar la imagen resultado en el fichero indicado

    if (result.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;

}