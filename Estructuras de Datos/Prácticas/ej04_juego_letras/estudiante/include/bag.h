#ifndef __BAG_H__
#define __BAG_H__

#include <vector>
#include "stdlib.h"
using namespace std;

/**
 *  \brief TDA Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>

class Bag{
private:
    vector<T> v;
public:
    /**
     * @brief Constructor por defecto
     */
    Bag() = default;

    /**
     * @brief Constuctor de copia
     * @param other - el objeto a copiar
     * @post Una bolsa idéntica a other
     */
    Bag(const Bag<T> &other){
        *this = other;
    }

    /**
     * @brief Añade un elemento a la bolsa
     * @param element - el objeto a añadir
     * @post element está en la bolsa
     */
    void add(const T & element){
        v.push_back(element);
    }

    /**
     * @brief Obtiene un elemento aleatorio de la bolsa
     * @return Un elemento aleatorio de la bolsa
     * @post El elemento extraído ya no pertenece a la bolsa
     */
    T get(){
        int indice = rand() % v.size();

        T result = v.at(indice);
        v[indice] = v[size()-1];
        v.pop_back();

        return result;
    }

    /**
     * @brief Vacía la bolsa
     * @post La bolsa está vacía
     */
    void clear(){
        v.clear();
    }

    /**
     * @brief Obtiene el tamaño de la bolsa
     * @return El tamaño de la bolsa
     */
    unsigned int size() const{
        return v.size();
    }

    /**
     * @brief Consulta si la bolsa está vacía
     * @return Booleano que devuelve true si la bolsa está vacía y false si no lo está
     */
    bool empty(){
        return v.empty();
    }

    /**
     * @brief Sobrecarga de operador = para la clase Bolsa
     * @param other - bolsa de la que se copian los datos
     * @return Bolsa con los datos de other
     */
    const Bag<T>& operator= (const Bag<T> &other){
        for (int i = 0; i < other.size(); i++)
            v[i] = other.v[i];

        return *this;
    }
};

#endif
