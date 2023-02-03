/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author Antonio Javier Rodríguez Romero
 */


#include <stack>
#include "maxqueue.h"

using namespace std;


ostream& operator<< (ostream& flujo, const element& p){
    flujo << p.value << "," << p.maximum;
    return flujo;
}

void MaxQueue::push(int n) {
    stack<element> aux;
    element nuevo;
    nuevo.value=n;
    nuevo.maximum= n;

    int m=size();
    for (int i=0;i<m;i++) {
        aux.push(front());
        pop();
    }
    _data.push(nuevo);
    bool max_bigger=false;
    for (int i=0;i<m;i++) {
        if (!max_bigger) {
            if (aux.top().maximum < nuevo.value)
                aux.top().maximum = nuevo.value;
            else max_bigger=true;
        }
        _data.push(aux.top());
        aux.pop();
    }

}

/*void MaxQueue::push(element n) {

    stack<element> aux;
    n.maximum = n.value;

    int m=size();
    for (int i=0;i<m;i++) {
        aux.push(front());
        pop();
    }
    _data.push(n);

    for (int i=0;i<m;i++) {
        if (aux.top().maximum<n.value)
            aux.top().maximum=n.value;
        _data.push(aux.top());
        aux.pop();
    }

}*/

void MaxQueue::pop() {
    if (!empty())
        _data.pop();
}

element MaxQueue::front() const{

    if (!empty())
        return _data.top();
    else {
        element vacio{};
        vacio.value=0;
        vacio.maximum=-1; // Lo cual es imposible dado que value es mayor
        return vacio;
    }
}

bool MaxQueue::empty() const {

    return _data.empty();
}

int MaxQueue::size() const {

    return _data.size();

}

MaxQueue::MaxQueue()=default;

