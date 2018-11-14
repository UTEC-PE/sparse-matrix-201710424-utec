#include <GL/glut.h>
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(5, 5);
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        std::cout << a(i, j) << ' ';
      }
      std::cout << '\n';
    }
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        a.set(i, j, i + j);
      }
    }
    std::cout << '\n';
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        std::cout << a(i, j) << ' ';
      }
      std::cout << '\n';
    }
    a.set(4,3, 0);
    a.set(1,2, 0);
    a.set(2,4, 0);
    a.set(4,3, 0);
    a = a.transposed();
    std::cout << '\n';
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        std::cout << a(i, j) << ' ';
      }
      std::cout << '\n';
    }
    a = a * a;
    std::cout << '\n';
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        std::cout << a(i, j) << ' ';
      }
      std::cout << '\n';
    }
    return 0;
}
