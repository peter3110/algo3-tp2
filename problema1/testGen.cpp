
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <time.h>
using namespace std;

string generate_next_string(string &str) {
	std::next_permutation(str.begin(), str.end());
	return str;
}

int main(int argc, char **argv) {
	
  freopen("input.in", "w", stdout);
  
  int CANT_CIUDADES = atoi(argv[1]);
  int CANT_VUELOS = atoi(argv[2]);
  int horario_izq = atoi(argv[3]);
  int horario_der = atoi(argv[4]);
  int horario_salida, horario_llegada;
  int ciudad1, ciudad2;
  
  /* Genero el set de ciudades */
  string ciudades[CANT_CIUDADES];
  string s = "abcd";
  for(int i=0; i<CANT_CIUDADES; i++) {
	  ciudades[i] = generate_next_string(s); 
  }
  
  /* Decido de donde a donde quiero llegar */
  srand(time(NULL));
  ciudad1 = rand() % CANT_CIUDADES;
  ciudad2 = rand() % CANT_CIUDADES;
  if (ciudad1 == ciudad2) {ciudad2--;}
  cout << ciudades[ciudad1] << " " << ciudades[ciudad2] << " ";
  cout << CANT_VUELOS << endl;
  
  /* Organizo viajes entre ciudades random en horarios random */
  for(int i=0; i<CANT_VUELOS; i++) {
	horario_salida  = horario_izq + (rand() % (horario_der - horario_izq));
	horario_llegada = horario_salida + 2 + (rand() % (horario_der - horario_salida));
    ciudad1 = rand() % CANT_CIUDADES;
    ciudad2 = rand() % CANT_CIUDADES;
    cout << ciudades[ciudad1] << " " << ciudades[ciudad2] << " ";
    cout << horario_salida << " " << horario_llegada << endl;
  } 
  
  
  return 0;	
}
