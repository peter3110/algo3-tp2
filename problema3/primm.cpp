
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#define INT_MAX 10000001
using namespace std;

bool ordenarPares(pair< pair<int,int> , int > a, pair< pair<int,int>,int > b){
        return a.second<b.second;
}


int minKey(vector<int>& key, vector<bool>& mstSet, int V)
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 1; v <= V; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;

   return min_index;
}

vector<pair < pair<int,int>,int> >  primm(vector<vector<int> >& graph, int cantNodos){

     vector<int> parent(cantNodos+1); // Array to store constructed MST
     vector<int> key(cantNodos+1);    // Key values used to pick minimum weight edge in cut
     vector<bool> mstSet(cantNodos+1);  // To represent set of vertices not yet included in MST
     pair<pair<int, int>,int > temp;
     vector<pair < pair<int,int>,int> > aristas;
     // Initialize all keys as INFINITE
     for (int i = 1; i <= cantNodos; i++)
        key[i] = INT_MAX, mstSet[i] = false;

     // Always include first 1st vertex in MST.
     key[1] = 1;     // Make key 0 so that this vertex is picked as first vertex
     parent[1] = -1; // First node is always root of MST

     // The MST will have V vertices
     for (int count = 1; count <= cantNodos; count++)
     {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, cantNodos);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 1; v <= cantNodos; v++){

           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (mstSet[v] == false && graph[u][v] <  key[v]){
             parent[v]  = u, key[v] = graph[u][v];

          }
     }
     }

     for(int i=2; i<=cantNodos; i++){
        temp.second=key[i];
        (temp.first).first=parent[i];
        (temp.first).second=i;
        aristas.push_back(temp);
     }

      // print the constructed MST
      //cout<<(aristas.top()).first<<endl;
      //printf("Edge   Weight\n");
      //for (int i = 1; i < cantNodos; i++){
      //printf("%d - %d    %f \n", parent[i]+1, i+1, graph[i][parent[i]]);}
      return aristas;
}
