// Fichero: contraste.cpp
// Lee y modifica el contraste de una imagen para después guardarla en otro fichero.
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]) {

    char *fich_orig, *fich_rdo; // nombres de los ficheros
    int e1, e2, s1, s2; // Margenes de contraste para la transformación de la imagen
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7) {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <FichImagenOriginal> <FichImagenDestino> <e1> <e2> <s1> <s2>\n";
        exit(1);
    }

    // Asignamos a cada parámetro el correspondiente argumento introducido
    fich_orig = argv[1];
    fich_rdo = argv[2];
    e1 = stoi(argv[3]);
    e2 = stoi(argv[4]);
    s1 = stoi(argv[5]);
    s2 = stoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;
    cout << "Umbral inferior de la imagen de entrada: " << e1 << endl;
    cout << "Umbral superior de la imagen de entrada: " << e2 << endl;
    cout << "Umbral inferior de la imagen de salida: " << s1 << endl;
    cout << "Umbral superior de la imagen de salida: " << s2 << endl;

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

    // Realizar la transformación en la imagen

    image.AdjustContrast(e1,e2,s1,s2);

    // Guardar la imagen modificada en el fichero indicado

    if (image.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;

}