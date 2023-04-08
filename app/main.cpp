#include <cstdlib>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int posCaracter(string cad, char carac) {
  int position = -1;
  for (int i = 0; i < cad.length(); i++) {
    if (cad[i] == carac) {
      position = i;
    }
  }
  return position;
}

int main() {
  string polynomial;

  /*NOTA: ESTO NO ES LO QUE PIDE EL PROFE:
  SE DEBE PEDIR POR CMD, TE PUEDE INGRESAR UN POLINOMIO   CUALQUIERA EN DISTINTO
  ORDEN Y SOLO QUIERE QUE LE ENTREGEN LAS RAICES (SEGUN EL GRADO)... NADA MAS...
  OCUPEN OPENMP
  */
  /*SINTAXIS DE INGRESO DEL POLINOMIO*/
  /* nx**m + nx**m - nx**m - nx + n */
  cout << "Formato del polinomio: nx**m - nx + n";
  cout << "\nPolinomio: ";
  cin >> polynomial;
  // x**3 + x

  /*SEPARANDO SINTAXIS EN ARREGLOS*/
  /*Generando arreglos de coeficientes*/
  int size = polynomial.size();
  int altCoefficient;
  int asterisk = 0;
  int highestGrade = 0;
  for (int i = 0; i < size; i++) {
    // 1. Busca el grado más alto
    if (polynomial[i] == '*') {
      asterisk++;
    }
    if (asterisk == 2 && polynomial[i] != '*') {
      if ((polynomial[i] - '0') > highestGrade) {
        highestGrade = (polynomial[i] - '0');
      }
      asterisk = 0;
    }
  } // PARTE I OK!!!

  // 2. Se separa por 'tokens' (ej.: 2x**2)
  vector<string> tokens;
  string token = "";
  for (int i = 0; i < size; i++) {
    // Guardar mientras no aparezna un nuevo monomio
    if (polynomial[i] != '+' && polynomial[i] != '-') {
      token.push_back(polynomial[i]);
      // token += polynomial[i];
    } else { // Nuevo token
      tokens.push_back(token);
      if (polynomial[i] == '-') {
        token = polynomial[i];
      } else {
        token = "";
      }
    }
    if (i == size - 1) {
      tokens.push_back(token);
    }
  } // PARTE II OK!!!

  // posicion de la cadena

  // 3. Crea un vector según el grado del polinomio
  // vector <int> coef [highestGrade + 1];
  int coef[highestGrade + 1];
  for (int i = 0; i <= highestGrade + 1; i++) {
    coef[i] = 0;
  }
  int num = 0;
  int degree = 0;

  for (int i = 0; i < tokens.size(); i++) {
    string word;
    word = tokens[i];
    cout << "Token: " << word << endl;
    int p = posCaracter(word, '-');
    cout << "Largo del token: " << word.length() << endl;
    cout << typeid(word).name() << endl;
    char c;
    int sizeW = word.length();
    cout << "P: " << p << endl;
    cout << "Error [1]" << endl;
    if (p != -1) { // Hay signo
      cout << "Error [1.1]" << endl;
      while (word.length() > 1) {
        cout << "Error [1.2]" << endl;
        c = word.back();
        // Caso 1: 2x**3
        if (sizeW-1 == 5) {
          cout << "Error [1.3]" << endl;
          if(degree == 0)
            degree = c - '0';
          if (c != '*' && c != 'x') {
            num = (c - '0') * -1;
          }
        }
        // Caso 2: x**3
        if (sizeW-1 == 4) {
          cout << "Error [1.4]" << endl;
          if(degree == 0)
            degree = c - '0';
          if (c != '*' && c != 'x') {
            num = -1;
          }
        }
        // Caso 3: 2x
        if (sizeW-1 <= 2 && sizeW >= 1) {
          cout << "Error [1.5]" << endl;
          if(degree == 0)
            degree = 1;
          if (c != 'x') { // Hay numero
            num = (c - '0') * -1;
          } else {
            num = -1;
          }
        }
        // Caso 4: n
        if (sizeW-1 == 1 && c != 'x') {
          cout << "Error [1.6]" << endl;
          degree = 0;
          num = (c - '0') * -1;
        }
        word.pop_back();
      }
    } else { // No hay signo
      cout << "Error [2.1]" << endl;
      while (word.length() > 0) {
        c = word.back();
        cout << "Error [2.2]" << endl;
        // Caso 1: 2x**3
        if (sizeW == 5) {
          cout << "Error [2.3]" << endl;
          if(degree == 0)
            degree = c - '0';
          if (c != '*' && c != 'x') {
            num = (c - '0');
          }
        }
        // Caso 2: x**3
        if (sizeW == 4) {
          cout << "Error [2.4]" << endl;
          if(degree == 0)
            degree = c - '0';
          if (c != '*' && c != 'x') {
            num = 1;
          }
        }
        // Caso 3: 2x
        if (sizeW-1 <= 2 && sizeW >= 1) {
          cout << "Error [2.5]" << endl;
          if(degree == 0)
            degree = 1;
          if (c != 'x') { // Hay numero
            num = (c - '0');
          } else {
            num = 1;
          }
        }
        // Caso 4: n
        if (sizeW == 1 && c != 'x') {
          cout << "Error [2.6]" << endl;
          degree = 0;
          num = c - '0';
        }
        cout << "Largo actualizado: " << word.length();
        word.pop_back();
      }
    }
    cout << "\nGrado: " << degree << endl;
    cout << "Coef: " << num << endl;
    
    coef[degree] = num;
    degree = 0;
  }

  //* DE AQUI PARA ARRIBA BORREN LOS COMENTARIOS INECESARIO PLS*//
  cout << "--------------------------" << endl;

  // 4.  Entregando arreglo con coef segun grado
  for (int j = 0; j < highestGrade + 1; j++) {
    cout << "Gr [" << j << "]: " << coef[j] << endl;
  }

  // 5. Mostrar raíces
  // Este paso falta, acomodar las funciones al codigo y mostrar las raices como quiere el profe (El punto 4 se puede borrar, es solo para saber si esta guardando el polinomio bien)
}