//
// Created by jbekios on 10/18/21.
//
// Controlador Cassette

#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <vector>
#include <iterator>
#include <cstdio>
#include <cstdlib>

using std::cout;
using std::endl;
using std::stack;
using std::array;
using std::queue;
using std::vector;
using std::copy;


#ifndef TEST01_PROGRAMACASSETTE_HPP
#define TEST01_PROGRAMACASSETTE_HPP

struct nodo{
    int idCancion;
    vector<int> cancionesSeleccionadas;
    int tiempoTotal;
};

typedef nodo Nodo;

class ProblemaCassette{
public:

    ProblemaCassette(int const numeroCanciones);
    Nodo resolver(void);
    vector<int> getMisCanciones(void);

private:

    stack<Nodo> pila;
    vector<int> misCanciones;
    int numeroTotalMisCanciones;
    Nodo mejorCandidato;

    void configurar(vector<int> canciones);
    void llenarPila(vector<int> canciones);
    queue<Nodo> generarListaCandidatos(Nodo n);
};


#endif //TEST01_PROGRAMACASSETTE_HPP
