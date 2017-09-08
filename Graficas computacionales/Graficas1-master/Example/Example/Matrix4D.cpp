// Matrix4D.cpp : Defines the entry point for the console application.
//
//C:\Users\Usuario\Documents\Visual Studio 2015\Projects\Graficas computacionales\Graficas1-master\Example\Example\Matrix4D.cpp

#include <memory>
#include <math.h>
#include "Cmatrix4D.h"

Cmatrix4D::Cmatrix4D()
{
	for (int i = 0; i < 16; i++)
		v[i] = 0;
	m00 = 1;
	m11 = 1;
	m22 = 1;
	m33 = 1;
}
Cmatrix4D::~Cmatrix4D()
{
}
Cmatrix4D::Cmatrix4D(float *vp) {
	for (int i = 0; i < 16; i++) {
		v[i] = vp[i];
	}
}
Cmatrix4D Zero_init()
{
	Cmatrix4D Z;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			Z.m[j][i] = 0;
		}
	}
	return Z;
}
Cmatrix4D operator*(Cmatrix4D& A, Cmatrix4D& B)
{
	Cmatrix4D R;
	memset(&R, 0, sizeof(R));
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.m[j][i] += A.m[j][k] * B.m[k][i];
	return R;
}
CVector4D operator*(const CVector4D & A, float f)
{
	CVector4D aux = { A.x * f,A.y * f,A.z * f,1 };
	return aux;
}
CVector4D operator*(CVector4D & V, Cmatrix4D & M)
{
	CVector4D R = { 0,0,0,0 };
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.v[j] += M.m[i][j] * V.v[i];
	return R;
}
CVector4D operator*(Cmatrix4D& M, CVector4D& V)
{
	CVector4D R;
	R.x = M.m00*V.x + M.m01*V.y + M.m02*V.z + M.m03*V.w;
	R.y = M.m10*V.x + M.m11*V.y + M.m12*V.z + M.m13*V.w;
	R.z = M.m20*V.x + M.m21*V.y + M.m22*V.z + M.m23*V.w;
	R.w = M.m30*V.x + M.m31*V.y + M.m32*V.z + M.m33*V.w;
	return R;
}
CVector4D operator*(CVector4D & A, CVector4D & B)
{
	CVector4D aux = { A.x*B.x,A.y*B.y, A.z*B.z, 1 };
	return aux;
}
CVector4D operator-(const CVector4D & cola, const CVector4D & punta) {
	CVector4D result;
	result.x = (punta.x - cola.x);
	result.y = (punta.y - cola.y);
	result.z = (punta.z - cola.z);
	return result;
}
CVector4D operator+(const CVector4D & A, const CVector4D & B)
{
	CVector4D result;
	result.x = (A.x + B.x);
	result.y = (A.y + B.y);
	result.z = (A.z + B.z);
	return result;
}
CVector4D operator/(const CVector4D & A, float B)
{
	CVector4D aux = { A.x / B,A.y / B,A.z / B,1 };
	return aux;
}
Cmatrix4D my_Identity()
{
	Cmatrix4D I;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			I.m[j][i] = (j == i) ? 1.0f : 0.0f;
	return I;
}
Cmatrix4D RotationY_RH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m00 = R.m22 = cos(theta);
	R.m20 = sin(theta);
	R.m02 = -R.m20;
	return R;
}
Cmatrix4D RotationX_RH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m11 = R.m22 = cos(theta);
	R.m21 = sin(theta);
	R.m12 = -R.m21;
	return R;
}
Cmatrix4D RotationZ_RH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m00 = R.m11 = cos(theta);
	R.m10 = sin(theta);
	R.m01 = -R.m10;
	return R;
}
Cmatrix4D RotationX_LH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m11 = R.m22 = cos(theta);
	R.m21 = -sin(theta);
	R.m12 = -R.m21;
	return R;
}
Cmatrix4D RotationY_LH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m00 = R.m22 = cos(theta);
	R.m20 = -sin(theta);
	R.m02 = -R.m20;
	return R;
}
Cmatrix4D RotationZ_LH(float theta)
{
	theta = theta*0.01745;
	Cmatrix4D R = my_Identity();
	R.m00 = R.m11 = cos(theta);
	R.m10 = -sin(theta);
	R.m01 = -R.m10;
	return R;
}
Cmatrix4D Transposed(Cmatrix4D& M)
{
	Cmatrix4D T;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			T.m[j][i] = M.m[i][j];
		}
	}
	return T;

}
Cmatrix4D Fast_Inverse(Cmatrix4D & M)
{
	Cmatrix4D R;
	CVector4D InvPos;
	R = Transposed(R);
	InvPos = R.vec[3];
	R.m03 = -Dot(R.vec[0], InvPos);
	R.m13 = -Dot(R.vec[1], InvPos);
	R.m23 = -Dot(R.vec[2], InvPos);
	R.vec[3].x = 0;
	R.vec[3].y = 0;
	R.vec[3].z = 0;
	return R;
}

float Inverse(Cmatrix4D & M, Cmatrix4D & R)
{
	Cmatrix4D I;
	double inv[16], det;
	int i;

	inv[0] = M.v[5] * M.v[10] * M.v[15] -
		M.v[5] * M.v[11] * M.v[14] -
		M.v[9] * M.v[6] * M.v[15] +
		M.v[9] * M.v[7] * M.v[14] +
		M.v[13] * M.v[6] * M.v[11] -
		M.v[13] * M.v[7] * M.v[10];

	inv[4] = -M.v[4] * M.v[10] * M.v[15] +
		M.v[4] * M.v[11] * M.v[14] +
		M.v[8] * M.v[6] * M.v[15] -
		M.v[8] * M.v[7] * M.v[14] -
		M.v[12] * M.v[6] * M.v[11] +
		M.v[12] * M.v[7] * M.v[10];

	inv[8] = M.v[4] * M.v[9] * M.v[15] -
		M.v[4] * M.v[11] * M.v[13] -
		M.v[8] * M.v[5] * M.v[15] +
		M.v[8] * M.v[7] * M.v[13] +
		M.v[12] * M.v[5] * M.v[11] -
		M.v[12] * M.v[7] * M.v[9];

	inv[12] = -M.v[4] * M.v[9] * M.v[14] +
		M.v[4] * M.v[10] * M.v[13] +
		M.v[8] * M.v[5] * M.v[14] -
		M.v[8] * M.v[6] * M.v[13] -
		M.v[12] * M.v[5] * M.v[10] +
		M.v[12] * M.v[6] * M.v[9];

	inv[1] = -M.v[1] * M.v[10] * M.v[15] +
		M.v[1] * M.v[11] * M.v[14] +
		M.v[9] * M.v[2] * M.v[15] -
		M.v[9] * M.v[3] * M.v[14] -
		M.v[13] * M.v[2] * M.v[11] +
		M.v[13] * M.v[3] * M.v[10];

	inv[5] = M.v[0] * M.v[10] * M.v[15] -
		M.v[0] * M.v[11] * M.v[14] -
		M.v[8] * M.v[2] * M.v[15] +
		M.v[8] * M.v[3] * M.v[14] +
		M.v[12] * M.v[2] * M.v[11] -
		M.v[12] * M.v[3] * M.v[10];

	inv[9] = -M.v[0] * M.v[9] * M.v[15] +
		M.v[0] * M.v[11] * M.v[13] +
		M.v[8] * M.v[1] * M.v[15] -
		M.v[8] * M.v[3] * M.v[13] -
		M.v[12] * M.v[1] * M.v[11] +
		M.v[12] * M.v[3] * M.v[9];

	inv[13] = M.v[0] * M.v[9] * M.v[14] -
		M.v[0] * M.v[10] * M.v[13] -
		M.v[8] * M.v[1] * M.v[14] +
		M.v[8] * M.v[2] * M.v[13] +
		M.v[12] * M.v[1] * M.v[10] -
		M.v[12] * M.v[2] * M.v[9];

	inv[2] = M.v[1] * M.v[6] * M.v[15] -
		M.v[1] * M.v[7] * M.v[14] -
		M.v[5] * M.v[2] * M.v[15] +
		M.v[5] * M.v[3] * M.v[14] +
		M.v[13] * M.v[2] * M.v[7] -
		M.v[13] * M.v[3] * M.v[6];

	inv[6] = -M.v[0] * M.v[6] * M.v[15] +
		M.v[0] * M.v[7] * M.v[14] +
		M.v[4] * M.v[2] * M.v[15] -
		M.v[4] * M.v[3] * M.v[14] -
		M.v[12] * M.v[2] * M.v[7] +
		M.v[12] * M.v[3] * M.v[6];

	inv[10] = M.v[0] * M.v[5] * M.v[15] -
		M.v[0] * M.v[7] * M.v[13] -
		M.v[4] * M.v[1] * M.v[15] +
		M.v[4] * M.v[3] * M.v[13] +
		M.v[12] * M.v[1] * M.v[7] -
		M.v[12] * M.v[3] * M.v[5];

	inv[14] = -M.v[0] * M.v[5] * M.v[14] +
		M.v[0] * M.v[6] * M.v[13] +
		M.v[4] * M.v[1] * M.v[14] -
		M.v[4] * M.v[2] * M.v[13] -
		M.v[12] * M.v[1] * M.v[6] +
		M.v[12] * M.v[2] * M.v[5];

	inv[3] = -M.v[1] * M.v[6] * M.v[11] +
		M.v[1] * M.v[7] * M.v[10] +
		M.v[5] * M.v[2] * M.v[11] -
		M.v[5] * M.v[3] * M.v[10] -
		M.v[9] * M.v[2] * M.v[7] +
		M.v[9] * M.v[3] * M.v[6];

	inv[7] = M.v[0] * M.v[6] * M.v[11] -
		M.v[0] * M.v[7] * M.v[10] -
		M.v[4] * M.v[2] * M.v[11] +
		M.v[4] * M.v[3] * M.v[10] +
		M.v[8] * M.v[2] * M.v[7] -
		M.v[8] * M.v[3] * M.v[6];

	inv[11] = -M.v[0] * M.v[5] * M.v[11] +
		M.v[0] * M.v[7] * M.v[9] +
		M.v[4] * M.v[1] * M.v[11] -
		M.v[4] * M.v[3] * M.v[9] -
		M.v[8] * M.v[1] * M.v[7] +
		M.v[8] * M.v[3] * M.v[5];

	inv[15] = M.v[0] * M.v[5] * M.v[10] -
		M.v[0] * M.v[6] * M.v[9] -
		M.v[4] * M.v[1] * M.v[10] +
		M.v[4] * M.v[2] * M.v[9] +
		M.v[8] * M.v[1] * M.v[6] -
		M.v[8] * M.v[2] * M.v[5];

	det = M.v[0] * inv[0] + M.v[1] * inv[4] + M.v[2] * inv[8] + M.v[3] * inv[12];

	if (fabs(det) < 0.0001)
		return 0.0f;

	double invdet = 1.0 / det;

	for (i = 0; i < 16; i++) {
		R.v[i] = (float)(inv[i] * invdet);
	}
	return (float)det;
}
Cmatrix4D Scaling(float sx, float sy, float sz)
{
	Cmatrix4D R = my_Identity();
	R.m00 = sx; R.m11 = sy; R.m22 = sz;
	return R;
}
Cmatrix4D Translation_RH(float dx, float dy, float dz)
{
	Cmatrix4D R = my_Identity();
	R.m03 = dx; R.m13 = dy; R.m23 = dz;
	return R;
}
Cmatrix4D Translation_LH(float dx, float dy, float dz)
{
	Cmatrix4D T = my_Identity();
	T.m30 = dx;
	T.m31 = dy;
	T.m32 = dz;
	return T;
}
float Dot(const CVector4D& A, CVector4D& B)
{
	return A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
}
float Mag(const CVector4D& A)
{
	return sqrt((((A.x)*(A.x)) + ((A.y)*(A.y)) + ((A.z)*(A.z))));
}
CVector4D Cross3(const CVector4D & a, const CVector4D & b)
{
	CVector4D aux = { a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x,0 };
	return aux;
}
CVector4D Normalize(const CVector4D & A)
{
	return A / Mag(A);
}
Cmatrix4D _LookAt_RH(CVector4D & EyePos, CVector4D & Target, CVector4D & Up)
{
	CVector4D xDir, yDir, zDir;
	zDir = Normalize(EyePos - Target);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);
	Cmatrix4D View;
	for (int i = 0; i < 16; i++) {
		View.v[i] = 0;
	}
	/*
	Cmatrix4D View = ( xDir.x,				yDir.x,				zDir.x,		 0,
		               xDir.y,				yDir.y,				zDir.y,		 0,
		               xDir.z,				yDir.z,				zDir.z,		 0,
		              -Dot(xDir,EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 );
	*/
	View.m00 = xDir.x;
	View.m01 = yDir.x;
	View.m02 = zDir.x;

	View.m10 = xDir.y;
	View.m11 = yDir.y;
	View.m12 = zDir.y;

	View.m20 = xDir.z;
	View.m21 = yDir.z;
	View.m22 = zDir.z;

	View.m30 = -Dot(xDir, EyePos);
	View.m31 = -Dot(yDir, EyePos);
	View.m32 = -Dot(zDir, EyePos);
	View.m33 = 1;
	return View;
}

Cmatrix4D _LookAt_LH(CVector4D & EyePos, CVector4D & Target, CVector4D & Up)
{
	CVector4D xDir, yDir, zDir;
	zDir = Normalize(Target - EyePos);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);
	Cmatrix4D View;
	for (int i = 0; i < 16; i++) {
		View.v[i] = 0;
	}
	/*Cmatrix4D View = ( xDir.x,			yDir.x,				zDir.x,		   0,
		                 xDir.y,			yDir.y,				zDir.y,		   0,
		                 xDir.z,			yDir.z,				zDir.z,		   0,
		                -Dot(xDir,EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 );
	*/
	View.m00 = xDir.x;
	View.m01 = yDir.x;
	View.m02 = zDir.x;

	View.m10 = xDir.y;
	View.m11 = yDir.y;
	View.m12 = zDir.y;

	View.m20 = xDir.z;
	View.m21 = yDir.z;
	View.m22 = zDir.z;

	View.m30 = -Dot(xDir, EyePos);
	View.m31 = -Dot(yDir, EyePos);
	View.m32 = -Dot(zDir, EyePos);
	View.m33 = 1;

	return View;
}
Cmatrix4D PerspectiveFOVRH(float FOVY, float ratio, float zNear, float zFar)
{
	float ang = FOVY / 2;

	//float h = 1 / tan(ang);
	//float w = h*ratio;

	float h = cos(ang) / sin(ang);
	float w = h / ratio;

	Cmatrix4D P;

	/*
	Cmatrix4D P = { w,	0,	 0,	  0,
		            0,	h,	 0,	  0,
		            0,	0,  zFar / (zNear - zFar),   -1,
		            0,	0,	zNear*zFar / (zNear - zFar), 0 };
	*/

	for (int i = 0; i < 16; i++) {
		P.v[i] = 0.0f;
	}

	P.m00 = w;
	P.m11 = h;
	P.m22 = zFar / (zNear - zFar);
	P.m23 = -1;
	P.m32 = zNear*zFar / (zNear - zFar);

	return P;
}

Cmatrix4D PerspectiveFOVLH(float FOVY, float ratio, float zNear, float zFar)
{
	float ang = FOVY / 2;
	//float h = 1 / tan(ang);
	//float w = h*ratio;

	float h = cos(ang) / sin(ang);
	float w = h / ratio;

	Cmatrix4D P;
	/*
	Cmatrix4D P = { w,	0,	 0,	  0,
					0,	h,	 0,   0,
					0,	0,		zFar / (zFar - zNear),		1,
					0,	0,	-zNear*zFar / (zFar - zNear),	0 };
	*/
	for (int i = 0; i < 16; i++) {
		P.v[i] = 0.0f;
	}
	P.m00 = w;
	P.m11 = h;
	P.m22 = zFar / (zFar - zNear);
	P.m23 = 1;
	P.m32 = -zNear*zFar / (zFar - zNear);
	return P;
}
CVector4D BuildPlane(CVector4D vertex0, CVector4D vertex1)
{
	CVector4D A, B, C, result;
	A = vertex0 + vertex1;
	A.x = (float)A.x / 2.0f;
	A.y = (float)A.y / 2.0f;
	A.z = 1; A.w = 1;
	B = A - vertex0;
	C = vertex1 - vertex0;
	A = Cross3(C, B);
	result = A;
	result.w = -Dot(A, vertex0);
	return result;
}
