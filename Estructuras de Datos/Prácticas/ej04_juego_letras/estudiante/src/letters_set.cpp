#include "letters_set.h"
#include <map>
#include <utility>
#include <iostream>
#include <string>

using namespace std;

LettersSet::LettersSet()=default;

LettersSet::LettersSet(const LettersSet &other){
    letters=other.letters;
}

bool LettersSet::insert(const pair<char,LetterInfo> & val){
    char n = val.first;
    if (!letters.count(n)) {

        letters.insert(val);
        return true;
    }

    else return false;
}

bool LettersSet::erase(const char &key) {

    if (letters.count(key)){
        letters.erase(key);
        return true;
    }

    else return false;

}

void LettersSet::clear(){
    letters.clear();
}

bool LettersSet::empty() const {
    return letters.empty();
}

unsigned int LettersSet::size() const {
    return letters.size();
}

int LettersSet::getScore(std::string word) {

    int score = 0;

    for (int i = 0; i < word.length(); i++)
        score += letters.find(word.at(i))->second.score;

    return score;
}

LettersSet& LettersSet::operator=(const LettersSet &cl) {

    this->letters=cl.letters;
    return *this;

}

LetterInfo& LettersSet::operator[](const char &val) {

    return letters.find(val)->second;
}

/**********************/

istream& operator>>(istream &is, LettersSet & cl) {

    string str;
    getline(is, str);
    char letra;
    LetterInfo aux;

    while (is){
        is >> letra;
        letra = tolower(letra);
        is >> aux.repetitions;
        is >> aux.score;
        pair<char,LetterInfo> pair(letra,aux);
        cl.insert(pair);
    }
    return is;

}

/**********************/
/********* ITERATOR **********/
/**********************/
LettersSet::Iterator::Iterator()=default;

LettersSet::Iterator::Iterator(const map<char,LetterInfo>::iterator other){
    it = other;
}

LettersSet::Iterator& LettersSet::Iterator::operator=(const Iterator &other){
    it=other.it;
    return *this;
}

LettersSet::Iterator& LettersSet::Iterator::operator=(const map<char,LetterInfo>::iterator other ){
    it=other;
    return *this;
}

bool LettersSet::Iterator::operator==(const Iterator &other){
    return this->it==other.it;
}

bool LettersSet::Iterator::operator!=(const Iterator &other){
    return this->it!=other.it;
}

LettersSet::Iterator& LettersSet::Iterator::operator++(){it++; return *this;}

pair<char,LetterInfo> LettersSet::Iterator::operator*(){return *it;}