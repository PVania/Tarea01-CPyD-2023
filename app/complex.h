#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/*
    NOTA!!!!!
    RECIBE UN POLINOMIO DE GRADO 2
    Ej.: Si hay grado 3 hay q derivar y se tiene un grado 2
    Si hay más grados, pues valió verga
*/
vector<string> rootsComplexDegreeTwo(float a, float b, float c) {
  vector<string> roots;
  float x1, x2, discriminant, realPart, imaginaryPart;
  discriminant = b * b - 4 * a * c;
  if (discriminant > 0) {
    x1 = (-b + sqrt(discriminant)) / (2 * a);
    x2 = (-b - sqrt(discriminant)) / (2 * a);
    // Caso 1: Raíces reales y diferentes
    // cout << "R 1: " << x1 << endl;
    // cout << "R 2: " << x2 << endl;
    roots.push_back(to_string(x1));
    roots.push_back(to_string(x2));
  } else if (discriminant == 0) {
    // Caso 2: Raíces reales y iguales
    x1 = (-b + sqrt(discriminant)) / (2 * a);
    // cout << "R 1: " << x1 << endl;
    roots.push_back(to_string(x1));
  } else {
    realPart = -b / (2 * a);
    imaginaryPart = sqrt(-discriminant) / (2 * a);
    //Caso 3: Raíces complejas y diferentes
    roots.push_back(to_string(realPart)+"+"+to_string(imaginaryPart)+"i");
    roots.push_back(to_string(realPart)+"-"+to_string(imaginaryPart)+"i");
    //cout << "R1: " << realPart << "+" << imaginaryPart << "i" << endl;
    //cout << "R2: " << realPart << "-" << imaginaryPart << "i" << endl;
  }
  return roots;
}
