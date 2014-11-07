
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "primm.cpp"
#define MAX_INT 10000001
using namespace std;


/* Declaro estructuras auxiliares */
struct nodo{
	int valor;
	vector<pair<int,int> > adyacentes;		// adyacentes.second tiene la longitud del eje que une nodo.valor con adyacentes.first
};

/* Declaro las funciones auxiliares */
void read(int &n, int &m, vector< pair< pair<int, int>, int > > &G);
bool cmpEquipos(pair< pair<int, int>, int > A, pair< pair<int, int>, int > B);
void BuscarEjeParaCicloYAgregar(vector< pair< pair<int, int>, int > > &G,
                                vector< pair< pair<int, int>, int > > &T);
vector<nodo> BuscarCiclo(vector< pair< pair<int, int>, int > > &T, int n);
void DevolverResultado(pair< vector< pair< pair<int, int>, int > >, vector< pair< pair<int, int>, int > > > &ANS, int &costo);
bool Chequear_Conexo(vector< pair< pair<int, int>, int > > &G, int n);
vector<nodo> generar_grafo_nodos(vector< pair< pair<int, int>, int > > &G, int n);
void dfs(nodo base, vector<int> &visitados, vector<nodo> &G2);
nodo dfsCiclo(nodo base, vector<int> &visitados, vector<nodo> &G2, vector<int> &padres);
pair< vector< pair< pair<int, int>, int > >, vector< pair< pair<int, int>, int > > > BuscarCicloYResto(vector< pair< pair<int, int>, int > > &T, int n, int &costo);
vector< vector<int> > matrizDeAdyacencia(vector< pair< pair<int, int>, int > > &G, int n);
bool noEstaEnCiclo(pair< pair<int, int>, int > x, vector< pair< pair<int, int>, int > > C);


void BFS(vector< pair<pair<int,int>,int > >& T, pair<pair<int,int>,int >& arista, int n);
/*========== Resolvedor del problema ==========*/
int main() {

  //freopen("input.in", "r", stdin);
  int n, m;
  vector< pair< pair<int, int>, int > > G, T;
  /*
   * n = cant equipos; m = cant enlaces; G = grafo de conexiones entre equipos
   * T = MST del grafo G
   */

  /* Leo el grafo: cada equipo es un nodo */

  read(n, m, G);

  /* Chequear que el grafo G sea conexo y que al menos haya un ciclo en G */

  if(!Chequear_Conexo(G, n)) {cout << "no" << endl; return 0;};
  if((int)G.size() == n-1) {cout << "no" << endl; return 0;}

  /* Armo el MST a partir del grafo G */

  vector< vector<int> > G2 = matrizDeAdyacencia(G,n);
  T = primm(G2,n);

  /* Ordeno los ejes de G  y de T de menor a mayor costo, para luego localizar
   * el menor eje de G que no esta en T y agregarlo a T para formar un ciclo */

  sort(G.begin(), G.end(), cmpEquipos);
 // sort(T.begin(), T.end(), cmpEquipos);
 pair< pair<int, int>, int > arista;
   for (int i=0; i<n; i++){
        if ((find(T.begin(), T.end(),G[i])) == T.end() ) {arista=(G[i]);} //MIRO LAS N ARISTAS MÁS CHICAS DE G Y LA MAS CHICA QUE NO ESTA EN T LA AGREGO. O(N^2)

    }
BFS(T, arista, n);
 // vector< pair< pair<int, int>, int > > T2 = T;
 // BuscarEjeParaCicloYAgregar(G,T2);		// G y T tienen que estar indexado entre 1..n; tam(T2) = n+2




//  int costo = 0;
 // pair< vector< pair< pair<int, int>, int > >, vector< pair< pair<int, int>, int > > > ANS = BuscarCicloYResto(T2,n,costo);

  /* Devolver resultado */

 // DevolverResultado(ANS,costo);

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
  if (A.second == B.second) { return A.first.first < B.first.first;}
  if (A.second == B.second && A.first == B.first) { return A.first.second < B.first.second;}
  return (A.second < B.second);
}

vector< vector<int> > matrizDeAdyacencia(vector< pair< pair<int, int>, int > > &G, int n) {
  vector <vector <int> > res(n+1, std::vector<int>(n+1,-1));
  for(int i=0; i<(int)G.size(); i++) {
      res[G[i].first.first][G[i].first.second] = G[i].second;
      res[G[i].first.second][G[i].first.first] = G[i].second;
  }
  int INF = MAX_INT;
  for(int i=1; i<=n; i++) {
	  for(int j=1; j<=n; j++) {
		  if(res[i][j] == -1) {res[i][j] = INF;}
	  }
  }
  return res;
}

vector<nodo> generar_grafo_nodos(vector< pair< pair<int, int>, int > > &G, int n) {
  vector<nodo> G2;
  for(int i=0; i<=n; i++) {
    nodo v;
    v.valor = i;
    G2.push_back(v);
  }
  for(int i=0; i<(int)G.size(); i++) {
    G2[G[i].first.first].adyacentes.push_back(make_pair(G[i].first.second,G[i].second));
    G2[G[i].first.second].adyacentes.push_back(make_pair(G[i].first.first,G[i].second));
  }
  return G2;
}

void dfs(nodo base, vector<int> &visitados, vector<nodo> &G2) {
  for(int i=0; i<(int)base.adyacentes.size(); i++) {
      if(visitados[base.adyacentes[i].first] == 0) {
	      visitados[base.adyacentes[i].first]++;
	      dfs(G2[base.adyacentes[i].first],visitados, G2);
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
                                vector< pair< pair<int, int>, int > > &T) {	// asumo G y T ordenados
	assert(G.size() > T.size());										// asumo que G no es un árbol
    bool flag = false;
    int i = 1, j = 1;
    while(flag == false) {
		bool iguales = sonIguales(G[i].first, T[j].first);

	    bool condicion1 = (!iguales && i<(int)G.size() && j<(int)T.size());
	    bool condicion2 = (j >= (int)T.size());

	    if(condicion1 || condicion2) {					// encuentro primer eje en G y no en T
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

	  if(padres[base.valor] == base.adyacentes[i].first) {continue;}

	  nodo temp;
      padres[base.adyacentes[i].first] = base.valor;
      if(visitados[base.adyacentes[i].first] < 2) {
	      temp = dfsCiclo(G2[base.adyacentes[i].first],visitados, G2,padres);
	      if(visitados[temp.valor]==2) {return temp;}
	  }
  }
  nodo aux; aux.valor = -15;	// nunca debería devolver esto
  cout << " mal" << endl;
  return aux;
}

pair< vector< pair< pair<int, int>, int > >, vector< pair< pair<int, int>, int > > > BuscarCicloYResto(vector< pair< pair<int, int>, int > > &T, int n, int &costo) {

  vector<int> visitados(n+2,0);		// tam(T) = n+2: un arbol con un ciclo
  vector<int> padres(n+2,0);
  vector<nodo> resTemp;				// guardo los nodos pertenecientes al ciclo
  vector<nodo> T2 = generar_grafo_nodos(T,n);

  nodo nodox = dfsCiclo(T2[1],visitados,T2,padres);

  resTemp.push_back(nodox);

  int padre = padres[nodox.valor];
  while(padre != nodox.valor) {
      resTemp.push_back(T2[padre]);
      padre = padres[T2[padre].valor];
  }
  resTemp.push_back(T2[padre]);

  vector< pair< pair<int, int>, int > > ciclo, resto;
  vector<int> estan(n+1,0);						// registro qué elementos de T estan en el ciclo
  for(int i=0; i<(int)resTemp.size(); i++) {

	  int e1 = resTemp[i].valor;
	  int e2 = resTemp[i+1].valor;
      for(int j=1; j<(int)T.size(); j++) {
	      if(T[j].first.first == e1 && T[j].first.second == e2 && padres[resTemp[i].valor] != nodox.valor) {estan[j] = 1;}
	      if(T[j].first.first == e2 && T[j].first.second == e1 && padres[resTemp[i].valor] != nodox.valor) {estan[j] = 1;}

	      if(padres[resTemp[i].valor] == nodox.valor &&
	         ((T[j].first.first == nodox.valor && T[j].first.second == resTemp[i].valor) ||
	          (T[j].first.first == resTemp[i].valor && T[j].first.second == nodox.valor))){
			  estan[j] = 1;
		  }
	  }
  }

  for(int i=0; i<(int)T.size(); i++) {
	  if(estan[i] == 1) {
		  ciclo.push_back(T[i]);
		  costo += T[i].second;
	  }else {
	      resto.push_back(T[i]);
	      costo += T[i].second;
	  }
  }

  return make_pair(ciclo,resto);
}

void DevolverResultado(pair< vector< pair< pair<int, int>, int > >, vector< pair< pair<int, int>, int > > > &ANS, int &costo) {

  cout << costo << " " << ANS.first.size() << " " << ANS.second.size() << endl;
  for(int i=0; i<(int)ANS.first.size(); i++) {
	  cout << ANS.first[i].first.first << " " << ANS.first[i].first.second << " " << ANS.first[i].second << endl;
  }
  for(int i=0; i<(int)ANS.second.size(); i++) {
	  cout << ANS.second[i].first.first << " " << ANS.second[i].first.second << " " << ANS.second[i].second << endl;
  }
}


void BFS(vector< pair<pair<int,int>,int > >& T, pair<pair<int,int>,int >& arista, int n) //hace bfs
{
    int pesoTotal=arista.second;
    for (int i=0; i<T.size();i++){
        pesoTotal+=T[i].second;
    }
	// defino fuente y destino del camino
	int src=(arista.first).first;
	int dst=(arista.first).second;

	//creo el grafo

	vector< vector<int> > adj = matrizDeAdyacencia(T, n);

	vector<bool> visitados (n+1,false);
	vector <pair<int, int> > prev(n+1);

    queue<int> queue; //creo cola bfs

    //visito nodo origen, lo hago root y lo pusheo
    visitados[src]=true;
    prev[src]=make_pair(-1,-1);
    queue.push(src);


	int nod;

    while(!queue.empty()){
       ///pop
        nod = queue.front();
        queue.pop();

        /// visito adyacentes
        for (int j=1; j<adj.size();j++){ //MENOR O IGUAL
			if( adj[nod][j]!=MAX_INT && (!visitados[j]) ){
				visitados[j]=true;
				//cout<<"Visito : "<<j<<" desde: "<<nod<<endl;
				prev[j]=make_pair(nod, adj[nod][j]); // en prev[j] está nod y el peso de la arista j-nod
				queue.push(j);
				}
			}
	}

	vector< pair<pair<int,int>,int > > ciclo;

	bool llegue=false;

	while(!llegue){
			ciclo.push_back(make_pair( make_pair(dst, prev[dst].first), prev[dst].second ) );
			if (prev[dst].first == src){
				llegue=true;
				}
			else{

				dst=prev[dst].first;
				}
		}

	//en prev está guardado el camino desde dst hasta src. si a ese camino le agrego arista ahí está el ciclo.
    ciclo.push_back(arista);

cout<<pesoTotal<<" "<<ciclo.size()<<" "<<T.size()-ciclo.size()+1<<endl;

	for (int i=0;i<ciclo.size();i++){cout<<(ciclo[i].first).first<<"-"<<(ciclo[i].first).second<<endl;}






	for (int j=0; j<T.size(); j++){
    bool encontre=false;
         for(int w=0; w<ciclo.size(); w++) {
             if(sonIguales((T[j].first), (ciclo[w].first))){encontre=true; break;}

        }

    if(!encontre){cout<<(T[j].first).first<<"-"<<(T[j].first).second<<endl;encontre=false;}
	}

}

