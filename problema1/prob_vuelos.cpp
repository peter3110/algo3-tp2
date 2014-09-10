
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
	
    int n, inicio, fin;
    string A, B, origen, destino;
    cin >> A >> B >> n;
    
    vector<vuelo> vuelos(n);
    vector<int> combinaciones(n);        // combinaciones[i] = el conjunto de los vuelos desde los cuales se puede acceder al vuelo i
    int puedoLlegar;                     // conjunto de vuelos a los que puedo llegar si como origen estoy en A
    
    for(int i=0; i<n; i++) {
        cin >> origen >> destino >> inicio >> fin;
        vuelos[i].origen = origen; vuelos[i].destino = destino;
        vuelos[i].inicio = inicio; vuelos[i].fin = fin;
    }
    
    for(int i=0; i<n; i++) {                                            // al principio, el vector combinaciones tiene todos los vuelos que se pueden conectar de a pares
        for(int j=0; j<n; j++) {                                        // y después, en base a esta inicialización, voy actualizando hasta considerar todos los vuelos
            if(vuelos[i].destino == vuelos[j].origen && 
               vuelos[i].fin + 2 <= vuelos[j].inicio) {     // se puede llegar de i a j
                    combinaciones[j] += (1<<i);
                    if(vuelos[i].origen == A) {puedoLlegar += (1<<i); } // el vuelo i tiene origen en A. Despues voy a actualizar este entero (que representa un cjto.) y
                                                                        // va a terminar diciendome a qué vuelos puedo llegar desde A.
            }
        }
    }
    
    /* Aca se hacen todas las comparaciones necesarias para saber, para cada viaje, si puede ser accedido
     * desde algún otro viaje al cuál se pueda acceder desde uno que tenga como origen a A */
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
                
                if((combinaciones[i] & (1<<j)) != 0) {                  // puedo llegar al vuelo i desde el vuelo j
                    combinaciones[i] += combinaciones[j];               // actualizo desde dónde puedo llegar al vuelo i
                    if((puedoLlegar & (1<<j)) != 0) {
                            puedoLlegar += (1<<i) + combinaciones[i];
                    }                                                   // también puedo llegar al vuelo i  y a los que se puede llegar desde i, desde A
                }
                
                if((combinaciones[j] & (1<<i)) != 0) {                  // puedo llegar al vuelo j desde el vuelo i
                    combinaciones[j] += combinaciones[i];               // actualizo desde dónde puedo llegar al vuelo j
                    if((puedoLlegar & (1<<i)) != 0) {
                            puedoLlegar += (1<<j) + combinaciones[j];   // también puedo llegar al vuelo j y los que se puede llegar desde j, desde A
                    } 
                }
        }
    }
    
    /* Ahora que ya tengo completo el vector "combinaciones" y el entero puedoLlegar, ya sé para cada viaje si se puede acceder 
     * desde el origen A. Entonces, me fijo cuál es el vuelo "i" que llega primero al destino B, de los vuelos a los cuáles se puede
     * acceder desde el origen A. Así, voy yendo para atrás, cada vez a algún vuelo cuyo destino sea el origen del vuelo i,
     * hasta encontrar un vuelo cuyo origen sea A. */
    for(int i=0; i<n; i++) {
        
    }
    
    
    
    return 0;
}
