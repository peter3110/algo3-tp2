#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <queue>          // std::queue
using namespace std;

struct casilla {
		casilla() : visited(false), kVisitado(0), saltosNecesarios(0),distSrc(0){}

        bool visited;
        int kVisitado;
        int saltosNecesarios;
        int distSrc;


};

bool esValida(int x, int y, int n)
{
    return ( x >= 0 && x < n && y >= 0 && y < n);
}

void ImprimirSolucion(vector<vector<casilla> >& graph, int k){
	pair<int,int> temp;
	int saltosMin=INT_MAX;

	for (int i=0;i<graph.size();++i){
		for (int j=0;j<graph.size();++j){

			if ((graph[i][j].kVisitado==k && graph[i][j].saltosNecesarios<saltosMin)){
				saltosMin=graph[i][j].saltosNecesarios;
				temp.first=i;
				temp.second=j;
				}
			}
		}
	cout<<temp.first<<" "<<temp.second<<" "<<saltosMin;
	}
void visitarNodo(casilla& nod){
	            nod.visited = true;
                nod.kVisitado++;
                nod.distSrc= nod.distSrc+1;
                nod.saltosNecesarios+=nod.distSrc;
	}
void visitarAdj(vector<vector<casilla> >& graph, queue<pair<int,int> >& queue, int i, int j, int n){

           pair<int,int> temp;

            if( esValida(i+2,j+1,n) && !(graph[i+2][j+1].visited) ){
				visitarNodo(graph[i+2][j+1]);
				temp=make_pair(i+2,j+1);
				queue.push(temp);
            }
            if( esValida(i+2,j-1,n) && !(graph[i+2][j-1].visited) ){
				visitarNodo(graph[i+2][j-1]);
				temp=make_pair(i+2,j-1);
				queue.push(temp);
            }
            if( esValida(i-2,j+1,n) && !(graph[i-2][j+1].visited) ){
				visitarNodo(graph[i-2][j+1]);
				temp=make_pair(i-2,j+1);
				queue.push(temp);
            }
            if( esValida(i-2,j-1,n) && !(graph[i-2][j-1].visited) ){
				visitarNodo(graph[i-2][j-1]);
				temp=make_pair(i-2,j-1);
				queue.push(temp);
            }
            if( esValida(i+1,j+2,n) && !(graph[i+1][j+2].visited) ){
				visitarNodo(graph[i+1][j+2]);
				temp=make_pair(i+1,j+2);
				queue.push(temp);
            }
            if( esValida(i-1,j+2,n) && !(graph[i-1][j+2].visited) ){
				visitarNodo(graph[i-1][j+2]);
				temp=make_pair(i-1,j+2);
				queue.push(temp);
            }
            if( esValida(i+1,j-2,n) && !(graph[i+1][j-2].visited) ){
				visitarNodo(graph[i+1][j-2]);
				temp=make_pair(i+1,j-2);
				queue.push(temp);
            }
            if( esValida(i-1,j-2,n) && !(graph[i-1][j-2].visited) ){
				visitarNodo(graph[i-1][j-2]);
				temp=make_pair(i-1,j-2);
				queue.push(temp);
            }
        }


void BFS(vector<vector<casilla> >& graph, int i, int j, int n)
{

    // Create a queue for BFS
    queue<pair<int,int> > queue;

    // Mark the current node as visited and enqueue it
    graph[i][j].visited = true;
    queue.push(make_pair(i,j));

    // 'i' will be used to get all adjacent vertices of a vertex
    //list<int>::iterator i;
	pair<int,int> src;
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        src = queue.front();
        //cout << s << " ";
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
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
		cin>>cab.first;
		cin>>cab.second;
		kCab.push_back(cab);
		}

	///inicializo nodos
	casilla temp=casilla();

	vector<vector<casilla> > graph(n);
	for(int i=0;i<n;++i){
		graph[i].resize(n);
		for (int j=0;j<n;++j){
				graph[i][j]=temp;//¿copia o ref?
			}

		}

	for(int z=0;z<k;++z){
		//ver inicial
		BFS(graph, kCab[z].first, kCab[z].second,n); //hago bfs
		for(int i = 0; i < n; ++i){ // limpio campos del bfs
			for(int j=0;j<n;++j){
				(graph[i][j]).visited = false;
				(graph[i][j]).distSrc = 0;
			}
		}

}
	ImprimirSolucion(graph, k);

    return 0;
}
