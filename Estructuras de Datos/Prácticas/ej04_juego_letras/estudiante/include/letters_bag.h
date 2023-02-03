#ifndef _LETTERS_BAG_H_
#define _LETTERS_BAG_H_
#include "bag.h"
#include "letters_set.h"
/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag{
private:
    Bag <char> letters;
public:

    /**
     * @brief Constructor por defecto
     */
    LettersBag() = default;

    /**
     * @brief Constructor de copia
     * @param inic - LettersBag a copiar
     * @post LettersBag idéntico a inic
     */
    LettersBag(LettersSet inic);

    /**
     * @brief Introduce una letra en la bolsa
     * @pre l no pertenece a la bolsa
     * @param l - letra a introducir
     * @post l pertenece a la bolsa
     */
    void insertLetter (const char& l);

    /**
     * @brief Extrae una letra aleatoria de la bolsa, eliminándola del conjunto
     * @pre La bolsa no está vacía
     * @post La letra ya no pertenece al conjunto
     * @return Letra extraída
     */
    char extractLetter ();

    /**
     * @brief Extrae un conjunto de letras, eliminándolas del conjunto
     * @pre num es menor que el número de elementos del conjunto
     * @param num - Número de letras a extraer
     * @return Lista con las letras extraídas aleatoriamente
     */
    vector<char> extractLetters(int num);

    /**
     * @brief Vacía la LettersBag
     * @post La LettersBag está vacía
     */
    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return int con el tamaño de la bolsa
     */
    unsigned int size();

    /**
     * @brief Sobrecarga del operador de asignación para la clase LettersBag
     * @param other - LettersBag a copiar
     * @return Referencia a this de esta forma el opeardor puede ser encadenado
     */
    LettersBag& operator= (const LettersBag &other);
};

#endif
