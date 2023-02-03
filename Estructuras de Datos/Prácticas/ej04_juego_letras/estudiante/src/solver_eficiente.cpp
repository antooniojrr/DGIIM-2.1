//
// Created by antoniojrr on 12/12/22.
//

#include <string>
#include <vector>
#include <utility>
#include "dictionary.h"
#include "letters_set.h"
#include "solver_eficiente.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                             Public functions                              //
///////////////////////////////////////////////////////////////////////////////

Solver_eficiente::Solver_eficiente(const Dictionary &dict, const LettersSet &letters_set) {

    this->diccionario=dict;
    this->letras=letters_set;

}

pair<vector<string>,int> Solver_eficiente::getSolutions(const vector<char> &available_letters, bool score_gaming) {

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
}


