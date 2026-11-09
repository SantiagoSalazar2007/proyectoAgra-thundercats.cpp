// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<vector<pair<int, int>>> ady;
vector<bool> esSalida;

void iniciarSimulacion(){

    int i, tCasos, caso, nInter, mCaminos, kSalidas, vMax, aOrigen, bDestino, dCientosMetros, iniLion, iniMutantes;
    for(caso = 1; caso <= tCasos; caso++){
        scanf("%d %d %d %d", &nInter, &mCaminos, &kSalidas, &vMax);
        ady.assign(nInter, vector<pair<int, int>>());
        esSalida.assign(nInter, false);

        for(i = 0; i < mCaminos; i++){
            scanf("%d %d %d", &aOrigen, &bDestino, &dCientosMetros);
            ady[aOrigen].push_back(make_pair(bDestino, dCientosMetros));
        }
        scanf("%d %d", &iniLion, &iniMutantes);

        for(i = 0; i < kSalidas; i++){
            scanf("%d", &nInter);
            esSalida[nInter] = true;
        }
    }
}

int main(){
    iniciarSimulacion();
    return 0;
}