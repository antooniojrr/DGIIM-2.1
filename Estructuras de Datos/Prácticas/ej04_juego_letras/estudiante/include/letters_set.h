#include <string>
#include <iostream>
#include <map>

using namespace std;

#ifndef _LETTER_SET_H_
#define _LETTER_SET_H_

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

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */
class LettersSet {
private:

    map<char,LetterInfo> letters;

public:
    /**
     * @brief Función friend que sobrecarga el operador de entrada >> para la clase LettersSet
     * @param Objetos istream y LettersSet (flujo de entrada y LettersSet, cuyos campos contendrán la información leída)
     */
    friend istream& operator>>(istream&, LettersSet&);

    /**
     * @brief Constructor por defecto
     */
    LettersSet();

    /**
     * @brief Constructor de copia
     * @param other - el objeto a copiar
     * @post Un LettersSet idéntico a other
     */
    LettersSet(const LettersSet & other);

    /**
     * @brief Inserta un elemento en el LettersSet
     * @pre val no pertenece al LettersSet
     * @param val - par a insertar
     * @post val pertenece al LettersSet
     * @return booleano que devuelve true si se ha podido insertar y false si no se ha podido insertar
     */
    bool insert(const pair< char,LetterInfo > & val);

    /**
     * @brief Elimina un caracter del LettersSet
     * @pre key pertenece al LettersSet
     * @param key - carácter a eliminar
     * @post key no pertenece al LettersSet
     * @return booleano que devuelve true si key se ha eliminado correctamente y false si no ha sido eliminado
     */
    bool erase(const char & key);

    /**
     * @brief Elimina el contenido del LettersSet
     * @post LettersSet vacío
     */
    void clear();

    /**
     * @brief Consulta si el LettersSet está vacío
     * @return booleano que devuelve true si el LettersSet está vacío, falso en sentido contrario
     */
    bool empty() const;

    /**
     * @brief Tamaño del LettersSet
     * @return Número de elementos del LettersSet
     */
    unsigned int size() const;

    /**
     * @brief Calcula la puntuación de una palabra
     * @param word - Palabra cuya puntuación se va a calcular
     * @return Número de puntos de word
     */
    int getScore(string word);

    /**
     * @brief Sobrecarga del operador de asignación para la clase LettersSet
     * @param cl - LettersSet a copiar
     * @return Referencia al objeto this para poder encadenar el opeardor
     */
    LettersSet &operator=(const LettersSet & cl);

    /**
     * @brief Sobrecarga del opeardor de consulta para la clase LettersSet
     * @param val - Carácter a consultar
     * @return LetterInfo con la información del carácter consultado
     */
    LetterInfo &operator[](const char &val);

    /**
     * @brief Clase Iterator
     *
     * Clase que permite iterar sobre los objetos de LettersSet
     */
    class Iterator {
    private:
        map<char,LetterInfo>::iterator it;
    public:

        /**
         * @brief Constructor por defecto
         */
        Iterator();

        /**
         * @brief Constructor de copia
         * @param other - Elemento a copiar
         */
        Iterator(const map<char,LetterInfo>::iterator other);

        /**
         * @brief Sobrecarga del operador de asignación para la clase Iterator
         * @param other - iterador a copiar
         * @return Referencia al objeto this para pdoer encadenar el operador
         */
        Iterator& operator=(const Iterator &other);

        /**
         * @brief Sobrecarga del operador de asignación para la clase Iterator
         * @param other - mapa a copiar
         * @return Referencia al objeto this para poder encadenar el operador
         */
        Iterator& operator=(const map<char,LetterInfo>::iterator other );

        /**
         * @brief Sobrecarga del operador de comparación de igualdad entre dos iteradores
         * @param other - iterador a comparar
         * @return booleano que devuelve true si son iguales, false si no lo son
         */
        bool operator==(const Iterator &other);

        /**
         * @brief Sobrecarga del operador de comparación de desigualdad entre dos iteradores
         * @param other - iterador a comparar
         * @return booleano que devuelve true si son distintos, false si no lo son
         */
        bool operator!=(const Iterator &other);

        /**
         * @brief Sobrecarga del operador ++ para la clase Iterator
         * @return iterador siguiente al actual
         */
        Iterator& operator++();

        /**
         * @brief Sobrecarga del operador * para la clase Iterator
         * @return Par al que hace referencia el iterador actual
         */
        pair<char,LetterInfo> operator*();
    };

    /**
     * @brief Sitúa el iterador en la primera posición
     * @return Iterador en posición begin()
     */
    Iterator begin() {return letters.begin();}

    /**
     * @brief Sitúa el iterador en la última posición
     * @return Iterador en posición end()
     */
    Iterator end() {return letters.end();}


};
#endif