
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;


/* Declaro estructuras auxiliares */
struct nodo{
	int valor;
	vector<int> adyacentes;
};

/* Declaro las funciones auxiliares */
void read(int &n, int &m, vector< pair< pair<int, int>, int > > &G);
bool cmpEquipos(pair< pair<int, int>, int > A, pair< pair<int, int>, int > B);
void BuscarEjeParaCicloYAgregar(vector< pair< pair<int, int>, int > > &G,
                                vector< pair< pair<int, int>, int > > &T);
vector<nodo> BuscarCiclo(vector< pair< pair<int, int>, int > > &T, int n);
vector<nodo> BuscarResto(vector< pair< pair<int, int>, int > > &T, vector<nodo> &C);
void DevolverResultado(vector< pair< pair<int, int>, int > > &T,
                       vector< pair< pair<int, int>, int > > &C,
                       vector< pair< pair<int, int>, int > > &R);
vector< pair< pair<int, int>, int > > MST(vector< pair< pair<int, int>, int > > &G);
bool Chequear_Conexo(vector< pair< pair<int, int>, int > > &G, int n);
vector<nodo> generar_grafo_nodos(vector< pair< pair<int, int>, int > > &G, int n);  
void dfs(nodo base, vector<int> &visitados, vector<nodo> &G2);                
nodo dfsCiclo(nodo base, vector<int> &visitados, vector<nodo> &G2, vector<int> &padres)     ;                              

/*========== Resolvedor del problema ==========*/
int main() {
  
  freopen("input.in", "r", stdin);
  int n, m;
  vector< pair< pair<int, int>, int > > G, T;
  /* 
   * n = cant equipos; m = cant enlaces; G = grafo de conexiones entre equipos 
   * T = MST del grafo G
   */
    
  /* Leo el grafo: cada equipo es un nodo */
  
  read(n, m, G);
  
  /* Chequear que el grafo G sea conexo */
  
  if(!Chequear_Conexo(G, n)) {cout << "no" << endl; return 0;};
  
  /* Armo el MST a partir del grafo G */
  
  T = MST(G);
  
  /* Ordeno los ejes de G  y de T de menor a mayor costo, para luego localizar 
   * el menor eje de G que no esta en T y agregarlo a T para formar un ciclo */
   
  //~ sort(G.begin(), G.end(), cmpEquipos);
  //~ sort(T.begin(), T.end(), cmpEquipos);
  
  vector< pair< pair<int, int>, int > > T2 = T;
  BuscarEjeParaCicloYAgregar(G,T2);		// G y T tienen que estar indexado entre 1..n; tam(T2) = n+2
										
  /* Recorrer arbol con un ciclo buscando el ciclo  y devolver dicho ciclo */
  
  vector<nodo> C = BuscarCiclo(T2,n);
  vector<nodo> R = BuscarResto(T2,C);
  
  /* Testing de funcion BuscarCiclo */
  //~ vector<nodo> C = BuscarCiclo(G,n);
  //~ cout << "El ciclo esta conformado por los nodos: ";
  //~ for(int i=0; i<(int)C.size(); i++) {cout << C[i].valor << " ";}cout << endl;
  
  /* Devolver resultado */
  
  //DevolverResultado(T,C,R);
  
  return 0;
}



/*========================Funciones Auxiliares========================*/

void read(int &n, int &m, vector< pair< pair<int, int>, int > > &G) {
  
  cin >> n >> m;
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
  
  //~ for(int i=0; i<(int)G.size(); i++) {cout << G[i].first.first << " " << G[i].first.second << " " << G[i].second; cout << endl;}cout << endl;
  
  vector< pair< pair<int, int>, int > > T = G;
  //~ T.erase(T.begin()+3);
  //~ T.erase(T.begin()+7);
  //~ T.erase(T.begin()+3);
  //~ for(int i=0; i<(int)T.size(); i++) {cout << T[i].first.first << " " << T[i].first.second << " " << T[i].second; cout << endl;}
   
  return T;
}

vector<nodo> generar_grafo_nodos(vector< pair< pair<int, int>, int > > &G, int n) {
  vector<nodo> G2;
  for(int i=0; i<=n; i++) {
    nodo v;
    v.valor = i;
    G2.push_back(v);
  }
  for(int i=0; i<(int)G.size(); i++) {
    G2[G[i].first.first].adyacentes.push_back(G[i].first.second);
    G2[G[i].first.second].adyacentes.push_back(G[i].first.first);
  }
  return G2;
}

void dfs(nodo base, vector<int> &visitados, vector<nodo> &G2) {
  for(int i=0; i<(int)base.adyacentes.size(); i++) {
      if(visitados[base.adyacentes[i]] == 0) {
	      visitados[base.adyacentes[i]]++;
	      dfs(G2[base.adyacentes[i]],visitados, G2);
	  }
  }
} 

bool Chequear_Conexo(vector< pair< pair<int, int>, int > > &G, int n) {
  vector<int> visitados(n+1,0);
  vector<nodo> G2 = generar_grafo_nodos(G,n);
  
  nodo base = G2[1];
  dfs(base,visitados,G2);
  
  /* Chequeo si quedo algún nodo sin visitar */
  for(int i=1; i<=n; i++) {
    if(visitados[i]==0) {return false; }
  }
  
  return true;	
}

bool sonIguales(pair<int, int> A, pair<int, int> B) {
  bool res1 = (A.first == B.first && A.second == B.second);
  bool res2 = (A.first == B.second && A.second == B.first);
  return (res1 || res2);
}

void BuscarEjeParaCicloYAgregar(vector< pair< pair<int, int>, int > > &G,
                                vector< pair< pair<int, int>, int > > &T) {
    bool flag = false;
    int i = 1, j = 1;
    while(flag == false) {
		bool iguales = sonIguales(G[i].first, T[j].first);
	    if(!iguales) {							// encuentro primer eje en G y no en T
			/*insertar al final del vector T y salir. queda vector de tam = n+2 */
			T.push_back(G[i]);
			flag = true;
		}
	    else {
		    i++; j++;
		} 
	}
}

nodo dfsCiclo(nodo base, vector<int> &visitados, vector<nodo> &G2, vector<int> &padres) {
  visitados[base.valor]++;
  if(visitados[base.valor] == 2) { return base; }
  for(int i=0; i<(int)base.adyacentes.size(); i++) {
	  
	  if(padres[base.valor] == base.adyacentes[i]) {continue;}
	  
	  nodo temp;
      padres[base.adyacentes[i]] = base.valor;
      //~ cout << base.valor << " es el padre de " << base.adyacentes[i] << endl;
      if(visitados[base.adyacentes[i]] < 2) {
	      temp = dfsCiclo(G2[base.adyacentes[i]],visitados, G2,padres);
	      if(visitados[temp.valor]==2) {return temp;}
	  }
  }
  nodo aux; aux.valor = -15;
  return aux;
} 

vector<nodo> BuscarCiclo(vector< pair< pair<int, int>, int > > &T, int n) {
  
  vector<int> visitados(n+2,0);		// tam(T) = n+2: un arbol con un ciclo
  vector<int> padres(n+2,0);
  vector<nodo> res;
  vector<nodo> T2 = generar_grafo_nodos(T,n);
  
  nodo nodox = dfsCiclo(T2[1],visitados,T2,padres);
  
  //~ cout << "procesé bien al ciclo. Devuelvo el nodo: " << nodox.valor << endl;
  for(int i=1; i<(int)padres.size(); i++) {cout << visitados[i] << " ";}cout << endl;
  for(int i=1; i<(int)padres.size(); i++) {cout << padres[i] << " ";}cout << endl;
  res.push_back(nodox);
  int padre = padres[nodox.valor];
  while(padre != nodox.valor) {
      res.push_back(T2[padre]);
      padre = padres[T2[padre].valor];
  }
  return res;
}

vector<nodo> BuscarResto(vector< pair< pair<int, int>, int > > &T,
                         vector<nodo> &C) {
  
  vector<nodo> R;
  return R;
}

void DevolverResultado(vector< pair< pair<int, int>, int > > &T,
                       vector< pair< pair<int, int>, int > > &C,
                       vector< pair< pair<int, int>, int > > &R) {
  
  
}
