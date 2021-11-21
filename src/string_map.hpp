
#include "string_map.h"

template<typename T>
string_map<T>::string_map() : raiz(nullptr), size_(0) {}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() { *this = aCopiar; }
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {

    this->destruirMapa();
    this->size_ = 0;

    if (d.empty()) {
        this->raiz = nullptr;
        return *this;
    } else {
        //this->copiarHaciaAbajo(this->raiz);

        if (d.raiz->definicion != nullptr) {
            this->raiz = new Nodo(d.raiz->definicion);
            this->size_++;
        } else {
            this->raiz = new Nodo();
        }

        for (int i = 0; i < d.raiz->siguientes.size(); i++) {
            if (d.raiz->siguientes[i] != nullptr) {
                this->raiz->siguientes[i] = new Nodo();
                this->copiarSiguientes(this->raiz->siguientes[i], d.raiz->siguientes[i]);
            }
        }
    }

}

template<typename T>
void string_map<T>::copiarSiguientes(string_map::Nodo *nodo, string_map::Nodo *aCopiar) {
    if (aCopiar->definicion != nullptr) {
        nodo->definicion = aCopiar->definicion;
        this->size_++;
    }
    for (int i = 0; i < aCopiar->siguientes.size(); i++) {
        if (aCopiar->siguientes[i] != nullptr) {
            nodo->siguientes[i] = new Nodo();
            this->copiarSiguientes(nodo->siguientes[i], aCopiar->siguientes[i]);
        }
    }

}


template<typename T>
string_map<T>::~string_map() {
    this->destruirMapa();
}


template<typename T>
void string_map<T>::destruirMapa() {
    if (this->size() == 0) {
        return;
    }
    this->raiz->destruirHaciaAbajo();
    this->size_ = 0;
    this->raiz = nullptr;
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

    /**
    //Esta parte es para mantener la lista de palabras definidas
    bool estabaDefinida = false;
    for (string palabra: this->palabrasDefinidas_) {
        if (palabra == par.first) {
            estabaDefinida = true;
            break;
        }
    }
    if (not estabaDefinida) {
        this->palabrasDefinidas_.push_back(par.first);
    } **/
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

