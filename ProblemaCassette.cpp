//
// Created by jbekios on 10/18/21.
//

#include "ProblemaCassette.hpp"

/**
  Constructor: Se construye un listado de canciones con
  tiempos generados al azar. El número de canciones viene
  determinado por el parámetro universoCanciones.

  @param universoCanciones Cantidad de caciones generadas para resolver el
  problema.
*/
ProblemaCassette::ProblemaCassette(int const universoCanciones){

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

/**
 * Resuelve el problema de asignación de canciones utilizando una pila (stack).
 *
 * @return (Nodo) retorna mejor solución encontrada como una estructura de tipo nodo.
 */
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

/**
 * Retorna el listado de canciones totales (universo de canciones).
 *
 * @return (vector) retorna un vector de tipo nodo con todas las canciones que tengo.
 */
vector<int> ProblemaCassette::getMisCanciones(void){
    return misCanciones;
}

/**
 * Inicializa el mejor candidato y llama un método para llenar la pila.
 *
 * @param canciones (vector) listado de todas las canciones, el vector contiene el número de
 * minutos por canción y el indice identifica el número de la canción.
 */
void ProblemaCassette::configurar(vector<int> canciones){
    //Inicializo mejorCandidado con el peor caso
    mejorCandidato.idCancion = -1;
    mejorCandidato.tiempoTotal = -1;

    //Lleno la pila con las canciones generadas por el Constructor
    llenarPila(canciones);
}

/**
 * Convierto las canciones a nodos y lleno la pila con todas las canciones que tengo.
 *
 * @param canciones (vector) listado de todas las canciones, el vector contiene el número de
 * minutos por canción y el indice identifica el número de la canción.
 */
void ProblemaCassette::llenarPila(vector<int> canciones){
    // Creo nodos estados y los agrego a la pila
    for(int i=canciones.size()-1; i >= 0; i--){
        Nodo n;
        n.idCancion = i;
        n.tiempoTotal = canciones[i];
        pila.push(n);
    }
}

/**
 * Genera futuros sucesores del nodo actual, es decir, por cada Nodo n pasado por parámetro genera
 * una lista de sucesores que incluyen la canción n más otra canción para probar diferentes
 * combinaciones.
 *
 * @param n (Nodo) nodo padre con un grupo de canciones seleccionadas
 * @return (queue) retorna una cola con nuevos nodos que incluyen la canción n, más una nueva canción.
 */
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
