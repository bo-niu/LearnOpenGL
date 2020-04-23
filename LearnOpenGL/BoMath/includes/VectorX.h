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
			std::cout << "not finished." << std::endl;
			assert(false);
		}

	};

}