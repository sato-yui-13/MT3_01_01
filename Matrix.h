#pragma once
#include <Vector3.h>
#include <math.h>
#include <time.h>
#define _USE_MATH_DEFINE
#include "Matrix4x4.h"
#include <Novice.h>
#include <Vector4.h>
#include <assert.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>


Vector3 Cross(const Vector3& v1, const Vector3& v2);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

static const int kRowHeight = 20;
static const int kColumnWidth = 60;