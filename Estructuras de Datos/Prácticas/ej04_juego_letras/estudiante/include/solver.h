//
// Created by antoniojrr on 12/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "dictionary.h"
#include "letters_set.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/**
 * @brief Ofrece la mejor solución para una partida y modo de juego determinado
 */
class Solver{

private:

    Dictionary diccionario;
    LettersSet letras;

    /**
     * @brief Calcula las palabras que se pueden crear con el conjunto de letras dado como argumento
     * @param available_letters - conjunto de letras disponible para crear palabras
     * @return Una objeto de tipo Clase vector con las palabras que se pueden crear con dichas letras.
     */
    vector<string> getPalabras(const vector<char> &available_letters);

    /**
     * @brief Comprueba si una palabra puede formarse a partir de un conjunto de letras dado como argumento
     * @param palabra - palabra a comprobar si se puede formar
     * @param available_letters - conjunto de letras disponible para crear palabras
     * @return booleano que devuelve true si sí se puede formar, y false si no se puede formar.
     */
    bool puedeHacerse(string palabra, const vector<char> &available_letters);

public:

    /**
     * @brief Constructor por parámetros. Crea un solver que tiene asociado un Dictionary y un LetterSet
     * @param dict - dictionary asociado al nuevo objeto solver
     * @param letters_set - letters_set asociado al nuevo objeto solver
     */
    Solver (const Dictionary& dict, const LettersSet& letters_set);

    /**
     * @brief Construye el vector de soluciones a partir de las letras de una partida.
     * @param available_letters - vector de letras disponible para la partida
     * @param score_gaming - bool indicando el tipo de partida. true indica que la partida se juega a
     * puntuación, false indica que la partida se juega a longitud.
     * @return Par con el vector de palabras que constituyen las mejores soluciones (puede haber empates) y la
     * puntuación que obtienen.
     */
    pair<vector<string>, int> getSolutions( const vector<char>& available_letters, bool score_gaming);

};
#endif //P04_JUEGO_LETRAS_SOLVER_H
