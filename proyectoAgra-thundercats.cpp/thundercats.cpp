// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> ady;
vector<bool> esSalida;

int nInter;
int MAX = INT_MAX;

int dijkstraBBinaria(){

}

vector<int> dijkstraEstados(int s){
    pair<int, int> actual, adyacencia;
    int i, du, u, v, duv;
    vector<int> dist(nInter, MAX);
    priority_queue<pair<int, int>> pqueue;       
    dist[s] = 0;
    pqueue.push(make_pair(0, s));

    while(!pqueue.empty()){
        actual = pqueue.top(); pqueue.pop();
        du = actual.first;
        u = actual.second;

        if(dist[u] == du){
            for(i = 0; i < ady[u].size(); i++){
                adyacencia = ady[u][i];
                duv = ady[u][i].second;              
                v = ady[u][i].first;                 

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
            esSalida[nInter] = true; // esto probablemente lo cambie por una mascara de bits
        }   
        if(iniLion != iniMutantes){
            distM = dijkstraEstados(iniMutantes);
        } else {
            printf("Mumm-Ra captures Lion-O!\n");
        }
            
    }
}

int main(){
    iniciarSimulacion();
    return 0;
}