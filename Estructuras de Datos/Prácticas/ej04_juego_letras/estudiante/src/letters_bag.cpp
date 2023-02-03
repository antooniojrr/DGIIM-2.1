#include "letters_bag.h"
#include "letters_set.h"

LettersBag::LettersBag(LettersSet inic) {

    for (LettersSet::Iterator it = inic.begin(); it != inic.end(); ++it) {
        for (int i = 0; i < (*it).second.repetitions; i++)
            letters.add((*it).first);
    }
}

void LettersBag::insertLetter(const char &l) {
     letters.add(l);
}

char LettersBag::extractLetter (){
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num){
    vector<char> result;
    for (int i = 0; i < num; i++)
        result.push_back(letters.get());
    return result;
}

void LettersBag::clear(){
    letters.clear();
}

unsigned int LettersBag::size(){
    return letters.size();
}

LettersBag& LettersBag::operator= (const LettersBag &other){
    this->letters = other.letters;
    return *this;
}
