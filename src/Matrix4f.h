#pragma once

class Matrix4f {
    private:
        float elements[4 * 4];
    public:
        /** Initilises a zero 4x4 matrix */
        Matrix4f();
        /** Creates acopy of another 4x4 matrix */
        Matrix4f(const Matrix4f &other_matrix);
        ~Matrix4f() = default;
    
        /**
         * Returns the value of the element in the @p row_id row
         * and @p col_id column in the matrix
         */
        inline float get_element(unsigned char row_id, unsigned char col_id) const {
            return elements[4 * col_id + row_id];
        }
        /**
         * Sets the value of the element in the @p row_id row
         * and @p col_id column in the matrix to the given value
         */
        inline void set_value(unsigned char row_id, unsigned char col_id, const float new_value) {
            elements[4 * col_id + row_id] = new_value;
        }
        /** Transposes the matrix */
        void transpose();

        Matrix4f operator+(const Matrix4f &other_matrix) const;
        void operator+=(const Matrix4f& other_matrix);
        Matrix4f operator-(const Matrix4f &other_matrix) const;
        void operator-=(const Matrix4f& other_matrix);
        Matrix4f operator*(const Matrix4f &other_matrix) const;
        void operator*=(const Matrix4f& other_matrix);

        /** Returns a pointer to the array of floats the matrix consists of */
        operator const float *();

        /** Modifies the matrix so that it's an identity matrix */
        void set_to_identity();
};