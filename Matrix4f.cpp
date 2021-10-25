#include "Matrix4f.h"

// For std::swap
#include <algorithm>

Matrix4f::Matrix4f() {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] = 0.0f;
    }
}

Matrix4f::Matrix4f(const Matrix4f &other_matrix) {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] = other_matrix.elements[i];
    }
}

void Matrix4f::transpose() {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            std::swap(elements[4 * i + j], elements[4 * j + i]);
        }
    }
}

Matrix4f Matrix4f::operator+(const Matrix4f &other_matrix) const {
    Matrix4f result;
    for (int i = 0; i < 4 * 4; ++i) {
        result.elements[i] = elements[i] + other_matrix.elements[i];
    }
    return result;
}

void Matrix4f::operator+=(const Matrix4f &other_matrix) {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] += other_matrix.elements[i];
    }
}

Matrix4f Matrix4f::operator-(const Matrix4f &other_matrix) const {
    Matrix4f result;
    for (int i = 0; i < 4 * 4; ++i) {
        result.elements[i] = elements[i] - other_matrix.elements[i];
    }
    return result;
}

void Matrix4f::operator-=(const Matrix4f &other_matrix) {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] -= other_matrix.elements[i];
    }
}

Matrix4f Matrix4f::operator*(const Matrix4f &other_matrix) const {
    Matrix4f result;
    for (int i = 0; i < 4 * 4; ++i) {
        result.elements[i] = elements[i] * other_matrix.elements[i];
    }
    return result;
}

void Matrix4f::operator*=(const Matrix4f &other_matrix) {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] *= other_matrix.elements[i];
    }
}



Matrix4f::operator const float *() {
    return reinterpret_cast<const float *>(&elements[0]);
}

void Matrix4f::set_to_identity() {
    for (int i = 0; i < 4 * 4; ++i) {
        elements[i] = 0.0f;
    }
    for (int i = 0; i < 4; ++i) {
        // 5 * i = 4 * i (row) + i (col)
        elements[5 * i] = 1.0f;
    }
}