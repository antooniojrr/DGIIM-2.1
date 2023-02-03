//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>



///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){

    int ocur=0;

    if (!(curr_node.right_sibling().is_null())) ocur += getOccurrences(curr_node.right_sibling(), c);
    if (!(curr_node.left_child().is_null())) ocur += getOccurrences(curr_node.left_child(),c);

    return (tolower(c)==tolower(((*curr_node).character))) ? ocur+1 : ocur;

}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
    std::pair<int,int> results;

    std::pair<int,int> results_lc;
    if (!(curr_node.left_child().is_null()))
        results_lc = getTotalUsages(curr_node.left_child(), c);
    std::pair<int,int> results_rs;
    if (!(curr_node.right_sibling().is_null()))
        results_rs = getTotalUsages(curr_node.right_sibling(), c);

    results.first = results_lc.first + results_rs.first;
    results.second = results_lc.second + results_rs.second;

    if (tolower((*curr_node).character)==tolower(c)) results.first += results_lc.second;

    if ((*curr_node).valid_word) {
        results.second++;
        if (tolower((*curr_node).character)==tolower(c)) results.first ++;
    }

    return results;

}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

/*std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}*/

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    return getOccurrences(words.get_root(), c);
}

int Dictionary::getTotalUsages(const char c){
    return getTotalUsages(words.get_root(),c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator()=default;

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->iter=(iter);
}

std::string Dictionary::iterator::operator*() {
    return curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {

    int level;
    bool valida = false;

    do {
        level=iter.get_level();
        ++iter;
        if (iter.get_level()!=0){

            if(iter.get_level() > level)
                curr_word.push_back((*iter).character);

            else if(iter.get_level()==level) {
                curr_word.pop_back();
                curr_word.push_back((*iter).character);
            }

            else {
                int dif=level-iter.get_level();
                curr_word=curr_word.substr(0,curr_word.length()-dif-1);
                curr_word.push_back((*iter).character);
            }

            if ((*iter).valid_word)
                valida=true;
        }

        else {
            curr_word="";
        }

    } while (!valida && iter.get_level()!=0);

    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return iter==other.iter;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return iter!=other.iter;
}

Dictionary::iterator Dictionary::begin() const {
    return iterator(words.cbegin_preorder());
}

Dictionary::iterator Dictionary::end() const {
    return iterator(words.cend_preorder());
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    possible_words_iterator iter(this->words.get_root(),available_characters);
    ++iter;
    return iter;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {

    possible_words_iterator iter(words.get_root(),vector<char>());

    return iter;
}

Dictionary::possible_words_iterator::possible_words_iterator() = default;


Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){
    this->current_node=current_node;

    for (int i=0; i< available_letters.size(); i++)
        this->available_letters.insert(available_letters[i]);

    current_word="";

    node temp=current_node;
    while(!(temp.parent().is_null())) {
        current_word = (*temp).character + current_word;
        temp=temp.parent();
    }

}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    *this=other;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    this->available_letters=other.available_letters;
    this->level=other.level;
    this->current_node=other.current_node;
    this->current_word=other.current_word;

    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {

    bool iguales=false;
    bool letras_igual=true;
    if (this->available_letters.size()==other.available_letters.size()){
        multiset<char> tmp(other.available_letters);
        multiset<char>::iterator iter;
        multiset<char>::iterator it;
        for(it=available_letters.begin();it!=available_letters.end();it++) {
            char c=(*it);
            iter=tmp.find(c);
            if (iter!=tmp.end())
                tmp.erase(iter);
            else {
                letras_igual=false;
            }
        }
    }

    else
        letras_igual=false;

    if (    letras_igual                                        &&
            this->level==other.level                            &&
            this->current_node==other.current_node              &&
            this->current_word==other.current_word )
        iguales=true;

    return iguales;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !(*(this)==other);
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

    Dictionary::possible_words_iterator tmp;
    bool puede;

    do {
        tmp=*this;
        puede= check_children(tmp);

        if (!puede) {
            tmp=*this;
            puede=check_siblings(tmp);

            while(!puede && level>0) {
                available_letters.insert((*current_node).character);
                current_word.pop_back();
                current_node=current_node.parent();
                level--;
                tmp=*this;
                puede=check_siblings(tmp);
            }
            if(puede) {
                this->current_node=tmp.current_node;
                available_letters.insert(current_word.at(current_word.size()-1));
                current_word.pop_back();
                current_word +=(*current_node).character;
                available_letters.erase(available_letters.find((*current_node).character));
            }

        }

        else {
            level++;
            current_node=tmp.current_node;
            current_word +=(*current_node).character;
            available_letters.erase(available_letters.find((*current_node).character));
        }
    } while (!(*current_node).valid_word && level != 0);

    if (level==0) available_letters.clear();

    return *this;

}

std::string Dictionary::possible_words_iterator::operator*() const {
    return current_word;
}


///////////////////////////////////////////////////////////////////////////////
//                               Aux functions                               //
///////////////////////////////////////////////////////////////////////////////

bool Dictionary::possible_words_iterator::check_child() {

    bool puede=false;
    multiset<char>::iterator iter;

    if (!(current_node.left_child().is_null())) {

        iter = available_letters.find((current_node.left_child().operator*()).character);

        if (iter!=available_letters.end()) {
            current_node=current_node.left_child();
            current_word+=(*current_node).character;
            level++;
            available_letters.erase(iter);
            puede=true;
        }

    }

    return puede;

}

bool Dictionary::possible_words_iterator::check_sibling() {

    bool puede=false;
    multiset<char>::iterator iter;

    if(!(current_node.right_sibling().is_null())) {

        char c=(*current_node).character;
        iter = available_letters.find((current_node.right_sibling().operator*()).character);

        if (iter!=available_letters.end()) {
            current_node=current_node.right_sibling();
            current_word.pop_back();
            current_word+=(*current_node).character;
            available_letters.erase(iter);
            available_letters.insert(c);
            puede=true;
        }

    }

    return puede;
}

bool Dictionary::possible_words_iterator::check_children(Dictionary::possible_words_iterator &iter) {

    bool puede=iter.check_child();
    if (!puede && !(iter.current_node.left_child().is_null())) {

        iter.current_node=iter.current_node.left_child();
        iter.level++;
        iter.current_word += '\0';

        while(!(iter.current_node.right_sibling().is_null()) && !puede) {
            puede=iter.check_sibling();
            if(!puede)
                iter.current_node=iter.current_node.right_sibling();
        }
    }
    return puede;
}

bool Dictionary::possible_words_iterator::check_siblings(Dictionary::possible_words_iterator &iter) {
    bool puede=iter.check_sibling();
    while(!puede && !(iter.current_node.right_sibling().is_null())) {
        iter.current_node=iter.current_node.right_sibling();
        puede=check_sibling();
    }

    return puede;
}

