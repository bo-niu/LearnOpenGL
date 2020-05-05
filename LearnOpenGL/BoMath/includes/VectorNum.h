#pragma once
#include "VectorX.h"

namespace Bo {

	template<typename T>
	class Vector3 : public VectorX<T, 3>
	{
	public:
		Vector3() : VectorX<T, 3>() {};

		Vector3(const Matrix<T> &m) : VectorX<T, 3>(m) {
			assert(m.getCols() == m.getRows() && m.getCols() == 3);
		};


		Vector3<T> crossProduct(const Vector3<T>& v) {
			return crossProduct(*this, v);
		}

		static Vector3<T> crossProduct(const Vector3<T>& v1, const Vector3<T>& v2) {
			Vector3<T> c;
			c[0] = v1[1] * v2[2] - v1[2] * v2[1];
			c[1] = v1[2] * v2[0] - v1[0] * v2[2];
			c[2] = v1[0] * v2[1] - v1[1] * v2[0];

			return c;
		}

		~Vector3() {};

	private:

	};

}