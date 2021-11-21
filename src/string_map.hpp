
#include "string_map.h"

template<typename T>
string_map<T>::string_map() : raiz(nullptr), size_(0) {}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() { *this = aCopiar; }
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    // COMPLETAR
}

template<typename T>
string_map<T>::~string_map() {
    this->destruirMapa();
}


template<typename T>
void string_map<T>::destruirMapa() {

}

template<typename T>
void string_map<T>::insert(const pair<string, T> &par) {
    if (this->size() == 0) {
        this->raiz = new Nodo();
    }
    Nodo *nodo_actual = this->raiz;
    for (char i: par.first) {
        if (nodo_actual->siguientes[int(i)] == nullptr) {
            nodo_actual->siguientes[int(i)] = new Nodo();
        }
        nodo_actual = nodo_actual->siguientes[int(i)];
    }
    if (nodo_actual->definicion == nullptr) {
        this->size_++;
    }
    nodo_actual->definicion = new T(par.second);
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
    // OPTATIVO
}

/**
COUNT
* Devuelve la cantidad de apariciones de la clave (0 o 1).
* Sirve para identificar si una clave está definida o no.
**/
template<typename T>
int string_map<T>::count(const string &clave) const {
    if (this->size() == 0) { return 0; }

    Nodo *nodo_actual = this->raiz;
    for (char i: clave) {
        nodo_actual = nodo_actual->siguientes[int(i)];
        if (nodo_actual == nullptr) {
            return 0;
        }
    }
    if (nodo_actual->definicion == nullptr) {
        return 0;
    } else {
        return 1;
    }
}

/**
  AT
  * Dada una clave, devuelve su significado.
  * PRE: La clave está definida.
  --PRODUCE ALIASING--
  -- Versión modificable y no modificable
  **/
template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *nodo_actual = this->raiz;
    for (char i: clave) {
        nodo_actual = nodo_actual->siguientes[int(i)];
    }
    return nodo_actual->definicion;
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *nodo_actual = this->raiz;
    for (char i: clave) {
        nodo_actual = nodo_actual->siguientes[int(i)];
    }
    return *nodo_actual->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    // COMPLETAR
}

template<typename T>
int string_map<T>::size() const {
    return this->size_;
}

template<typename T>
bool string_map<T>::empty() const {
    return (this->size() == 0);
}

