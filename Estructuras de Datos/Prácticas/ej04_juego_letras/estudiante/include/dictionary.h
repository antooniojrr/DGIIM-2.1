//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {

private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        /**
         * @brief Sobrecarga del operador de asignación
         * @param rhs - a copiar
         * @return bool que indica el resultado de la operación lógica ==
         */

        inline bool operator==(const char_info &rhs) {
            return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        /**
         * @brief Sobrecarga del operador de diferencia
         * @param rhs - a comparar si es diferente
         * @return bool que indica el resultado de la operación lógica !=
         */
        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        /**
         * @brief Sobrecarga del operador de referencia
         * @return Referencia al mismo objeto
         */
        inline bool operator*() { return this->character; }

        /**
         * @brief Sobrecarga del operador de salida
         * @param os - flujo a utilizar
         * @param other - objeto de referencia
         * @return Flujo de salida del objeto
         */
        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
            os << other.character << (other.valid_word ? "✓" : "×");
            return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Calcula el número de ocurrencias de una letra en el subárbol que cuelga del nodo pasado como argumento
     * @param curr_node - nodo del cual cuelga el subárbol donde contaremos las ocurrencias de la letra
     * @param c - letra de la que queremos calcular las ocurrencias
     * @return Número de ocurrencias de c
     */
    int getOccurrences(node curr_node, char c);

    /**
     * @brief Esta función nos va a devolver una pareja de valores, el número de ocurrencias del carácter en los
     * nodos que cuelgan del nodo actual, y el número de palabras que terminan por debajo del nodo actual.
     * @param curr_node - nodo actual
     * @param c - letra de la que queremos calcular las ocurrencias
     * @return Un par con las ocurrencias del carácter en los nodos que cuelgan del nodo actual, y el número de
     * palabras que terminan por debajo del nodo actual.
     */
    std::pair<int, int> getTotalUsages(node curr_node, char c);


public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Esta función debe devolver el número de ocurrencias del carácter que se pasa como argumento
     * en nuestro árbol.
     * @param c - caracter del cual queremos calcular las ocurrencias.
     * @return Número de ocurrencias de c en el árbol
     */

    int getOccurrences(const char c);

    /**
     * @brief Esta función se encarga de contar el número de usos de la letra para formar palabras en el diccionario.
     * @param c - letra de la cual queremos calcular el número de usos
     * @return Número de usos de c para formar palabras en el diccionario
     */
    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    class iterator {
    private:
        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:
        /**
         * @brief Constructor por defecto
         */
        iterator();

        /**
         * @brief Constructor de copia
         * @param iter - a copiar
         */
        iterator(tree<char_info>::const_preorder_iterator iter);

        /**
         * @brief Sobrecarga de operador*
         */
        std::string operator*();

        /**
         * @brief Sobrecarga de operador++
         */
        iterator &operator++();

        /**
         * @brief Sobrecarga de operador==
         */
        bool operator==(const iterator &other);

        /**
         * @brief Sobrecarga de operadores!=
         */
        bool operator!=(const iterator &other);

    };

    /**
     * @brief Método que devuelve el comienzo del iterador
     * @return Iterador en su posición primera
     */
    iterator begin() const;

    /**
     * @brief Método que devuelve el final del interador
     * @return Iterador en su posición final
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    /**
     * @brief Iterador que se va a encargar de recorrer la estructura del diccionario explorando sólo las
     * ramas de la estructura que pueden generar palabras válidas dada una bolsa de letras.
     */
    class possible_words_iterator {
    public:

        /**
         * @brief Constructor por defecto
         */
        possible_words_iterator();

        /**
         * @brief Constructor de copia a partir de los datos privados de otro possible_words_iterador
         * @param current_node - a copiar
         * @param available_letters - a copiar
         */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Constructor de copia a partir de otro possible_words_iterator
         * @param other - a copiar
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Sobrecarga operador =
         * @param other - a igualar
         * @return Nuevo possible_words_iterator
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Sobrecarga operador ==
         * @param other - a comparar
         * @return Resultado operación lógica ==
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Sobrecarga operador !=
         * @param other - a comparar
         * @return Resultado operación lógica !=
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Sobrecarga operador ++
         * @return Nuevo possible_words_iterator
         */
        possible_words_iterator &operator++();

        /**
         * @brief Sobrecarga operador *()
         * @return Referencia al mismo objeto
         */
        std::string operator*() const;

    private:
        multiset<char> available_letters;
        int level;
        node current_node;
        string current_word;

        /**
         * @brief Funcion auxiliar para la sobrecarga del operador++. Comprueba si el hermano del nodo actual
         * es una opcion valida para ser la siguiente posicion del iterador
         * @return true o false dependiendo de si es o no valida
         */
        bool check_sibling();

        /**
         * @brief Funcion auxiliar para la sobrecarga del operador++. Comprueba si el hijo a la izda del nodo actual
         * es una opcion valida para ser la siguiente posicion del iterador
         * @return true o false dependiendo de si es o no valida
         */
        bool check_child();

        /**
         * @brief Funcion auxiliar para la sobrecarga del operador++. Comprueba si entre los hijos del nodo actual
         * del nodo actual se encuentra alguna opcion valida para ser la siguiente posicion del iterador
         * @param iter iterador pasado por referencia del cual se comprobarán los hijos y que se actualizará.
         * @return true o false dependiendo de si encuentra o no una posición valida
         * @post si devuelve true, iter se situará en la posición encontrada. Si es false, el valor de iter no es fiable
         */
        bool check_children(Dictionary::possible_words_iterator &iter);

        /**
         * @brief Funcion auxiliar para la sobrecarga del operador++. Comprueba si entre los hermanos del nodo actual
         * del nodo actual se encuentra alguna opcion valida para ser la siguiente posicion del iterador
         * @param iter iterador pasado por referencia del cual se comprobarán los hermanos y que se actualizará.
         * @return true o false dependiendo de si encuentra o no una posición valida
         * @post si devuelve true, iter se situará en la posición encontrada. Si es false, el valor de iter no es fiable
         */
        bool check_siblings(Dictionary::possible_words_iterator &iter);

    };

    /**
     * @brief Método que devuelve el comienzo del iterador possible_words_iterator
     * @return Iterador en su posición primera
     */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief Método que devuelve el final del interador possible_words_iterator
     * @return Iterador en su posición final
     */
    possible_words_iterator possible_words_end() const;

};


#endif //TREE_DICTIONARY_HPP
