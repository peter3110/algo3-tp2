#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <queue>
using namespace std;

struct casilla {


        bool visited; // bool para BFS
        int kVisitado; // contador para chequear cuántos caballos visitaron esa posición
        int saltosNecesarios; // acumulador para saltos necesarios para llegar a esa posición
        int distSrc; //distancia para BFS


};

bool esValida(int x, int y, int n){ //chequea si una posición del tablero es válida
    return ( x >= 0 && x < n && y >= 0 && y < n);
}

void ImprimirSolucion(vector<vector<casilla> >& graph, int k){ //busca en el grafo la posición visistada por los k caballos que tenga menos saltos necesearios acumulados
	pair<int,int> temp;
	int saltosMin=INT_MAX;

	for (int i=0;i<graph.size();++i){
		for (int j=0;j<graph.size();++j){
           //cout<<graph[i][j].kVisitado<<" "<<graph[i][j].saltosNecesarios<<endl;
			if ((graph[i][j].kVisitado==k && graph[i][j].saltosNecesarios<saltosMin)){
				saltosMin=graph[i][j].saltosNecesarios;
				temp.first=i;
				temp.second=j;
				}
			}
		}
	if(saltosMin==INT_MAX){
	    cout<<"no"<<endl;}
    else{
    cout<<temp.first<<" "<<temp.second<<" "<<saltosMin;
    }
}
void visitarNodo(casilla& nod, int distanciaPadre){ //actualiza los campos de un nodo dado al visitarlo por BFS
	            nod.visited = true;
                nod.kVisitado++;
                nod.distSrc= distanciaPadre+1;
                nod.saltosNecesarios+=nod.distSrc;
	}
void visitarAdj(vector<vector<casilla> >& graph, queue<pair<int,int> >& queue, int i, int j, int n){ //visita los adyacentes a la casilla [i,j] en el graph y los pushea en queue

           pair<int,int> temp;

            if( esValida(i+2,j+1,n) && !(graph[i+2][j+1].visited) ){
				visitarNodo(graph[i+2][j+1], graph[i][j].distSrc);
				temp=make_pair(i+2,j+1);
				queue.push(temp);
            }
            if( esValida(i+2,j-1,n) && !(graph[i+2][j-1].visited) ){
				visitarNodo(graph[i+2][j-1], graph[i][j].distSrc);
				temp=make_pair(i+2,j-1);
				queue.push(temp);
            }
            if( esValida(i-2,j+1,n) && !(graph[i-2][j+1].visited) ){
				visitarNodo(graph[i-2][j+1], graph[i][j].distSrc);
				temp=make_pair(i-2,j+1);
				queue.push(temp);
            }
            if( esValida(i-2,j-1,n) && !(graph[i-2][j-1].visited) ){
				visitarNodo(graph[i-2][j-1], graph[i][j].distSrc);
				temp=make_pair(i-2,j-1);
				queue.push(temp);
            }
            if( esValida(i+1,j+2,n) && !(graph[i+1][j+2].visited) ){
				visitarNodo(graph[i+1][j+2], graph[i][j].distSrc);
				temp=make_pair(i+1,j+2);
				queue.push(temp);
            }
            if( esValida(i-1,j+2,n) && !(graph[i-1][j+2].visited) ){
				visitarNodo(graph[i-1][j+2], graph[i][j].distSrc);
				temp=make_pair(i-1,j+2);
				queue.push(temp);
            }
            if( esValida(i+1,j-2,n) && !(graph[i+1][j-2].visited) ){
				visitarNodo(graph[i+1][j-2], graph[i][j].distSrc);
				temp=make_pair(i+1,j-2);
				queue.push(temp);
            }
            if( esValida(i-1,j-2,n) && !(graph[i-1][j-2].visited) ){
				visitarNodo(graph[i-1][j-2], graph[i][j].distSrc);
				temp=make_pair(i-1,j-2);
				queue.push(temp);
            }
        }


void BFS(vector<vector<casilla> >& graph, int i, int j, int n) //hace bfs
{

    queue<pair<int,int> > queue; //creo cola bfs

    //visito nodo origen, incremento su kVisitado y la pusheo
    graph[i][j].visited = true;
    graph[i][j].kVisitado ++;
    queue.push(make_pair(i,j));


	pair<int,int> src;

    while(!queue.empty())
    {
       ///pop
        src = queue.front();
        queue.pop();

        /// visito adyacentes
		visitarAdj(graph, queue, src.first,src.second,n);

    }
}





int main() {


	///leer entrada
	int n,k,f,c;
	cin>>n;
	cin>>k;
	pair<int,int> cab;
	vector<pair<int,int> >kCab(k);
	for(int i=0;i<k;++i){
		cin>>f;
		cin>>c;
        kCab[i]=make_pair(f,c);
		//cout<<cab.first<<" "<<cab.second<<endl;
		//kCab.push_back(cab);
       // cout<<"Pares: "<<kCab[i].first<<" "<<kCab[i].second<<endl;
		}

	///inicializo nodos
	vector<vector<casilla> > graph(n);
	for(int i=0;i<n;i++){
		graph[i].resize(n);
		for (int j=0;j<n;j++){
                graph[i][j].visited=false;
                graph[i][j].kVisitado=0;
                graph[i][j].saltosNecesarios=0;
                graph[i][j].distSrc=0;
		}
    }

	for(int z=0 ; z<k ; ++z){ ///K veces BFS

		BFS(graph, (kCab[z]).first, (kCab[z]).second,n);

		// limpio campos del bfs para la próxima corrida (n^2)
		for(int i = 0; i < n; ++i){
			for(int j=0;j<n;++j){
				(graph[i][j]).visited = false;
				(graph[i][j]).distSrc = 0;
			}
		}

    }

	ImprimirSolucion(graph, k);

    return 0;
}
