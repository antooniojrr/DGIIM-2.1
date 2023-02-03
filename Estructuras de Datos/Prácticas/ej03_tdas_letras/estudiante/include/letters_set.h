#include <string>
#include <iostream>
#include <map>

using namespace std;

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */
struct LetterInfo {
    int repetitions;
    int score;
};

class Iterator {

private:

    map<char,LetterInfo>::iterator it;

public:

    Iterator();
    Iterator(const map<char,LetterInfo>::const_iterator other);
    const Iterator& operator=(const Iterator &other);
    const Iterator& operator=(const map<char,LetterInfo>::iterator other );
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    Iterator& operator++();
    const char operator*();

};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */
class LetterSet {
private:

    map<char,LetterInfo> letters;

public:

    friend ostream& operator<<(ostream&, const LetterSet&);
    friend istream& operator>>(istream&, const LetterSet&);

    LetterSet();

    LetterSet(const LetterSet & other);

    bool insert(const pair< char,LetterInfo > & val);

    bool erase(const char & key);

    void clear();

    bool empty() const;

    unsigned int size() const;

    LetterSet &operator=(const LetterSet & cl);

    LetterInfo &operator[](const char &val);

    Iterator begin() const{return letters.begin();}

    Iterator end() const{return letters.end();}

};

#endif
