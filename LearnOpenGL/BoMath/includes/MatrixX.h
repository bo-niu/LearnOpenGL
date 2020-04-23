#pragma once
#include "Matrix.hpp"

namespace Bo {

	template<typename T, size_t L>
	class MatrixX : public Matrix<T>
	{
	public:

		MatrixX() : Matrix<T>(L, L) {}

		~MatrixX() {};

		MatrixX(const Matrix<T>& m) : Matrix<T>(m) {
			assert(m.getCols() == m.getRows());
			for (int i = 0; i < this->_rows; i++) {
				memcpy_s(this->_mat[i], sizeof(T) * this->_cols, m[i], sizeof(T) * this->_cols);
			}
			
		};

		size_t size() { return this->_rows; }

		void normalize() {
			std::cout << "not finished." << std::endl;
			assert(false);
		}

	};

}



