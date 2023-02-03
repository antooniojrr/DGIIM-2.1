//
// Created by antoniojrr on 12/12/22.
//

#include <string>
#include <vector>
#include <utility>
#include "dictionary.h"
#include "letters_set.h"
#include "solver.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//                               Aux functions                               //
///////////////////////////////////////////////////////////////////////////////

bool Solver::puedeHacerse(string palabra, const vector<char> &available_letters) {

    bool puede=true;
    vector<char> letras_disp(available_letters);

    for (int i=0; i < palabra.size() && puede; i++) {
        char c=palabra.at(i);
        bool esta=false;
        for (int j=0; j < letras_disp.size() && !esta; j++) {
            if (letras_disp.at(j)==c) {
                esta = true;
                letras_disp.at(j)='\0';
            }
        }
        if (!esta)
            puede=false;
    }
    return puede;
}
vector<string> Solver::getPalabras(const vector<char> &available_letters) {

    vector<string> palabras;

    // Primero, para evitar problemas de comparación entre mayusc y minusc, pasamos todas
    // las letras a minúsculas

    for (int i=0; i < available_letters.size(); i++)
        tolower(available_letters[i]);

    // Vamos pasando palabra por palabra del diccionario comprobando cuales se pueden formar con
    // available_letters

    Dictionary::iterator iter(diccionario.begin());

    for (; iter!=diccionario.end() ; ++iter) {
        if (puedeHacerse((*iter), available_letters) && (*iter)!="")
            palabras.push_back((*iter));
    }

    return palabras;
}

///////////////////////////////////////////////////////////////////////////////
//                             Public functions                              //
///////////////////////////////////////////////////////////////////////////////

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {

    this->diccionario=dict;
    this->letras=letters_set;

}

pair<vector<string>, int> Solver::getSolutions(const vector<char> &available_letters, bool score_gaming) {

    vector<string> pos_soluciones = getPalabras(available_letters);
    vector<string> soluciones;

    // Dependiendo del modo de juego, compararemos de una manera o de otra
    soluciones.push_back(pos_soluciones[0]);
    int score;

    if (score_gaming) {
        // Compararemos las puntuaciones de cada palabra según la de cada letra de "letras"
        score=letras.getScore(pos_soluciones[0]);
        for (int i=1; i < pos_soluciones.size(); i++) {

            if (letras.getScore(pos_soluciones[i]) == score)
                soluciones.push_back(pos_soluciones[i]);

            else if (letras.getScore(pos_soluciones[i]) > score) {
                soluciones.clear();
                soluciones.push_back(pos_soluciones[i]);
                score=letras.getScore(pos_soluciones[i]);
            }
        }
    }

    else {
        // Compararemos las longitudes de las palabras
        score=pos_soluciones[0].size();
        for (int i=1; i < pos_soluciones.size(); i++) {

            if (pos_soluciones[i].size() == score)
                soluciones.push_back(pos_soluciones[i]);

            else if (pos_soluciones[i].size() > score) {
                soluciones.clear();
                soluciones.push_back(pos_soluciones[i]);
                score=pos_soluciones[i].size();
            }
        }
    }

    return pair<vector<string>, int> (soluciones,score);
}

/*
pair<vector<string>,int> Solver::getSolutions(const vector<char> &available_letters, bool score_gaming) {

    Dictionary::possible_words_iterator iter(diccionario.possible_words_begin(available_letters));
    int score;
    vector<string> solutions;
    solutions.push_back(*iter);
    ++iter;
    if (score_gaming) {
        score=letras.getScore(solutions[0]);

        for (; iter != diccionario.possible_words_end(); ++iter) {
            if (letras.getScore(*iter) > score) {
                solutions.clear();
                solutions.push_back(*iter);
                score=letras.getScore(*iter);
            }

            else if (letras.getScore(*iter) == score)
                solutions.push_back(*iter);

        }

    }

    else {
        score=solutions[0].size();

        for(;iter!=diccionario.possible_words_end();++iter) {
            if ((*iter).size() > score) {
                solutions.clear();
                solutions.push_back(*iter);
                score=(*iter).size();
            }

            else if ((*iter).size() == score)
                solutions.push_back(*iter);

        }
    }

    return pair<vector<string>,int> (solutions,score);
} */ // SOLVER EFICIENTE