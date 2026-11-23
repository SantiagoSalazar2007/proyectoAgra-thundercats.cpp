// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstdio>

using namespace std;

vector<vector<pair<int, int>>> ady;
vector<bool> esSalida;

int nInter;
const long long INF = 1e18;
const double EPS = 1e-7; // agregamos epsilon necesario para la bbinaria


vector<long long> dijkstraMutantes(int s){
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

bool dijkstraProbarVelocidad(double velLion, int s, int velMutantes, vector<long long>& distM){
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
                flag = true;
            } else {
                for(i = 0; i < ady[u].size(); i++){
                    adyacencia = ady[u][i];
                    v = adyacencia.first;
                    duv = adyacencia.second;
                    distAcumuladaNodo = du + duv;
                    // Ajustar relajacion de velocidades en cada iteracion del dijkstra para ajustar ultimo digito (POSIBLE CORRECION)
                    if(distAcumuladaNodo < dist[v] && velMutantes * distAcumuladaNodo <= velLion * distM[v]){ // solo entra a v si es un camino mas corto y lion llega antes o igual que los mutantes y tambien se asegura que sea una distancia actualizada o que nos aporte algo en ese nuevo camino
                        dist[v] = distAcumuladaNodo;
                        pqueue.push(make_pair(distAcumuladaNodo, v));
                    }
                }
            }
        }
    }
    return flag;
}

double busquedaBinaria(int iniLion, int vMax, long long cotaSuperior, vector<long long>& distM){
    double lo, hi, mid;
    lo = 0;
    hi = vMax * cotaSuperior;  // cambiar cota superior para que se ajuste el ultimo digito? (POSIBLES CORRECIONES)
    mid = (lo + hi) / 2;
    while(hi - lo > EPS && mid > lo && mid < hi){
        if(dijkstraProbarVelocidad(mid, iniLion, vMax, distM)){
            hi = mid;
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