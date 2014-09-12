
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
using namespace std;

#define INF 10000001

struct vuelo {
        string origen; string destino;
        int inicio; int fin;
};

int main() {
	
	freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    
    int n, inicio, fin;
    int horarioLlegada, ultimo, puedoLlegar;
    string A, B, origen, destino;
    vector<vuelo> vuelos(n);
    vector<int> res, combinaciones;
    
    while(cin >> A >> B >> n) {
		
		/* Inicializo las variables correctamente */
		ultimo = 0; puedoLlegar = 0;
		vuelos.resize(n); res.resize(0);
		combinaciones.resize(n); fill(combinaciones.begin(), combinaciones.end(), 0);
		
		/* Leo los vuelos que tengo y inicializo "combinaciones" y "puedoLlegar" */
		for(int i=0; i<n; i++) {
			cin >> origen >> destino >> inicio >> fin;
			vuelos[i].origen = origen; vuelos[i].destino = destino;
            vuelos[i].inicio = inicio; vuelos[i].fin = fin;
            combinaciones[i] |= (1<<i);
            if(origen == A) {puedoLlegar |= (1<<i); }
		}
		
		/* Relleno "combinaciones" y "puedoLlegar" dinámicamente para todos los pares de vuelos */
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {									// PUEDO ARRANCAR DESDE i+1 ???
				if(vuelos[i].destino == vuelos[j].origen && 
                   vuelos[i].fin + 2 <= vuelos[j].inicio) {				// camino directo i->j
					   combinaciones[j] |= (1<<i);
					   if((puedoLlegar & (1<<i)) != 0) {puedoLlegar |= (1<<j); }
				}
				if(vuelos[j].destino == vuelos[i].origen && 
                   vuelos[j].fin + 2 <= vuelos[i].inicio) {				// camino directo j->i
					   combinaciones[i] |= (1<<j); 
					   if((puedoLlegar & (1<<j)) != 0) {puedoLlegar |= (1<<i); }
				}
			}
		}
		
		/* Relleno "combinaciones" y "puedoLlegar" dinámicamente de forma completa */
		for(int i=0; i<n;i++) {
			for(int j=0; j<n; j++) {									// PUEDO ARRANCAR DESDE i+1 ???
				if((combinaciones[i] & (1<<j)) != 0) {							// si existe camino j --> i actualizo desde qué vuelos puedo llegar al vuelo i
					if((puedoLlegar & (1<<j)) != 0) {puedoLlegar |= (1<<i); }	// y también actualizo a qué vuelos puedo llegar desde A.
					combinaciones[i] |= combinaciones[j];
				}
				if((combinaciones[j] & (1<<i)) != 0) {							// si existe camino i --> j actualizo desde qué vuelos puedo llegar al vuelo j
					if((puedoLlegar & (1<<i)) != 0) {puedoLlegar |= (1<<j); }	// y también actualizo a qué vuelos puedo llegar desde A.
					combinaciones[j] |= combinaciones[i];
				}
			}
		}

		/* Devolver resultado */
		horarioLlegada = INF;
		for(int i=0; i<n; i++) {
			if(((puedoLlegar & (1<<i)) != 0) && (vuelos[i].destino==B)){horarioLlegada = min(horarioLlegada, vuelos[i].fin); ultimo = i; }
		}
		if(horarioLlegada==INF){
			cerr<<"no"<<endl;
		}else{
			res.push_back(ultimo);
			while(vuelos[ultimo].origen != A) {
				for(int i=0; i<n; i++) {
						if(vuelos[i].destino == vuelos[ultimo].origen) {ultimo = i; res.push_back(ultimo); break; }
				}
			}
			cerr << horarioLlegada << " " << res.size() << " ";
			for(int i=res.size() - 1; i>= 0; i--) {cerr << res[i] << " ";}
			cerr << endl;
		}
	}
	
	return 0;   
}
