/*Newton-Raphson*/
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/*
Me estoy guiando por esto: https://www.youtube.com/watch?time_continue=432&v=n53t8CtaLrM
*/
vector<string> rootReal(int coefArray[], int longArray) {
  vector<string> roots;
  int before = -999999999, result = 0, num = -100, numBefore = 0, aprox1, aprox2;
  int x1, x2;
  // 1. Obtener los maximos y minimos:
  //      Se sustituye valores de 'x' y tomar aquellos puntos que haya
  //      la conversión de (-) a (+)

  // Va a ir reemplazando x del -100 al 100
  while (num <= 100) {
    for (int i = 0; i < longArray; i++) {
      if (coefArray[i] != 0) { // Slot no vacio
        result = pow(num * coefArray[i], i);
        if (result > before) {
          if (before < 0 && result > 0) {
            //Se encuentra puntos criticos
            // Ej.:
            // F(1) = -6
            // F(2) = -1  *  pto min
            // F(3) = 16  *  pto max
            x1 = before;
            x2 = result;
            cout << "x1: " << x1 << endl;
            cout << "x2: " << x2 << endl;
            aprox1 = numBefore;
            aprox2 = num;
          } else {
            before = result;
            numBefore = num;
          }
        }
      }
    }
    num++;
  }

  // 2. Aproximacion entre los puntos min y max
  
  
  // 3. Formula
  // 3.1 Derivamos el polinomio
  // 3.2 Aplicamos la formula 

  return roots;
}

// PASOS:
//  1. Obtener los maximos y minimos
//  2. Seleccionamos nuestra aproximacion
//  3. Aplicar la formula Xn+1 = Xn - F(Xn)/F'(Xn)
//         -> Si se repire el mismo num quiere decir q hace 0, osea raiz