//
// Created by antoniojrr on 25/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H
#define P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H

#include "dictionary.h"
#include "letters_set.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
/**
 * @brief Nuevo solver más eficiente, cuya diferencia con el anterior es que ahora solo se itera sobre las palabras
 * válidas, reduciendo así el número de elementos explorados
 */
class Solver_eficiente{

private:

    Dictionary diccionario;
    LettersSet letras;


public:

    /**
     * @brief Constructor por parámetros. Crea un solver_eficiente que tiene asociado un Dictionary y un LetterSet
     * @param dict - dictionary asociado al nuevo objeto solver_eficiente
     * @param letters_set - letters_set asociado al nuevo objeto solver_eficiente
     */
    Solver_eficiente (const Dictionary& dict, const LettersSet& letters_set);

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
#endif //P04_JUEGO_LETRAS_SOLVER_EFICIENTE_H