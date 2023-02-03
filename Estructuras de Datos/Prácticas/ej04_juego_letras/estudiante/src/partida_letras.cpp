//
// Created by antoniojrr on 24/12/22.
//

#include <string>
#include <vector>
#include <utility>
#include <stdlib.h>
#include "dictionary.h"
#include "letters_set.h"
#include "solver.h"
#include <cmath>
#include <fstream>
#include <letters_bag.h>

using namespace std;

int main(int argc, char *argv[]){

    srand(time(nullptr));
    const string JUEGO_LON="L";
    const string JUEGO_PUN="P";
    if (argc != 5) {
        cout << "Error: introduzca los argumentos necesarios para jugar:" << endl
                                << " - Ruta del diccionario" << endl
                                << " - Ruta de las letras" << endl
                                << " - Modo de juego ( L o P )" << endl
                                << " - Cantidad de letras para la partida" << endl;
        exit(-1);
    }

    Dictionary diccionario;
    LettersSet letras;

    ifstream entrada_diccionario;

    entrada_diccionario.open(argv[1]);
    if (entrada_diccionario.fail()) {
        cout << "Error abriendo el archivo diccionario" << endl;
        exit(-1);
    }

    entrada_diccionario >> diccionario;

    ifstream entrada_letras;

    entrada_letras.open(argv[2]);
    if (entrada_letras.fail()) {
        cout << "Error abriendo el archivo letras" << endl;
        exit(-1);
    }

    entrada_letras >> letras;

    bool score_gaming;
    if (argv[3] != JUEGO_LON && argv[3] != JUEGO_PUN) {
        cout << "Error: Introduzca como tercer argumento el modo de juego ( L o P )" << endl;
        exit(-1);
    }

    else if (argv[3] == JUEGO_LON)
        score_gaming=false;
    else
        score_gaming=true;


    LettersBag bolsa;
    LettersSet::Iterator iter;
    for (iter=letras.begin(); iter != letras.end(); iter.operator++()) {
        for (int i = 0; i < (*iter).second.repetitions; i++)
            bolsa.insertLetter((*iter).first);
    }

    // Ahora que tenemos todas las TDA necesarias construidas, extraeremos las letras con las que
    // jugamos
    int num_letras=stoi(argv[4]);
    vector<char> available_letters=bolsa.extractLetters(num_letras);

    cout << "LETRAS DISPONIBLES:" << endl;
    for (int i = 0;i < available_letters.size(); i++) {
        cout << (char)toupper(available_letters[i]) << " ";
    }

    // Inicializamos un Solver con el diccionario y el letterset introducidos
    Solver sol(diccionario,letras);

    pair<vector<string>,int> soluciones(sol.getSolutions(available_letters,score_gaming));

    cout << endl << "SOLUCIONES:" << endl;
    for (int i=0; i<soluciones.first.size(); i++)
        cout << soluciones.first[i] << endl;

    cout << "PUNTUACION:" << endl;
    cout << soluciones.second;

    return 0;

}