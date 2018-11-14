#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix() {};
        Matrix(int sizeX, int sizeY) {
          if (sizeX > 0 && sizeY > 0) {
            this->rows = sizeX;
            this->columns = sizeY;
            Node<T>* lastEntry = nullptr;
            for (int i = this->rows-1; i > -1; i--) {
              Node<T>* newNode = new Node<T> {i, -1, 0, nullptr, lastEntry};
              lastEntry = newNode;
              newNode = nullptr;
            }
            this->hRows = lastEntry;
            lastEntry = nullptr;
            for (int i = this->columns-1; i > -1; i--) {
              Node<T>* newNode = new Node<T> {-1, i, 0, lastEntry, nullptr};
              lastEntry = newNode;
              newNode = nullptr;
            }
            this->hColumns = lastEntry;
          } else throw("Invalid size");
        };

        void set(int x, int y, T data){
          if (x < 0 || y < 0) {
            throw("Invalid position");
          }

          if (x < this->rows && y < this->columns) {
            if (x <= y) {
              Node<T>* currentNode = this->hRows;
              for (size_t i = 0; i < x; i++) {
                currentNode = currentNode->down;
              }
              Node<T>* previusXNode = currentNode;
              currentNode = currentNode->next;
              while (currentNode != nullptr && currentNode->y < y) {
                currentNode = currentNode->next;
                previusXNode = previusXNode->next;
              }
              bool existNode = currentNode != nullptr && currentNode->y == y;
              if ((existNode && data == 0) || (!existNode && data != 0)) {
                Node<T>* previusYNode = this->hColumns;
                for (size_t i = 0; i < y; i++) {
                  previusYNode = previusYNode->next;
                }
                while (previusYNode->down != currentNode && (previusYNode->down)->x < x) {
                  previusYNode = previusYNode->down;
                }
                if (data == 0) {
                  previusXNode->next = currentNode->next;
                  previusYNode->down = currentNode->down;
                  delete currentNode;
                  currentNode = nullptr;
                  return;
                } else {
                  currentNode = new Node<T> {x, y, data, previusXNode->next, previusYNode->down};
                  previusXNode->next = currentNode;
                  previusYNode->down = currentNode;
                  currentNode = nullptr;
                  return;
                }
              } else {
                if (data != 0) {
                  currentNode->data = data;
                  return;
                } else return;
              }
            } else {
              Node<T>* currentNode = this->hColumns;
              for (size_t i = 0; i < y; i++) {
                currentNode = currentNode->next;
              }
              Node<T>* previusYNode = currentNode;
              currentNode = currentNode->down;
              while (currentNode != nullptr && currentNode->x < x) {
                currentNode = currentNode->down;
                previusYNode = previusYNode->down;
              }
              bool existNode = currentNode != nullptr && currentNode->x == x;
              if ((existNode && data == 0) || (!existNode && data != 0)) {
                Node<T>* previusXNode = this->hRows;
                for (size_t i = 0; i < x; i++) {
                  previusXNode = previusXNode->down;
                }
                while (previusXNode->next != currentNode && (previusXNode->next)->y < y) {
                  previusXNode = previusXNode->next;
                }
                if (data == 0) {
                  previusXNode->next = currentNode->next;
                  previusYNode->down = currentNode->down;
                  delete currentNode;
                  currentNode = nullptr;
                  return;
                } else {
                  currentNode = new Node<T> {x, y, data, previusXNode->next, previusYNode->down};
                  previusXNode->next = currentNode;
                  previusYNode->down = currentNode;
                  currentNode = nullptr;
                  return;
                }
              } else {
                if (data != 0) {
                  currentNode->data = data;
                  return;
                } else return;
              }
            }
          } else throw("Element out range");
        };

        T operator()(int x, int y) {
          if (x < 0 || y < 0) {
            throw("Invalid position");
          }

          if (x < this->rows && y < this->columns) {
            if (x <= y) {
              Node<T>* currentNode = this->hRows;
              for (size_t i = 0; i < x; i++) {
                currentNode = currentNode->down;
              }
              while (currentNode != nullptr && currentNode->y < y) {
                currentNode = currentNode->next;
              }
              if (currentNode != nullptr && currentNode->y == y) {
                return currentNode->data;
              } else return 0;
            } else {
              Node<T>* currentNode = this->hColumns;
              for (size_t i = 0; i < y; i++) {
                currentNode = currentNode->next;
              }
              while (currentNode != nullptr && currentNode->x < x) {
                currentNode = currentNode->down;
              }
              if (currentNode != nullptr && currentNode->x == x) {
                return currentNode->data;
              } else return 0;
            }
          } else throw("Element out range");
        };

        Matrix<T> operator*(Matrix<T> other) {
          if (this->columns == other.rows) {
            Matrix<T> newMatrix = Matrix(this->rows, other.columns);
            T acumulator = 0;
            for (size_t i = 0; i < this->rows; i++) {
              for (size_t j = 0; j < other.columns; j++) {
                acumulator = 0;
                for (size_t k = 0; k < this->columns; k++) {
                  acumulator = acumulator + ((*this)(i, k) * other(k, j));
                }
                newMatrix.set(i, j, acumulator);
              }
            }
            return newMatrix;
          } else throw("Invalid sizes");
        };
        Matrix<T> operator*(T scalar) {
          Matrix<T> newMatrix(this->rows, this->columns);
          for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->columns; j++) {
              newMatrix.set(i, j, (*this)(i, j) * scalar);
            }
          }
          return newMatrix;
        };
        Matrix<T> operator+(Matrix<T> other) {
          if (this->columns == other.columns && this->rows == other.rows) {
            Matrix<T> newMatrix(this->rows, this->columns);
            for (size_t i = 0; i < this->rows; i++) {
              for (size_t j = 0; j < this->columns; j++) {
                newMatrix.set(i, j, (*this)(i, j) + other(i, j));
              }
            }
            return newMatrix;
          } else throw("Invalid sizes");
        };
        Matrix<T> operator-(Matrix<T> other) {
          if (this->columns == other.columns && this->rows == other.rows) {
            Matrix<T> newMatrix(this->rows, this->columns);
            for (size_t i = 0; i < this->rows; i++) {
              for (size_t j = 0; j < this->columns; j++) {
                newMatrix.set(i, j, (*this)(i, j) - other(i, j));
              }
            }
            return newMatrix;
          } else throw("Invalid sizes");
        };
        Matrix<T> transposed() {
          Matrix<T> newMatrix(this->columns, this->rows);
          for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->columns; j++) {
              newMatrix.set(j, i, (*this)(i, j));
            }
          }
          return newMatrix;
        };
        Matrix<T>& operator=(Matrix<T> other) {
          if (this->rows > other.rows) {
            for (size_t i = other.rows; i < this->rows; i++) {
              for (size_t j = 0; j < this->columns; j++) {
                this->set(i, j, 0);
              }
            }
            Node<T>* nodeToDestroy = this->hRows;
            Node<T>* currentNode = this->hRows;
            for (size_t i = 0; i < other.rows; i++) {
              currentNode = currentNode->down;
            }
            nodeToDestroy = currentNode->down;
            currentNode->down = nullptr;
            for (size_t i = other.rows; i < this->rows; i++) {
              currentNode = nodeToDestroy->down;
              delete nodeToDestroy;
              nodeToDestroy = currentNode;
            }
          }else if (this->rows < other.rows) {
            Node<T>* currentNode = this->hRows;
            while (currentNode->down != nullptr) {
              currentNode = currentNode->down;
            }
            for (int i = this->rows; i < other.rows; i++) {
              Node<T>* newNode = new Node<T> {i, -1, 0, nullptr, nullptr};
              currentNode->down = newNode;
              currentNode = currentNode->down;
            }
          }
          this->rows = other.rows;
          if (this->columns == other.columns) {
            for (size_t i = 0; i < other.rows; i++) {
              for (size_t j = 0; j < other.columns; j++) {
                this->set(i, j, other(i,j));
              }
            }
          }else if (this->columns > other.columns) {
            for (size_t i = 0; i < other.rows; i++) {
              for (size_t j = 0; j < other.columns; j++) {
                this->set(i, j, other(i,j));
              }
              for (size_t j = other.columns; j < this->columns; j++) {
                this->set(i, j, 0);
              }
            }
            Node<T>* nodeToDestroy = this->hColumns;
            Node<T>* currentNode = this->hColumns;
            for (size_t i = 0; i < other.columns; i++) {
              currentNode = currentNode->next;
            }
            nodeToDestroy = currentNode->next;
            currentNode->next = nullptr;
            for (size_t i = other.columns; i < this->columns; i++) {
              currentNode = nodeToDestroy->next;
              delete nodeToDestroy;
              nodeToDestroy = currentNode;
            }
          }else {
            Node<T>* currentNode = this->hColumns;
            while (currentNode->next != nullptr) {
              currentNode = currentNode->next;
            }
            for (int i = this->columns; i < other.columns; i++) {
              Node<T>* newNode = new Node<T> {-1, i, 0, nullptr, nullptr};
              currentNode->next = newNode;
              currentNode = currentNode->next;
            }
            for (size_t i = 0; i < other.rows; i++) {
              for (size_t j = 0; j < other.columns; j++) {
                this->set(i, j, other(i,j));
              }
            }
          }
          this->columns = other.columns;
          return *this;
        };

        // ~Matrix() {
        //   Node<T>* currentHeader = this->hRows;
        //   Node<T>* currentNode = nullptr;
        //   Node<T>* nodeToDestroy = nullptr;
        //   while (currentHeader != nullptr) {
        //     currentNode = currentHeader->next;
        //     nodeToDestroy = currentNode;
        //     while (currentNode != nullptr) {
        //       currentNode = currentNode->next;
        //       delete nodeToDestroy;
        //       nodeToDestroy = currentNode;
        //     }
        //     nodeToDestroy = currentHeader;
        //     currentHeader = currentHeader->down;
        //     delete nodeToDestroy;
        //   }
        //   currentHeader = this->hColumns;
        //   while (currentHeader != nullptr) {
        //     currentNode = currentHeader->down;
        //     nodeToDestroy = currentNode;
        //     while (currentNode != nullptr) {
        //       currentNode = currentNode->down;
        //       delete nodeToDestroy;
        //       nodeToDestroy = currentNode;
        //     }
        //     nodeToDestroy = currentHeader;
        //     currentHeader = currentHeader->next;
        //     delete nodeToDestroy;
        //   }
        // };
};

#endif
