
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;


/* Declaro las funciones auxiliares */
void read(int &n, int &m, vector< pair< pair<int, int>, int > > &G);
bool cmpEquipos(pair< pair<int, int>, int > A, pair< pair<int, int>, int > B);
void BuscarEjeParaCicloYAgregar(vector< pair< pair<int, int>, int > > &G,
                                vector< pair< pair<int, int>, int > > &T);
vector< pair< pair<int, int>, int > > BuscarCiclo(vector< pair< pair<int, int>, int > > &T);
vector< pair< pair<int, int>, int > > BuscarResto(vector< pair< pair<int, int>, int > > &T,
                                                  vector< pair< pair<int, int>, int > > &C);
void DevolverResultado(vector< pair< pair<int, int>, int > > &T,
                       vector< pair< pair<int, int>, int > > &C,
                       vector< pair< pair<int, int>, int > > &R);
vector< pair< pair<int, int>, int > > MST(vector< pair< pair<int, int>, int > > &G);
                                                               

/*========== Resolvedor del problema ==========*/
int main() {
  
  int n, m;
  vector< pair< pair<int, int>, int > > G, T;
  /* 
   * n = cant equipos; m = cant enlaces; G = grafo de conexiones entre equipos 
   * T = MST del grafo G
   */
    
  /* Leo el grafo: cada equipo es un nodo */
  read(n, m, G);
  
  /* Armo el MST a partir del grafo G . Tenemos que detectar que si no es 
   * posible armar este MST, entonces el problema no tiene solución. */
  T = MST(G);
  // IF T = nil, return "no"
  
  /* Ordeno los ejes de G de menor a mayor costo, para luego localizar el menor eje de G
   * que no esta en T y agregarlo a T para formar un ciclo */
  sort(G.begin(), G.end(), cmpEquipos);
  vector< pair< pair<int, int>, int > > T2 = T;
  BuscarEjeParaCicloYAgregar(G,T2);
  
  /* Recorrer arbol con un ciclo buscando el ciclo  y devolver dicho ciclo */
  vector< pair< pair<int, int>, int > > C = BuscarCiclo(T2);
  vector< pair< pair<int, int>, int > > R = BuscarResto(T2,C);
  
  /* Devolver resultado */
  DevolverResultado(T,C,R);
  
  return 0;
}



/*========================Funciones Auxiliares========================*/

void read(int &n, int &m, vector< pair< pair<int, int>, int > > &G) {
  
  int e1, e2, c;
  for(int i=0; i<m; i++) {
      cin >> e1 >> e2 >> c;		// 1 <= ei <= n; c = costo del enlace
      G.push_back(make_pair(make_pair(e1,e2),c));
  }
}

bool cmpEquipos(pair< pair<int, int>, int > A, pair< pair<int, int>, int > B) {
  return (A.second < B.second);
}

vector< pair< pair<int, int>, int > > MST(vector< pair< pair<int, int>, int > > &G) {
  
  vector< pair< pair<int, int>, int > > T;  
  return T;
}

void BuscarEjeParaCicloYAgregar(vector< pair< pair<int, int>, int > > &G,
                                vector< pair< pair<int, int>, int > > &T) {
  
}

vector< pair< pair<int, int>, int > > BuscarCiclo(vector< pair< pair<int, int>, int > > &T) {
  
  vector< pair< pair<int, int>, int > > C;
  return C;
}

vector< pair< pair<int, int>, int > > BuscarResto(vector< pair< pair<int, int>, int > > &T,
                                                  vector< pair< pair<int, int>, int > > &C) {
  
  vector< pair< pair<int, int>, int > > R;
  return R;
}

void DevolverResultado(vector< pair< pair<int, int>, int > > &T,
                       vector< pair< pair<int, int>, int > > &C,
                       vector< pair< pair<int, int>, int > > &R) {
  
  
}
