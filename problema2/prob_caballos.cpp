
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <queue>          // std::queue
using namespace std;

struct casilla {
        bool visited
        int kVisitado;
        int num; //fila del tablero
        int saltosNecesarios;
        int distSrc;
};

void BFS(vector<vector<casilla> >& graph, casilla& cab)
{
	
    // Create a queue for BFS
    queue<casilla> queue;
 
    // Mark the current node as visited and enqueue it
    cab.visited = true;
    queue.push(cab);
 
    // 'i' will be used to get all adjacent vertices of a vertex
    //list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        src = queue.front();
        cout << s << " ";
        queue.pop();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(int w = 0; w<n; ++w)
        {
			if(){}///chequear que sean adj
            if( !(graph[src.num][w].visited) )//chequear visita 
            {
                graph[src.num][w].visited = true;
                graph[src.num][w].kVisitado++;
                graph[src.num][w].distSrc= src.distSrc+1;
                graph[src.num][w].saltosNecesarios+=graph[src.num][w].distSrc;
                queue.push(graph[src.num][w]);
            }
        }
        
    }
}


   

	
int main() {
	
	
	///leer entrada
	
	int w=k;
while(w){
		BFS(graph, cab); //hago bfs
		for(int i = 0; i < n; ++i){ // limpio campos del bfs
			for(int j=0;j<n;++j){
				(graph[i][j]).visited = false;
				(graph[i][j]).distSrc = 0;
			}
		}
		w--;
}
ImprimirSolucion(graph, k);
    
    return 0;
}
