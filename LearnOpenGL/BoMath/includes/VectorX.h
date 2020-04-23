#pragma once
#include "Matrix.hpp"

namespace Bo {

	template<typename T, size_t L>
	class VectorX : public Matrix<T>
	{
	public:

		VectorX() : Matrix<T>(L, 1) {}

		~VectorX() {};

		VectorX(const Matrix<T>& m) : Matrix<T>(L, 1) {
			assert(m._cols == 1);
		};

		size_t size() { return this->_rows; }

		void normalize() {

		}

	};

}