#pragma once

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Matrix<T> — a rows x cols grid of T, stored in one flat vector.
// (YOU implement the definitions marked TODO, below the class)
//
// One class template, used with two different element types:
//   Matrix<Color>   the image's pixels      (Grid in Filter.h)
//   Matrix<double>  a convolution kernel's weights
//
// Why is all of the code in the header? The compiler writes the real
// Matrix<Color> and Matrix<double> classes from this template when it
// sees them used. To do that it needs the full definitions, not just
// declarations, in every .cpp that uses a Matrix. So templates live in
// headers.
//
// Storage: element (r, c) lives at data_[r * cols_ + c]. One vector is
// faster and simpler than a vector of vectors, and every row is
// guaranteed to have the same length.
//
// Caution: Matrix<bool> won't compile with at()/operator() returning T&,
// because std::vector<bool> is a SPECIALIZATION (W07) that packs bits and
// can't hand out a bool&. Use Matrix<char> or Matrix<int> instead.
// -----------------------------------------------------------------------
template <typename T>
class Matrix {
public:
    // An empty 0 x 0 matrix.
    Matrix() = default;

    // rows x cols, every element a copy of 'fill'.
    // Throws std::invalid_argument if rows or cols is negative.
    Matrix(int rows, int cols, const T& fill = T{});

    // rows x cols from values listed row by row:
    //   Matrix<int> m(2, 3, {1, 2, 3,
    //                        4, 5, 6});
    // Throws std::invalid_argument if values.size() != rows * cols.
    Matrix(int rows, int cols, std::initializer_list<T> values);

    int rows() const;
    int cols() const;
    bool empty() const;   // true when there are no elements

    // Bounds-checked access. Throws std::out_of_range.
    T&       at(int r, int c);
    const T& at(int r, int c) const;

    // Unchecked access, for tight loops where the indices are known good.
    T&       operator()(int r, int c);
    const T& operator()(int r, int c) const;

    // Calls f(element) on every element, in row-major order.
    // f takes a T& and may change the element:
    //   m.forEach([](int& x) { x *= 2; });
    // F is a SECOND template parameter, on the member function itself:
    // forEach accepts a lambda, a function pointer, or any callable.
    template <typename F>
    void forEach(F f);

    // Same shape and every element equal.
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    // Lets you write  for (const T& x : m)  over every element.
    typename std::vector<T>::iterator       begin() { return data_.begin(); }
    typename std::vector<T>::iterator       end() { return data_.end(); }
    typename std::vector<T>::const_iterator begin() const { return data_.begin(); }
    typename std::vector<T>::const_iterator end() const { return data_.end(); }

private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<T> data_;

    void checkIndex(int r, int c) const;
};

// =======================================================================
// Definitions. Outside the class, every member needs the full
//     template <typename T>
//     ReturnType Matrix<T>::name(...)
// prefix. The first three are done for you as examples of the syntax.
// =======================================================================

template <typename T>
Matrix<T>::Matrix(int rows, int cols, const T& fill)
    : rows_(rows), cols_(cols) {
    if (rows < 0 || cols < 0)
        throw std::invalid_argument("Matrix dimensions can't be negative");
    data_.assign(static_cast<size_t>(rows) * cols, fill);
}

template <typename T>
int Matrix<T>::rows() const { return rows_; }

template <typename T>
int Matrix<T>::cols() const { return cols_; }

template <typename T>
T& Matrix<T>::operator()(int r, int c) {
    return data_[static_cast<size_t>(r) * cols_ + c];
}

template <typename T>
const T& Matrix<T>::operator()(int r, int c) const {
    return data_[static_cast<size_t>(r) * cols_ + c];
}

// ---------------- TODO: everything below ----------------

template <typename T>
Matrix<T>::Matrix(int rows, int cols, std::initializer_list<T> values)
    : rows_(rows), cols_(cols), data_(values) {
    // TODO: throw std::invalid_argument if rows/cols is negative, or if
    //   the number of values isn't rows * cols
}

template <typename T>
bool Matrix<T>::empty() const {
    return false;   // TODO
}

template <typename T>
void Matrix<T>::checkIndex(int r, int c) const {
    // TODO: throw std::out_of_range (with a helpful message) if (r, c)
    //   is outside the matrix
    (void)r;
    (void)c;
}

template <typename T>
T& Matrix<T>::at(int r, int c) {
    // TODO: check the index first
    return (*this)(r, c);
}

template <typename T>
const T& Matrix<T>::at(int r, int c) const {
    // TODO: check the index first
    return (*this)(r, c);
}

// A member template inside a class template needs TWO template headers:
// one for the class (T) and one for the member function (F).
template <typename T>
template <typename F>
void Matrix<T>::forEach(F f) {
    // TODO: call f(element) on every element of data_
    (void)f;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
    // TODO: same rows, same cols, same elements
    (void)other;
    return false;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) const {
    return !(*this == other);
}

// A free FUNCTION template: works for any T that has its own operator<<.
// Print one row per line, no newline after the last row:
//   [1, 2, 3]
//   [4, 5, 6]
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    // TODO
    (void)m;
    return os;
}
