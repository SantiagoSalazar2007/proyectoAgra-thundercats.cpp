// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstdio>

using namespace std;

vector<vector<pair<int, int>>> ady; // Lista de adyacencia de cada interseccion
vector<bool> esSalida; // Flags para cada interseccion indicando si es salida

int nInter; // Numero de intersecciones de cada caso
const long long INF = 1e18; // Simulacion de infinito en c++
const double EPS = 1e-7; // Tolerancia para parar cada busqueda binaria cuando el tamanio del intervalo sea menor


vector<long long> dijkstraMutantes(int s){  // dijkstra estandar para conocer la distancia desde la posición inicial de los mutantes hasta cada interseccion
    pair<long long, int> actual;
    pair<int, int> adyacencia;
    int i, u, v;
    long long du, duv;
    vector<long long> dist(nInter + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pqueue;
    dist[s] = 0;
    pqueue.push(make_pair(0, s));

    while(!pqueue.empty()){
        actual = pqueue.top(); pqueue.pop();
        du = actual.first;
        u = actual.second;

        if(dist[u] == du){
            for(i = 0; i < ady[u].size(); i++){
                adyacencia = ady[u][i];
                v = adyacencia.first;
                duv = adyacencia.second;

                if(du + duv < dist[v]){
                    dist[v] = du + duv;
                    pqueue.push(make_pair(dist[v], v));
                }
            }
        }
    }
    return dist;
}

bool dijkstraProbarVelocidad(double velLion, int s, int velMutantes, vector<long long>& distM){ // dijkstra modificado que retorna flag la cual prueba si es posible escapar con la velocidad dada
    pair<long long, int> actual;
    pair<int, int> adyacencia;
    int i, u, v;
    long long du, duv, distAcumuladaNodo;
    bool flag = false;
    vector<long long> dist(nInter + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pqueue;
    dist[s] = 0;
    pqueue.push(make_pair(0, s));

    while(!pqueue.empty() && !flag){
        actual = pqueue.top(); pqueue.pop();
        du = actual.first;
        u = actual.second;

        if(dist[u] == du){
            if(esSalida[u]){
                flag = true; // si encuentra una salida, la velocidad si permite a Lion-O escapar de los mutantes
            } else {
                for(i = 0; i < ady[u].size(); i++){
                    adyacencia = ady[u][i];
                    v = adyacencia.first;
                    duv = adyacencia.second;
                    distAcumuladaNodo = du + duv;
                    // primero verificamos que no estemos en un camino mas largo a la interseccion adyacente 
                    // luego, (T = x * v) calculamos que lion llegue a la interseccion antes que los mutantes
                    if(distAcumuladaNodo < dist[v] && velMutantes * distAcumuladaNodo <= velLion * distM[v]){
                        pqueue.push(make_pair(distAcumuladaNodo, v));
                    }
                }
            }
        }
    }
    return flag; // retornamos si se pudo llegar a una salida a tiempo
}

double busquedaBinaria(int iniLion, int vMax, long long cotaSuperior, vector<long long>& distM){ // busqueda binaria con tolerancia en el tamanio del intervalo que busca velocidades 
    // usando el dijkstraProbarVelocidad (dPV : velocidad -> tiempo)
    double lo, hi, mid;
    lo = 0; // cota inferior del intervalo inicial (v = 0, osea estar parado)
    hi = vMax * cotaSuperior; // cota superior (tiempo que tardan exactamente en llegar a cada nodo los mutantes) 
    mid = (lo + hi) / 2;
    while(hi - lo > EPS){
        if(dijkstraProbarVelocidad(mid, iniLion, vMax, distM)){
            hi = mid; // monotona decreciente y buscamos minima velocidad
        } else {
            lo = mid;
        }
        mid = (lo + hi) / 2;
    }
    return hi;
}

void iniciarSimulacion(){
    int i, tCasos, caso, mCaminos, kSalidas, vMax, aOrigen, bDestino, dCientosMetros, iniLion, iniMutantes, salida;
    vector<long long> distM;
    long long cotaSuperior;
    double velMinima;

    scanf("%d", &tCasos);
    for(caso = 1; caso <= tCasos; caso++){
        scanf("%d %d %d %d", &nInter, &mCaminos, &kSalidas, &vMax);
        ady.assign(nInter + 1, vector<pair<int, int>>());
        esSalida.assign(nInter + 1, false);
        cotaSuperior = 0;

        for(i = 0; i < mCaminos; i++){
            scanf("%d %d %d", &aOrigen, &bDestino, &dCientosMetros);
            ady[aOrigen].push_back(make_pair(bDestino, dCientosMetros));
            ady[bDestino].push_back(make_pair(aOrigen, dCientosMetros));
            cotaSuperior += dCientosMetros;
        }
        scanf("%d %d", &iniLion, &iniMutantes);

        for(i = 0; i < kSalidas; i++){
            scanf("%d", &salida);
            esSalida[salida] = true;
        }

        distM = dijkstraMutantes(iniMutantes);

        if(!dijkstraProbarVelocidad(1e18, iniLion, vMax, distM)){ // se prueba tambien que la ruta sea posible usando la maxima velocidad posible
            printf("Mumm-Ra captures Lion-O!\n");
        } else {
            velMinima = busquedaBinaria(iniLion, vMax, cotaSuperior, distM);
            printf("Lion-O can escape at a speed of %.7f km/h!\n", velMinima);
        }
    }
}

int main(){
    iniciarSimulacion();
    return 0;
}