#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <list>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T> &aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map &operator=(const string_map &d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T> &par);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/
    int count(const string &clave) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T &at(const string &clave) const;

    T &at(const string &clave);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string &clave);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        vector<Nodo *> siguientes;
        T *definicion;

        Nodo();

        Nodo(T *def);

        void destruirHaciaAbajo();

        int cantidadHijos();
    };

    Nodo *raiz;
    int size_;

    void destruirMapa();

    void copiarSiguientes(Nodo *nodo, Nodo *aCopiar);
};

template<typename T>
string_map<T>::Nodo::Nodo() : siguientes(256, nullptr), definicion(nullptr) {}

template<typename T>
string_map<T>::Nodo::Nodo(T *def) : siguientes(256, nullptr), definicion(def) {}

/**
 * destruye el nodo this y todo lo que tenga debajo
 **/
template<typename T>
void string_map<T>::Nodo::destruirHaciaAbajo() {
    for (Nodo *nodo: this->siguientes) {
        if (nodo != nullptr) {
            nodo->destruirHaciaAbajo();
            nodo = nullptr;
        }
    }
    this->definicion = nullptr;
    delete this;
}

//Dice si este nodo tiene al menos un hijo valido
template<typename T>
int string_map<T>::Nodo::cantidadHijos() {
    int res = 0;
    for (Nodo *nodo: this->siguientes) {
        if (nodo != nullptr) {
            res++;
        }
    }
    return res;
}

#include "string_map.hpp"

#endif // STRING_MAP_H_
