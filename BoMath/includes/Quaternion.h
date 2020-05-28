//
// Created by Bo Niu on 4/21/2020.
// Reference:
// https://www.cprogramming.com/tutorial/3d/quaternions.html
//

#ifndef BOQUATERNION_QUATERNION_H
#define BOQUATERNION_QUATERNION_H

#define _USE_MATH_DEFINES
#include <cassert>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include "Matrix.hpp"

namespace Bo{

    template<typename T>
    class Quaternion {

    private:
        T x;
        T y;
        T z;
        T w;


    public:
        Quaternion(T x, T y, T z, T w) {
            assert(this->x || this->y || this->z || this->w);
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        // you'll need to initialize your total quaternion to the value (1,0,0,0). This represents the "initial" state of your object - no rotation.
        Quaternion() {
			x = 0;
			y = 0;
			z = 0;
			w = 1;
        }

        void normalize(){
            assert(this->x || this->y || this->z || this->w);
            T magnitude = sqrt( x * x + y * y + z * z + w * w );
            x = x / magnitude;
            y = y / magnitude;
            z = z / magnitude;
            w = w / magnitude;

        }

        Quaternion(const Quaternion<T> &q){
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
        }

        std::vector<T> getQuaternion(){
            return std::vector<T>({x, y, z, w});
        }

        void operator=(const Quaternion<T> &q) {
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
        }

        bool operator==(const Quaternion<T> &q) {
            return (fabs(x - q.x) + fabs(y - q.y)
            + fabs(y - q.y) + fabs(y - q.y)) < 0.00001;
        }

        //inline T *&operator[](const size_t &index) const {
        //    return _vec[index];
        //}

        Quaternion<T> operator*(const Quaternion<T> &q) const {

            T w2 = w * q.w - x*q.x - y*q.y - z*q.z;
            T x2 = w*q.x + x*q.w + y*q.z - z*q.y;
            T y2 = w*q.y - x*q.z + y*q.w + z*q.x;
            T z2 = w*q.z + x*q.y - y*q.x + z*q.w;

            return Quaternion(x2, y2, z2, w2);
        }

        static Quaternion<float> generateQuaternion(float x, float y, float z, float fAngle) {
            float magnitude = sqrtf( x*x + y*y + z*z );
            x = x / magnitude;
            y = y / magnitude;
            z = z / magnitude;
            float qw = cosf(fAngle / 2.0f);
            float qx = x * sinf(fAngle / 2.0f);
            float qy = y * sinf(fAngle / 2.0f);
            float qz = z * sinf(fAngle / 2.0f);
            return Quaternion<float>(qx, qy, qz, qw);
        }

        Matrix<T> toMatrix() {
            Matrix<T> m(4, 4);
            normalize();
            m[0][0] = 1 - 2 * y * y - 2 * z * z;
            m[0][1] = 2 * x * y - 2 * w * z;
            m[0][2] = 2 * x * z + 2 * w * y;
            m[0][3] = 0;

            m[1][0] = 2 * x * y + 2 * w * z;
            m[1][1] = 1 - 2 * x * x - 2 * z * z;
            m[1][2] = 2 * y * z + 2 * w * x;
            m[1][3] = 0;

            m[2][0] = 2 * x * z - 2 * w * y;
            m[2][1] = 2 * y * z - 2 * w * x;
            m[2][2] = 1 - 2 * x * x - 2 * y * y;
            m[2][3] = 0;

            m[3][0] = 0;
            m[3][1] = 0;
            m[3][2] = 0;
            m[3][3] = 1;

            return m;
        }

        ///Reference: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		static Quaternion<T> toQuaternion(T yaw, T pitch, T roll) {// yaw (Z), pitch (Y), roll (X)
		
			// Abbreviations for the various angular functions
			T cy = cos(yaw * 0.5);
			T sy = sin(yaw * 0.5);
			T cp = cos(pitch * 0.5);
			T sp = sin(pitch * 0.5);
			T cr = cos(roll * 0.5);
			T sr = sin(roll * 0.5);

			T w = cr * cp * cy + sr * sp * sy;
			T x = sr * cp * cy - cr * sp * sy;
			T y = cr * sp * cy + sr * cp * sy;
			T z = cr * cp * sy - sr * sp * cy;

			return Quaternion<T>(x, y, z, w);
		}

        ///Reference: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		static void toEulerAngles(const Quaternion<T> &q, T &roll, T &pitch, T &yaw) {

			// roll (x-axis rotation)
			double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
			double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
			roll = std::atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			double sinp = 2 * (q.w * q.y - q.z * q.x);
			if (std::abs(sinp) >= 1)
				pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
			else
				pitch = std::asin(sinp);

			// yaw (z-axis rotation)
			double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
			double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
			yaw = std::atan2(siny_cosp, cosy_cosp);

		}

		void toEulerAngles(T& roll, T& pitch, T& yaw) const {

            toEulerAngles(*this, roll, pitch, yaw);

		}

    };
}




#endif //BOQUATERNION_QUATERNION_H
