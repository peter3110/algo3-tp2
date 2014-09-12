
#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <assert.h>
using namespace std;

struct equipo {
    int id;
    int usado;
    // int pesoDeConexiones;
    vector<equipo> seConectaCon;
};

struct conexion {
    int e1, e2;
};

int main() {
  
  int n, m, e1, e2, c;
  
  while(cin >> n >> m) {
      for(int i=0; i<m; i++) {
          cin >> e1 >> e2 >> c;
      }
  }
    
  
  return 0;
}
