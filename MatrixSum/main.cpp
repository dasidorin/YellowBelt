#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() {
        //конструктор по умолчанию, должен создавать матрицу, содержащую 0 строк и 0 столбцов2
        matrix.resize(0);
    }

    Matrix(int num_rows, int num_cols) {
        //параметризованный конструктор, создает матрицу num_rows * num_cols
        //выкинуть out_of_range если дано отрицательное количество строк или столбцов
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("");
        }

        matrix.resize(num_rows);
        for (auto row : matrix) {
            row.resize(num_cols);
        }
    }

    void Reset(int num_rows, int num_cols) {
        //изменить размер матрицы и обнулить все эелементы
        //выкинуть out_of_range если дано отрицательное количество строк или столбцов
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("");
        }

        matrix.resize(num_rows);
        for (auto& row : matrix) {
            row.resize(num_cols);
            for (auto& item : row) {
                item = 0;
            }
        }
    }

    int At(int row, int col) const {
        //вернуть элемент по адресу [row][col]
        //выкинуть out_of_range если ячейка выходит за границв матрицы
        if (row > GetNumRows() - 1 || col > GetNumColumns() - 1) {
            throw out_of_range("");
        }

        return matrix[row][col];
    };

    int& At(int row, int col) {
        //вернуть ссылку на элемент по адресу [row][col]
        //выкинуть out_of_range если ячейка выходит за границв матрицы
        if (row > GetNumRows() - 1 || col > GetNumColumns() - 1) {
            throw out_of_range("");
        }

        return matrix[row][col];
    };

    int GetNumRows() const {
        //вернуть количество строк в матрице
        return matrix.size();
    }

    int GetNumColumns() const {
        //вернуть количество столбцов в матрице
        return matrix[0].size();
    }

private:
    vector <vector <int>> matrix;
};

bool IsEqualSize(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumColumns() == rhs.GetNumColumns() && lhs.GetNumRows() == rhs.GetNumRows()) {
        return true;
    }

    return false;
}

Matrix operator + (Matrix lhs, Matrix rhs) {

    if (!IsEqualSize(lhs, rhs)) {
        throw invalid_argument("");
    }

    Matrix res;
    res.Reset(lhs.GetNumRows(), lhs.GetNumColumns());

    for (int i = 0; i < res.GetNumRows(); ++i) {
        for (int j = 0; j < res.GetNumColumns(); ++j) {
            res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return res;
}
//если переданные матрицы имеют имеют разные размеры выкинуть invalid_argument

bool operator == (const Matrix& lhs, const Matrix& rhs) {

    if (!IsEqualSize(lhs, rhs)) {
        return false;
    }

    for (int i = 0; i < lhs.GetNumRows(); ++i) {
        for (int j = 0; j < lhs.GetNumColumns(); ++j) {
            if (lhs.At(i, j) != rhs.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}
//true если матрицы имеют одинаковый размер и все элементы равны между собой

istream& operator >> (istream& stream, Matrix& matrix){
    if (stream) {
        int num_rows, num_cols;
        stream >> num_rows >> num_cols;

        matrix.Reset(num_rows, num_cols);
        int item = 0;

        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; j++) {
                stream >> item;
                matrix.At(i, j) = item;
            }
        }
    }
    return stream;
}
//сначала задаётся количество строк и столбцов, а затем все элементы матрицы

ostream& operator << (ostream& stream, const Matrix& matrix) {
    if (stream) {
        stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;

        for (int i = 0; i < matrix.GetNumRows(); ++i) {
            for (int j = 0; j < matrix.GetNumColumns(); ++j) {
                stream << matrix.At(i, j) << " ";
            }
            stream << endl;
        }
    }
    return (stream);
}
//сначала выводится количество строк и столбцов, а затем все элементы матрицы

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
