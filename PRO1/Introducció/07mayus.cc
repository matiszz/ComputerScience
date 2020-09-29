#include <iostream>
using namespace std;

int main() {
  char letra;
  int dist=0;
  cin >> letra;
  if (letra >= 'a' and letra <= 'z') {//Si está entre la "a" minúscula y la "z" minúscula, significa que la letra es minúscula
    dist = letra-'a'; //Contar la distancia desde la "a" hasta la letra
    cout << char('A'+dist) << endl; //Sumar a la "A" la distancia
    //Es importante forzar a imprimir un "char", sino imprime un entero
  } else {
    dist= letra-'A'; //Contar la distancia desde la "A" hasta la letra
    cout << char('a'+dist) << endl; //Sumar a la "a" la distancia
  }
}