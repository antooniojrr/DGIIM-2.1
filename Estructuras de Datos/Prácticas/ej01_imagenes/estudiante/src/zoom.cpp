// Fichero: zoom.cpp
// Genera una imagen nueva a partir del zoom x2 a otra
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]) {

    char *fich_orig, *fich_rdo; // nombres de los ficheros
    int fila, col; // Pixel superior izdo de la imagen a recortar
    int lado; // tamaño del lado del cuadrado a hacer zoom
    Image image;

    // Comprobar validez de la llamada
    if (argc != 6) {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <fila> <colum> <lado>\n";
        exit(1);
    }

    // Asignamos a cada parámetro el correspondiente argumento introducido
    fich_orig = argv[1];
    fich_rdo = argv[2];
    fila = stoi(argv[3]);
    col = stoi(argv[4]);
    lado = stoi(argv[5]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;
    cout << "Coordenadas pixel superior izdo: (" << fila << "," << col << ")" << endl;
    cout << "Tamaño del cuadrado de zoom: " << lado << endl;

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

    // Comprobación de la validez de los argumentos
    if (fila+lado>=image.get_rows() || col+lado>=image.get_cols() ) {
        cerr << "Error: dimensiones de la imagen inferiores a las necesarias" << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Realizar el zoom a la imagen
    Image aux(image.Crop(fila,col,lado,lado));
    Image result(aux.Zoom2X());

    // Guardar la imagen resultado en el fichero

    if (result.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;

}