#include <iostream>
#include "ProblemaCassette.hpp"

int main() {
    ProblemaCassette pc(15);
    Nodo resultado = pc.resolver();
    vector<int> listadoMisCanciones = pc.getMisCanciones();

    // Mostrar el universo de canciones
    cout << "LISTADO TOTAL DE CANCIONES:" << endl;
    cout << "==========" << endl << endl;
    int index = 0;
    cout << "| ";
    for(int i: listadoMisCanciones)
        cout << index++ << " : " << i << " | " ;
    cout << endl << endl;

    // Imprimir el resultado
    cout << "RESULTADO:" << endl;
    cout << "==========" << endl << endl;
    cout << "Última canción seleccionada: " << resultado.idCancion << endl;
    cout << "Tiempo máximo utilzado en el cassette: " << resultado.tiempoTotal << endl;
    cout << "Canciones en el cassette:" << endl;
    cout << "| " << resultado.idCancion << " : " << listadoMisCanciones[resultado.idCancion] << " | ";
    for(int i: resultado.cancionesSeleccionadas){
        cout << "| " << i << " : " << listadoMisCanciones[i] << " | ";
    }
    cout << endl;


}