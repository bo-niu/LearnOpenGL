#pragma once
#include "MatrixX.h"

namespace Bo {

	template<typename T>
	class Matrix4 : public MatrixX<T, 4>
	{
	public:
		Matrix4() : MatrixX<T, 4>() {
			this->_mat[0][0] = 1; this->_mat[0][1] = 0; this->_mat[0][2] = 0; this->_mat[0][3] = 0;
			this->_mat[1][0] = 0; this->_mat[1][1] = 1; this->_mat[1][2] = 0; this->_mat[1][3] = 0;
			this->_mat[2][0] = 0; this->_mat[2][1] = 0; this->_mat[2][2] = 1; this->_mat[2][3] = 0;
			this->_mat[3][0] = 0; this->_mat[3][1] = 0; this->_mat[3][2] = 0; this->_mat[3][3] = 1;
		};
		~Matrix4() {};

		Matrix4(const Matrix<T>& m) : MatrixX<T, 4>() {};

		static Matrix4<T> rotateX(T roll) {
			Matrix4<T> m;
			T c = cos(roll);
			T s = sin(roll);
			m << 1, 0, 0, 0,
				0, c, -s, 0,
				0, s, c, 0,
				0, 0, 0, 1;

			return m;
		}

		static Matrix4<T> rotateY(T pitch) {
			Matrix4<T> m;
			T c = cos(pitch);
			T s = sin(pitch);
			m << c, 0, s, 0,
				0, 1, 0, 0,
				-s, 0, c, 0,
				0, 0, 0, 1;

			return m;
		}

		static Matrix4<T> rotateZ(T yaw) {
			Matrix4<T> m;
			T c = cos(yaw);
			T s = sin(yaw);
			m << c, -s, 0, 0,
				s, c, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1;

			return m;
		}

		//Reference: https://en.wikipedia.org/wiki/Rotation_matrix
		static Matrix4<T> rotate(T roll, T pitch, T yaw) {

			//Reference: https://stackoverflow.com/questions/22880493/no-suitable-user-defined-conversion
			return rotateZ(yaw) * rotateY(pitch) * rotateX(roll);
		}

		static Matrix4<T> translate(T x, T y, T z) {
			Matrix4<T> m;
			m << 1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1;
			return m;
		}

		static Matrix4<T> scale(T sx, T sy, T sz) {
			Matrix4<T> m;
			m << sx, 0, 0, 0,
				0, sy, 0, 0,
				0, 0, sz, 0,
				0, 0, 0, 1;
			return m;
		}

		static Matrix4<T> scale(T x) {
			Matrix4<T> m;
			m << x, 0, 0, 0,
				0, x, 0, 0,
				0, 0, x, 0,
				0, 0, 0, 1;
			return m;
		}




	};


}