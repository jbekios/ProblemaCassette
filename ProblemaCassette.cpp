//
// Created by jbekios on 10/18/21.
//

#include "ProblemaCassette.hpp"

ProblemaCassette::ProblemaCassette(int const universoCanciones){
    /**
      Constructor: Se construye un listado de canciones con
      tiempos generados al azar. El número de canciones viene
      determinado por el parámetro universoCanciones.

      @param universoCanciones Cantidad de caciones generadas para resolver el
      problema.
    */
    numeroTotalMisCanciones = universoCanciones;
    // Semilla para generar números pseudoaleatorios
    srand(0);
    for(int i=0; i < numeroTotalMisCanciones; i++){
        // Obtengo números aleatorios entre 1 y 12
        int tiempoEnMinutos =  1 + rand() % 12;
        misCanciones.push_back(tiempoEnMinutos);
    }

    configurar(misCanciones);

}

Nodo ProblemaCassette::resolver(void){
    while(!pila.empty()){
        Nodo candidato = pila.top();
        pila.pop();
        //showNodo(candidato);
        //Candidato es mejor solucion
        if (candidato.tiempoTotal <= 30){
            // Si todavia se pueden agregar mas canciones
            if (candidato.tiempoTotal >= mejorCandidato.tiempoTotal){
                mejorCandidato.idCancion = candidato.idCancion;
                mejorCandidato.cancionesSeleccionadas = candidato.cancionesSeleccionadas;
                mejorCandidato.tiempoTotal = candidato.tiempoTotal;
            }
            //Generar lista de sucesores
            queue<Nodo> candidatos = generarListaCandidatos(candidato);
            //Agrego nuevos candidatos a la pila
            while(!candidatos.empty()){
                Nodo naux = candidatos.front();
                candidatos.pop();
                pila.push(naux);
            }
        }
    }

    return mejorCandidato;
}

vector<int> ProblemaCassette::getMisCanciones(void){
    return misCanciones;
}

void ProblemaCassette::configurar(vector<int> canciones){
    //Inicializo mejorCandidado con el peor caso
    mejorCandidato.idCancion = -1;
    mejorCandidato.tiempoTotal = -1;

    //Lleno la pila con las canciones generadas por el Constructor
    llenarPila(canciones);
}

void ProblemaCassette::llenarPila(vector<int> canciones){
    // Creo nodos estados y los agrego a la pila
    for(int i=canciones.size()-1; i >= 0; i--){
        Nodo n;
        n.idCancion = i;
        n.tiempoTotal = canciones[i];
        pila.push(n);
    }
}

queue<Nodo> ProblemaCassette:: generarListaCandidatos(Nodo n){
    queue<Nodo> listaCandidatos;
    for(int i=n.idCancion+1; i < numeroTotalMisCanciones; i++){
        Nodo candidatoNuevo;
        candidatoNuevo.idCancion = i;
        //Agrego el tiempo de la actual cancion
        candidatoNuevo.tiempoTotal = misCanciones[i];
        candidatoNuevo.tiempoTotal += n.tiempoTotal;
        copy(n.cancionesSeleccionadas.begin(),
             n.cancionesSeleccionadas.end(),
             back_inserter(candidatoNuevo.cancionesSeleccionadas));
        candidatoNuevo.cancionesSeleccionadas.push_back(n.idCancion);
        listaCandidatos.push(candidatoNuevo);
    }

    return listaCandidatos;
}
