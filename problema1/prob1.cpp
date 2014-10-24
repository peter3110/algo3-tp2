
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "dijkstra.cpp"
using namespace std;

#define INT_MAX 10000001

/* Funciones auxiliares */
void escribirMatriz(vector<vector<int> > &M) {
  for(int i=0; i<(int)M.size(); i++) {
    for(int j=0; j<(int)M[0].size(); j++) {
        cout << M[i][j] << " ";  
    }  
    cout << endl;
  }  
}

struct vuelo{
    string origen, destino;
    int inicio, fin;
};

bool hayCombinacionDirecta(vuelo x, vuelo y) {
  /* Chequea si desde el vuelo x puedo combinar de forma directa con el vuelo y */
  bool condicion1 = (x.destino == y.origen);
  bool condicion2 = (x.fin + 2 <= y.inicio);

  return (condicion1 && condicion2);
}

int main() {
  
  freopen("input.in", "r", stdin);
  string A, B;
  int n;
  cin >> A >> B >> n; // n = cant. vuelos
  
  vector<vuelo> vuelos;
  string ori, des;
  int ini, fi;
  
  /* Leo la entrada */
  for(int i=0; i<n; i++) {
      cin >> ori >> des >> ini >> fi;
      vuelo temp;
      temp.origen = ori; temp.destino = des;
      temp.inicio = ini; temp.fin = fi;
      vuelos.push_back(temp);
  }
  
  /* Armo la matriz de adyacencia: cada vuelo es un nodo y se conecta 
   * con otro si puede haber conexion entre ellos */
  vector <vector <int> > M(n, std::vector<int>(n+1, 0));      // dejo espacio para el nodo ficticio 
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
        if(hayCombinacionDirecta(vuelos[i],vuelos[j])) {
            M[i][j] = vuelos[i].fin;                         // desde el vuelo i, puedo combinar al vuelo j y guardo hora llegada
        }  
        if(hayCombinacionDirecta(vuelos[j],vuelos[i])) {
            M[j][i] = vuelos[j].fin;                         // desde el vuelo j, puedo combinar al vuelo i y guardo hora llegada
        }
    }  
  }
  
  /* Agrego nodo ficticio que va a ser el origen. ¿desde qué nodos (vuelos) puedo empezar? */
  vector<int> nodoFicticio(n+1,INT_MAX);
  for(int i=0; i<n; i++) {
      if(vuelos[i].origen == A) { nodoFicticio[i] = vuelos[i].inicio; }  
      if(i==n) { nodoFicticio[i] = 0; }
  }
  M.push_back(nodoFicticio);
  
  /* Resuelvo camino mínimo entre nodo ficticio y todos los demás */
  vector<int> dist;
  dist = dijkstra(M, n, n+1);   // n+1 nodos y n es el nodo origen
  
  /* testeo */
  //~ escribirMatriz(M);
  
  for(int i=0; i<(int)dist.size(); i++) {cout << dist[i] << " ";}
  cout << endl;
  
  /* Rastreo las combinaciones que hay que hacer */
  int fin = INT_MAX;
  for(int i=0; i<(int)dist.size()-1; i++) {
      if(vuelos[i].origen == B) { fin = min(fin,dist[i]); }
      if(vuelos[i].destino == B && dist[i] + 2 <= vuelos[i].inicio) {
            fin = min(fin, vuelos[i].fin);
      }  
  }
  cout << "Llego a " << B << " a las " << fin << endl;
  /* Devuelvo el resultado ( fin k v1 .. vk ) */
  
  
  return 0;
}
