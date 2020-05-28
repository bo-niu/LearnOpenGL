#pragma once
#include "Matrix.hpp"

namespace Bo {

	template<typename T, size_t L>
	class VectorX : public Matrix<T>
	{
	public:

		VectorX() : Matrix<T>(L, 1) {}

		~VectorX() {};

		VectorX(const Matrix<T>& m) : Matrix<T>(m) {
			assert(m.getCols() == 1 && m.getRows() == L);
		};

		size_t size() { return this->_rows; }

		inline T& operator[](const size_t& index) const {
			return this->_mat[index][0];
		}

		void normalize() {
			T l = 0;
			for (int i = 0; i < this->_rows; i++) {
				l += this->_mat[i][0] * this->_mat[i][0];
			}
			l = sqrt(l);
			for (int i = 0; i < this->_rows; i++)
				this->_mat[i][0] = this->_mat[i][0] / l;
		}

		T dotProduct(const VectorX<T, L>& v) {
			T dot = 0;
			for (int i = 0; i < this->_rows; i++) {
				dot += this->_mat[i][0] * v[i];
			}
			return dot;
		}

	};

}