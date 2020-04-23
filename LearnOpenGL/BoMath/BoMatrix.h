//
// Created by niubo on 2/29/20.
//

#ifndef BOMATRIX_BOMATRIX_H
#define BOMATRIX_BOMATRIX_H

#include "includes/Matrix.hpp"
#include "includes/Matrix4.h"
#include "includes/VectorX.h"

typedef Bo::Matrix<double> BoMatrixXd;
typedef Bo::Matrix<int> BoMatrixXi;
typedef Bo::Matrix<float> BoMatrixXf;

typedef Bo::Matrix4<float> BoMatrix4f;
typedef Bo::Matrix4<double> BoMatrix4d;
typedef Bo::Matrix4<int> BoMatrix4i;

typedef Bo::VectorX<float, 4> BoVector4f;
typedef Bo::VectorX<double, 4> BoVector4d;
typedef Bo::VectorX<int, 4> BoVector4i;



#endif //BOMATRIX_BOMATRIX_H