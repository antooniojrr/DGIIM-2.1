/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Antonio Javier Rodríguez Romero
 */

#ifndef _MAXQUEUE_H_
#define _MAXQUEUE_H_

#include <stack>
#include <iostream>

using namespace std;

struct element {
    int value; // Current value to store
    int maximum; // Current max value in the structure

};

class MaxQueue{

private:
    /**
     * @brief Objeto de la clase stack de la STL que guardará objetos de tipo element, con un valor y guardando el máximo.
     */
     stack<element> _data;

public:

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase MaxQueue con O elementos
      * @return MaxQueue, el objeto creado.
      */
    MaxQueue();

    /**
      @brief Añade un elemento a la cola.
      @param n Valor a añadir a la cola
      @post Se revisarán todos los máximos de manera que queden correctamente asignados
    **/
    void push(int n);

    /**
      @brief Elimina el primer elemento de la cola
      @post La cola queda con un elemento nuevo al frente.
    **/
    void pop();

    /**
      @brief Consulta el elemento al frente de cola, tanto el valor como el máximo guardado
      @return objeto "element" situado al principio de la cola, en el frente
    **/
    element front() const;

    /**
      @brief Comprueba si la cola está vacía. Es decir, size()=0.
      @post será true si está vacía y false si hay algún elemento
      @return bool empty
    **/
    bool empty() const;

    /**
      @brief Consulta el número de elementos guardados en la cola
      @post size() >= 0
      @return número de elementos guardados.
    **/
    int size() const;

};

ostream& operator<< (ostream& flujo, const element& p);

#endif // _MAXQUEUE_H_
