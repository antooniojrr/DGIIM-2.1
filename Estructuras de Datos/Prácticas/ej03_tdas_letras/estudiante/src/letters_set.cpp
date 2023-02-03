#include "letters_set.h"
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;

LetterSet::LetterSet()=default;

LetterSet::LetterSet(const LetterSet &other){
    letters=other.letters;
}

bool LetterSet::insert(const pair<char,LetterInfo> & val){
    char n=val.first;
    if (!letters.count(n)) {

        letters.insert(val);
        return true;
    }

    else return false;
}

bool LetterSet::erase(const char &key) {

    if (letters.count(key)){
        letters.erase(key);
        return true;
    }

    else return false;

}

void LetterSet::clear(){
    letters.clear();
}

bool LetterSet::empty() const {
    return letters.empty();
}

unsigned int LetterSet::size() const {
    return letters.size();
}

LetterSet& LetterSet::operator=(const LetterSet &cl) {

    this->letters=cl.letters;
    return *this;

}

LetterInfo& LetterSet::operator[](const char &val) {

    return letters.at(val);
}

/******************************************************************/

ostream& operator<<(ostream &os, const LetterSet & cl) {
    os << "Letra   Cantidad   Puntos" << endl;
    Iterator it=cl.begin();
    for (; it != cl.end(); it++)


}
ostream& operator<<(ostream &os, const LetterSet & cl);

/******************************************************************/
/************************* ITERARTOR ******************************/
/******************************************************************/
Iterator::Iterator()=default;

Iterator::Iterator(const map<char,LetterInfo>::const_iterator other){it=other;}

const Iterator& Iterator::operator=(const Iterator &other){
    it=other.it;
    return *this;
}

const Iterator& Iterator::operator=(const map<char,LetterInfo>::iterator other ){
    it=other;
    return *this;
}

bool Iterator::operator==(const Iterator &other){
    return this->it==other.it;
}

bool Iterator::operator!=(const Iterator &other){
    return this->it!=other.it;
}

Iterator& Iterator::operator++(){it++; return *this;}

const char Iterator::operator*(){return it->first;}



