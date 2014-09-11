
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
using namespace std;

struct vuelo {
        string origen; string destino;
        int inicio; int fin;
};

int main() {
	
	freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    
    int n, inicio, fin;
    int horarioLlegada, ultimo;
    string A, B, origen, destino;
    vector<vuelo> vuelos(n);
    vector<int> res, puedoLlegar;
    vector< vector<int> > combinaciones;   
    
    while(cin >> A >> B >> n) {
		
		/* Inicializo las variables correctamente */
		ultimo = 0;
		vuelos.resize(n); 
		res.resize(0);
		puedoLlegar.resize(n); fill(puedoLlegar.begin(), puedoLlegar.end(), 0);
		combinaciones.resize(n); 
		for(int i=0; i<n; i++) {
			combinaciones[i].resize(n); 
			fill(combinaciones[i].begin(), combinaciones[i].end(), 0);
		}
		
		/* Leo los vuelos que tengo y inicializo "combinaciones" y "puedoLlegar" */
		for(int i=0; i<n; i++) {
			cin >> origen >> destino >> inicio >> fin;
			vuelos[i].origen = origen; vuelos[i].destino = destino;
            vuelos[i].inicio = inicio; vuelos[i].fin = fin;
            combinaciones[i][i] = 1;
            if(origen == A) {puedoLlegar[i] = 1; }
		}
		
		/* Relleno "combinaciones" y "puedoLlegar" dinámicamente para todos los pares de vuelos */
		for(int i=0; i<n; i++) {
			for(int j=i; j<n; j++) {
				if(vuelos[i].destino == vuelos[j].origen && 
                   vuelos[i].fin + 2 <= vuelos[j].inicio) {				// camino directo i->j
					   combinaciones[i][j] = 1;
					   if(puedoLlegar[i]) {puedoLlegar[j] = 1;}
				}
				if(vuelos[j].destino == vuelos[i].origen && 
                   vuelos[j].fin + 2 <= vuelos[i].inicio) {				// camino directo j->i
					   combinaciones[j][i] = 1;
					   if(puedoLlegar[j]) {puedoLlegar[i] = 1;}
				}
			}
		}
		
		/* Relleno "combinaciones" y "puedoLlegar" dinámicamente de forma completa */
		
		for(int i=0; i<n;i++) {
			for(int j=0; j<n; j++) {
				if(combinaciones[j][i] == 1) {
					for(int k=0; k<n; k++) {
						combinaciones[k][i] = max(combinaciones[k][i], combinaciones[k][j]);
					}
					if(puedoLlegar[j] == 1) {puedoLlegar[i] = 1;}
				}
				// si combinaciones[j][i] == 1 ---> actualizar combinaciones[1..n][i] sumando las de j 
				// 									si puedoLlegar[j] == 1 ----> puedoLlegar[i] = 1;
				// (estoy en el caso en que existe camino de j -> i)
			}
		}
		
		/* Devolver resultado */
		horarioLlegada = 1000;
		for(int i=0; i<n; i++) {
			if((puedoLlegar[i]==1) && (vuelos[i].destino==B)){horarioLlegada = min(horarioLlegada, vuelos[i].fin);}}
		if(horarioLlegada==1000){cerr<<"no"<<endl;}else{cerr << horarioLlegada << endl;}
				
	}
	
	return 0;   
}
