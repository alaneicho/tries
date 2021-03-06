
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
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
    // OPTATIVO
}

/**
COUNT
* Devuelve la cantidad de apariciones de la clave (0 o 1).
* Sirve para identificar si una clave est?? definida o no.
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
  * PRE: La clave est?? definida.
  --PRODUCE ALIASING--
  -- Versi??n modificable y no modificable
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

/**
ERASE
* Dada una clave, la borra del diccionario junto a su significado.
* PRE: La clave est?? definida.
--PRODUCE ALIASING--
**/
template<typename T>
void string_map<T>::erase(const string &clave) {
    bool hayQueBorrarTodo = true;
    Nodo *ultimo_nodo_no_borrable;
    char primer_char_borrable;
    Nodo *nodo_actual = this->raiz;

    for (char i: clave) {
        if (nodo_actual->cantidadHijos() > 1 || nodo_actual->definicion != nullptr) {
            hayQueBorrarTodo = false;
            ultimo_nodo_no_borrable = nodo_actual;
            primer_char_borrable = i;
        }
        nodo_actual = nodo_actual->siguientes[int(i)];
    }
    nodo_actual->definicion = nullptr;
    this->size_--;

    if (nodo_actual->cantidadHijos() > 0) { //no hay que borrar ningun nodo
        return;
    } else if (hayQueBorrarTodo) {
        this->destruirMapa();
    } else { //se viene la borrada de nodos
        Nodo *primer_nodo_borrable = ultimo_nodo_no_borrable->siguientes[int(primer_char_borrable)];
        ultimo_nodo_no_borrable->siguientes[int(primer_char_borrable)] = nullptr;
        primer_nodo_borrable->destruirHaciaAbajo();
    }
}

template<typename T>
int string_map<T>::size() const {
    return this->size_;
}

template<typename T>
bool string_map<T>::empty() const {
    return (this->size() == 0);
}

