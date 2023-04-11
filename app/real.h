/*Newton-Raphson*/
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/*
Me estoy guiando por esto:
https://www.youtube.com/watch?time_continue=432&v=n53t8CtaLrM
*/

float Fx(int coef[], int size, float x) {
  float fx = 0;
  int i;
  //cout << "Evaluando en F(" << x << "): ";
  // Evaluar x en F(x)
  //  f(x) = x**5 - x  - 1
  //[ 1 | -1 | 0 | 0 | 0 | 1 ]
  for (i = 0; i < size; i++) {
    if (coef[i] != 0 && i != 0){
      fx += coef[i] * pow(x, i);
      //cout << "Fx += " << fx << endl;
    }
    else if (i == 0 && coef[i] != 0){
      fx += coef[i];
      //cout << "Fx += " << fx << endl;
    }
  }
  //cout << fx << endl;
  return fx;
}

string Convert (float number){
    ostringstream buff;
    buff<<number;
    return buff.str();   
}

vector<string> rootReal(int coefArray[], int longArray) {
  vector<string> roots;
  //           -9999999901
  int before = -999999999, result = 0, num = -10, numBefore = 0, aprox1, aprox2;
  int x1, x2;
  // 1. Obtener los maximos y minimos:
  //      Se sustituye valores de 'x' y tomar aquellos puntos que haya
  //      la conversión de (-) a (+)

  // Va a ir reemplazando x del -100 al 100
  while (num <= 10) {
    result = Fx(coefArray, longArray, num);
    // Antes de evaluar el sig f(x) comparar si hay cambio de signo
    //cout << result << ">" << before << endl;
    if (result >= before) {
      //cout << before << " < " << "0 ? " << (before < 0) << endl;
      //cout << result << " > " << "0 ? " << (result >= 0) << endl;
      if (before < 0 && result >= 0) {
        // Se encuentra puntos criticos
        //  Ej.:
        //  F(1) = -6
        //  F(2) = -1  *  pto min
        //  F(3) = 16  *  pto max
        x1 = before;
        x2 = result;
        //cout << "x1: " << x1 << endl;
        //cout << "x2: " << x2 << endl;
        aprox1 = numBefore;
        aprox2 = num;
        //cout << "Num ant: " << aprox1 << endl;
        //cout << "Num: " << aprox2 << endl;
        break;
      } else {
        before = result;
        numBefore = num;
        //cout << "result before: " << before << endl;
        //cout << "num Before: " << numBefore << endl;
      }
    }
      num++;
  }

  //Punto critico
  int crit;
  if(x1>x2){
    crit = numBefore;
  } else {
    crit = num;
  }

  // 3. Formula
  float x = (float)crit, prev = x;
  
  // 3.1 Derivamos el polinomio
  int derivative[longArray - 1];
  for (int x = 0; x < longArray; x++) {
    derivative[x] = 0;
  }

  for (int i = 0; i < longArray; i++) {
    if (coefArray[i] != 0) {
      // f(x) = x**5 - x  - 1
      //[ 1 | -1 | 0 | 0 | 0 | 1 ]
      // f(x)' = 5x**4 - 1
      //[ -1 | 0 | 0 | 0 | 5 ]
      if (i != 0) {
        derivative[i - 1] = coefArray[i] * i;
      } else {
        // En caso de ser numero independiente
        // No haga nada
      }
    }
  }
  // 3.2 Aplicamos la formula
  // Xn+1 = Xn - F(Xn)/F'(Xn)
  bool raiz = false;
  while (raiz == false){
    //cout << "Ultimo while" << endl;
    x = x - Fx(coefArray, longArray, x) / Fx(derivative, longArray - 1, x);// x2 = 1.25  -- 1.17877 ---
    //cout << "---------\nAnt: " << prev << " igual a " << x << "? " << (fabs(prev - x) < 0.005f) << endl;
    //cout << "Tipo de dato prev: " <<  typeid(prev).name() << endl;
    //cout << "Tipo de dato x: " <<  typeid(x).name() << endl;
    if (fabs(prev - x) < 0.005f){
    //if (prev == x){
      raiz = true;
      //cout << "Raiz: " << x <<  endl;
      //cout << "Tipo de dato raiz: " <<  typeid(x).name() << endl;
      
      roots.push_back(to_string(x));
    } else {
      prev = x;
    }
  }
  return roots;
}

// PASOS:
//  1. Obtener los maximos y minimos
//  2. Seleccionamos nuestra aproximacion
//  3. Aplicar la formula Xn+1 = Xn - F(Xn)/F'(Xn)
//         -> Si se repire la misma aprox quiere decir q es el num en x hace 0,
//         osea raiz