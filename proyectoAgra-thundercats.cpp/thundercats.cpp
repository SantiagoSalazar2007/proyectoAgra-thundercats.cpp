// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> ady;
vector<bool> esSalida;

int nInter;
unsigned int INF = 1e18;

bool dijkstraProbarVelocidad(double velLion, int s, int velMutantes, vector<long long>& distM, vector<bool>& esSalida){
    pair<int, int> actual, adyacencia;
    int i, u, v;
    long long du, duv, distAcumuladaNodo;
    int flag = false;
    vector<long long> dist(nInter + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pqueue;
    dist[s] = 0;
    cola.push(make_pair(0, s));
    while(!cola.empty() && !flag) {
        actual = pqueue.top(); pqueue.pop;
        du = actual.first;
        u = actual.second;
        if(dist[u] == du){
            if(esSalida[u]){
                flag == true;
            } else {
                for(i = 0; i < ady[u].size(); i++){
                    adyacencia = ady[u][i];
                    duv = adyacencia.second;
                    v = adyacencia.first;
                    distAcumuladaNodo = du + duv;
                    if(velMutantes * distAcumuladaNodo <= velLion * distM[duv]){ // si lion puede llegar al nodo mas rapido o igual que los mutantes
                        dist[duv] = distAcumuladaNodo;
                        pqueue.push(make_pair(distAcumuladaNodo, v));
                }
            }
        }
    }
    return flag
}

vector<long long> dijkstraMutantes(int s){
    pair<int, int> actual, adyacencia;
    int i, u, v;
    long long du, duv;
    vector<long long> dist(nInter, INF);
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
                duv = adyacencia.second;              
                v = adyacencia.first;                 

                if(du + duv < dist[v]){
                    dist[v] = du + duv;
                    pqueue.push(make_pair(dist[v], v));
                }
            }
        }
    }
    return dist;
}

void iniciarSimulacion(){

    int i, tCasos, caso, mCaminos, kSalidas, vMax, aOrigen, bDestino, dCientosMetros, iniLion, iniMutantes;
    vector<int> distM;
    for(caso = 1; caso <= tCasos; caso++){
        scanf("%d %d %d %d", &nInter, &mCaminos, &kSalidas, &vMax);
        ady.assign(nInter + 1, vector<pair<int, int>>());
        esSalida.assign(nInter + 1, false);

        for(i = 0; i < mCaminos; i++){
            scanf("%d %d %d", &aOrigen, &bDestino, &dCientosMetros);
            dCientosMetros = (dCientosMetros * 100) / 1000;
            ady[aOrigen].push_back(make_pair(bDestino, dCientosMetros));
            ady[bDestino].push_back(make_pair(aOrigen, dCientosMetros));  
        }
        scanf("%d %d", &iniLion, &iniMutantes);

        for(i = 0; i < kSalidas; i++){
            scanf("%d", &nInter);
            esSalida[nInter] = true; 
        }   
        if(iniLion != iniMutantes){
            distM = dijkstraMutantes(iniMutantes);
        } else {
            printf("Mumm-Ra captures Lion-O!\n");
        }
            
    }
}

int main(){
    iniciarSimulacion();
    return 0;
}