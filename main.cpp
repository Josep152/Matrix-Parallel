#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Matrix {
  int **my_matrix;
  int row;
  int colum;

  // Contructor
  Matrix(int r, int c) {
    row = r;
    colum = c;
    my_matrix = new int *[row];
    for (int i = 0; i < row; i++) {
      my_matrix[i] = new int[colum];
    }

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < colum; j++) {
        my_matrix[i][j] = 0;
      }
    }
  }
  // Functions
  void fill() {
    int f;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < colum; j++) {
        cout << "matrix" << '[' << i << "][" << j << "] :";
        cin >> f;
        my_matrix[i][j] = f;
      }
    }
  }

  void fill_r() {
    int f;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < colum; j++) {
        my_matrix[i][j] = rand() % 21;
      }
    }
  }

  Matrix operator+(Matrix a) {
    if (a.row == row || a.colum == colum) {
      Matrix rpta(row, colum);
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < colum; j++) {
          rpta.my_matrix[i][j] = my_matrix[i][j] + a.my_matrix[i][j];
        }
      }
      return rpta;
    }
  }

  void operator=(Matrix a) {
    if (a.row == row || a.colum == colum) {
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < colum; j++) {
          my_matrix[i][j] = a.my_matrix[i][j];
        }
      }
    }
  }

  void print_m() {
    cout << endl;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < colum; j++) {
        cout << my_matrix[i][j] << ' ';
      }
      cout << endl;
    }
    cout << endl;
  }
  // Destructor
  /*~Matrix() {
      for (int i = 0; i < colum; i++){
          delete my_matrix[i];
      }
      delete my_matrix;
  }*/
};

// Multiplicacion Clasica
void multi_clasic(Matrix x, Matrix y) {
  cout << "\nTamaño de la nueva matriz: " << y.colum << ' ' << x.row << endl;

  if (x.colum != y.row) {
    cout << "\nOperacion impocible por las dimensiones.\n";
    return;
  }

  Matrix n_m(x.row, y.colum);

  for (int i = 0; i < x.row; i++) {
    for (int j = 0; j < y.colum; j++) {
      for (int k = 0; k < y.row; k++) {
        n_m.my_matrix[i][j] += x.my_matrix[i][k] * y.my_matrix[k][j];
      }
    }
  }

  // n_m.print_m();
}

// Multiplicacion por bloques
void multi_blocks(Matrix x, Matrix y) {
  cout << "\nTamaño de la nueva matriz: " << y.colum << ' ' << x.row << endl;

  if (x.colum != y.row) {
    cout << "\nOperacion impocible por las dimensiones.\n";
    return;
  }
  int blocks = 64; // Tamaño de los bloques
  Matrix n_m(x.row, y.colum);
  for (int ii = 0; ii < x.colum; ii += blocks) {
    for (int jj = 0; jj < x.colum; jj += blocks) {
      for (int kk = 0; kk < x.colum; kk += blocks) {

        for (int i = ii; i < ii + blocks; i++) {
          for (int j = jj; j < jj + blocks; j++) {
            for (int k = kk; k < kk + blocks; k++) {
              n_m.my_matrix[i][j] += x.my_matrix[i][k] * y.my_matrix[k][j];
            }
          }
        }
      }
    }
  }
  // n_m.print_m();
}

int main() {
  srand(time(NULL));

  int size_m = 512;

  Matrix my_m1(size_m, size_m);
  my_m1.fill_r();
  // my_m1.print_m();
  Matrix my_m2(size_m, size_m);
  my_m2.fill_r();
  // my_m2.print_m();

  unsigned t0, t1;

  /*t0 = clock();
  multi_clasic(my_m1, my_m2);
  t1 = clock();

  double time1 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time Clasic: " << time1 << endl;*/

  t0 = clock();
  multi_clasic(my_m1, my_m2);
  t1 = clock();

  double time2 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time by Blocks: " << time2 << endl;

  cout << "done!" << endl;
  return 0;
}