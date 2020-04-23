#pragma once
#include "Matrix.hpp"

namespace Bo {

	template<typename T, size_t L>
	class MatrixX : public Matrix<T>
	{
	public:

		MatrixX() : Matrix<T>(L, L) {}

		~MatrixX() {};

		MatrixX(const Matrix<T>& m) : Matrix<T>(L) {};

		size_t size() { return this->_rows; }

		void normalize() {

		}

	};

}



