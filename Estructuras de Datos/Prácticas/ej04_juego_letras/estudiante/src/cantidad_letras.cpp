//
// Created by antoniojrr on 4/12/22.
//

#include "dictionary.h"
#include <string>
#include "letters_set.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    if(argc != 3){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con el Letter_Set" << endl;
        return 1;
    }

    ifstream f_diccionario(argv[1]);

    if(!f_diccionario){
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        return 0;
    }
    Dictionary diccionario;
    f_diccionario >> diccionario;

    ifstream f_letters(argv[2]);

    if(!f_letters){
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        return 0;
    }

    LettersSet letras;
    f_letters >> letras;

    cout << "Letras\tUsos\tOcurrencias" << endl;
    char c;
    int usos, ocur;
    for (LettersSet::Iterator iter(letras.begin()); iter != letras.end(); iter.operator++()) {
        c = (*iter).first;
        usos = diccionario.getTotalUsages(c);
        ocur = diccionario.getOccurrences(c);
        cout << (char)toupper(c) << " " << usos << " " << ocur << endl;

    }

    return 0;

}

