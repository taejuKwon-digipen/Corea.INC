#include "../Header/MatrixOperator.h"
#include <vector>

using namespace coconut;
using namespace math;

Affine::Affine()
{
	row[0][0] = 1; row[0][1] = 0; row[0][2] = 0; row[0][3] = 0;
	row[1][0] = 0; row[1][1] = 1; row[1][2] = 0; row[1][3] = 0;
	row[2][0] = 0; row[2][1] = 0; row[2][2] = 1; row[2][3] = 0;
	row[3][0] = 0; row[3][1] = 0; row[3][2] = 0; row[3][3] = 1;
}

Affine::Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D)
{
	row[0][0] = Lx.x;
	row[1][0] = Lx.y;
	row[2][0] = Lx.z;
	row[3][0] = Lx.w;

	row[0][1] = Ly.x;
	row[1][1] = Ly.y;
	row[2][1] = Ly.z;
	row[3][1] = Ly.w;

	row[0][2] = Lz.x;
	row[1][2] = Lz.y;
	row[2][2] = Lz.z;
	row[3][2] = Lz.w;

	row[0][3] = D.x;
	row[1][3] = D.y;
	row[2][3] = D.z;
	row[3][3] = D.w;
}

Hcoord operator+(const Hcoord& u, const Hcoord& v)
{
	return Hcoord((u.x + v.x), (u.y + v.y), (u.z + v.z), (u.w + v.w));
}

Hcoord operator-(const Hcoord& u, const Hcoord& v)
{
	return Hcoord((u.x - v.x), (u.y - v.y), (u.z - v.z), (u.w - v.w));
}

Hcoord operator-(const Hcoord& v)
{
	return Hcoord(-v.x, -v.y, -v.z, -v.w);
}

Hcoord operator*(float r, const Hcoord& v)
{
	return Hcoord(r * v.x, r * v.y, r * v.z, r * v.w);
}

Hcoord operator*(const Matrix& A, const Hcoord& v)
{
	float c1 = ((A.row[0].x * v.x) + (A.row[0].y * v.y) + (A.row[0].z * v.z) + (A.row[0].w * v.w));
	float c2 = ((A.row[1].x * v.x) + (A.row[1].y * v.y) + (A.row[1].z * v.z) + (A.row[1].w * v.w));
	float c3 = ((A.row[2].x * v.x) + (A.row[2].y * v.y) + (A.row[2].z * v.z) + (A.row[2].w * v.w));
	float c4 = ((A.row[3].x * v.x) + (A.row[3].y * v.y) + (A.row[3].z * v.z) + (A.row[3].w * v.w));
	return Hcoord(c1, c2, c3, c4);
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
	float c11 = ((A.row[0].x * B.row[0].x) + (A.row[0].y * B.row[1].x) + (A.row[0].z * B.row[2].x) + (A.row[0].w * B.row[3].x));
	float c21 = ((A.row[0].x * B.row[0].y) + (A.row[0].y * B.row[1].y) + (A.row[0].z * B.row[2].y) + (A.row[0].w * B.row[3].y));
	float c31 = ((A.row[0].x * B.row[0].z) + (A.row[0].y * B.row[1].z) + (A.row[0].z * B.row[2].z) + (A.row[0].w * B.row[3].z));
	float c41 = ((A.row[0].x * B.row[0].w) + (A.row[0].y * B.row[1].w) + (A.row[0].z * B.row[2].w) + (A.row[0].w * B.row[3].w));

	float c12 = ((A.row[1].x * B.row[0].x) + (A.row[1].y * B.row[1].x) + (A.row[1].z * B.row[2].x) + (A.row[1].w * B.row[3].x));
	float c22 = ((A.row[1].x * B.row[0].y) + (A.row[1].y * B.row[1].y) + (A.row[1].z * B.row[2].y) + (A.row[1].w * B.row[3].y));
	float c32 = ((A.row[1].x * B.row[0].z) + (A.row[1].y * B.row[1].z) + (A.row[1].z * B.row[2].z) + (A.row[1].w * B.row[3].z));
	float c42 = ((A.row[1].x * B.row[0].w) + (A.row[1].y * B.row[1].w) + (A.row[1].z * B.row[2].w) + (A.row[1].w * B.row[3].w));

	float c13 = ((A.row[2].x * B.row[0].x) + (A.row[2].y * B.row[1].x) + (A.row[2].z * B.row[2].x) + (A.row[2].w * B.row[3].x));
	float c23 = ((A.row[2].x * B.row[0].y) + (A.row[2].y * B.row[1].y) + (A.row[2].z * B.row[2].y) + (A.row[2].w * B.row[3].y));
	float c33 = ((A.row[2].x * B.row[0].z) + (A.row[2].y * B.row[1].z) + (A.row[2].z * B.row[2].z) + (A.row[2].w * B.row[3].z));
	float c43 = ((A.row[2].x * B.row[0].w) + (A.row[2].y * B.row[1].w) + (A.row[2].z * B.row[2].w) + (A.row[2].w * B.row[3].w));

	float c14 = ((A.row[3].x * B.row[0].x) + (A.row[3].y * B.row[2].x) + (A.row[3].z * B.row[2].x) + (A.row[3].w * B.row[3].x));
	float c24 = ((A.row[3].x * B.row[0].y) + (A.row[3].y * B.row[2].y) + (A.row[3].z * B.row[2].y) + (A.row[3].w * B.row[3].y));
	float c34 = ((A.row[3].x * B.row[0].z) + (A.row[3].y * B.row[2].z) + (A.row[3].z * B.row[2].z) + (A.row[3].w * B.row[3].z));
	float c44 = ((A.row[3].x * B.row[0].w) + (A.row[3].y * B.row[2].w) + (A.row[3].z * B.row[2].w) + (A.row[3].w * B.row[3].w));

	return Matrix{ Hcoord(c11,c21,c31,c41), Hcoord(c12,c22,c32,c42),
		Hcoord(c13,c23,c33,c43), Hcoord(c14,c24,c34,c44) };
}

float dot(const Vector& u, const Vector& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w));
}

float math::abs(const Vector& v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

Vector normalize(const Vector& v)
{
	return Vector(v.x / math::abs(v), v.y / math::abs(v), v.z / math::abs(v));
}

Vector cross(const Vector& u, const Vector& v)
{
	float x = (u.y * v.z) - (u.z * v.y);
	//float y = ((u.z * v.x) - (u.x * v.z));
	float y = -((u.x * v.z) - (u.z * v.x));
	float z = (u.x * v.y) - (u.y * v.x);
	return Vector(x, y, z);
}
/////////////////////////////////////

Matrix operator+(Matrix& u, Matrix& v)
{
	Matrix mat;
	mat[0][0] = u.row[0].x + v.row[0].x; mat[0][1] = u.row[0].y + v.row[0].y; mat[0][2] = u.row[0].z + v.row[0].z; mat[0][3] = u.row[0].w + v.row[0].w;
	mat[1][0] = u.row[1].x + v.row[1].x; mat[1][1] = u.row[1].y + v.row[1].y; mat[1][2] = u.row[1].z + v.row[1].z; mat[1][3] = u.row[1].w + v.row[1].w;
	mat[2][0] = u.row[2].x + v.row[2].x; mat[2][1] = u.row[2].y + v.row[2].y; mat[2][2] = u.row[2].z + v.row[2].z; mat[2][3] = u.row[2].w + v.row[2].w;
	mat[3][0] = u.row[3].x + v.row[3].x; mat[3][1] = u.row[3].y + v.row[3].y; mat[3][2] = u.row[3].z + v.row[3].z; mat[3][3] = 1;
	return mat;
}

//Matrix operator-(Matrix& u, Matrix& v)
//{
//	Matrix mat;
//	mat[0][0] = u.row[0].x - v.row[0].x; mat[0][1] = u.row[0].y - v.row[0].y; mat[0][2] = u.row[0].z - v.row[0].z; mat[0][3] = 0;
//	mat[1][0] = u.row[1].x - v.row[1].x; mat[1][1] = u.row[1].y - v.row[1].y; mat[1][2] = u.row[1].z - v.row[1].z; mat[1][3] = 0;
//	mat[2][0] = u.row[2].x - v.row[2].x; mat[2][1] = u.row[2].y - v.row[2].y; mat[2][2] = u.row[2].z - v.row[2].z; mat[2][3] = 0;
//	mat[3][0] = u.row[3].x - v.row[3].x; mat[3][1] = u.row[3].y - v.row[3].y; mat[3][2] = u.row[3].z - v.row[3].z; mat[3][3] = 1;
//	return mat;
//}
//////////////////////////////////////

Affine rotate(float t, const Vector& v) 
{
	Affine mat; //outer product matrix -> u * uT
	mat[0][0] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.x * v.x; mat[0][1] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.x * v.y; mat[0][2] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.x * v.z; mat[0][3] = 0;
	mat[1][0] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.y * v.x; mat[1][1] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.y * v.y; mat[1][2] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.y * v.z; mat[1][3] = 0;
	mat[2][0] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.z * v.x; mat[2][1] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.z * v.y; mat[2][2] = (1.f - cos(t)) / (math::abs(v) * math::abs(v)) * v.z * v.z; mat[2][3] = 0;
	mat[3][0] = 0;											   mat[3][1] = 0;											   mat[3][2] = 0;											   mat[3][3] = 1;

	Affine CP; //cross product matrix -> Au
	CP[0][0] = 0;										  CP[0][1] = (sin(t) / math::abs(v)) * -v.z; CP[0][2] = (sin(t) / math::abs(v)) * v.y;	CP[0][3] = 0;
	CP[1][0] = (sin(t) / math::abs(v)) * v.z;					  CP[1][1] = 0;						   CP[1][2] = (sin(t) / math::abs(v)) * -v.x;	CP[1][3] = 0;
	CP[2][0] = (sin(t) / math::abs(v)) * -v.y;				  CP[2][1] = (sin(t) / math::abs(v)) * v.x;  CP[2][2] = 0;						CP[2][3] = 0;
	CP[3][0] = 0;										  CP[3][1] = 0;						   CP[3][2] = 0;						CP[3][3] = 1;

	Affine I;
	I[0][0] = cos(t) * 1; I[0][1] = 0;			I[0][2] = 0;			I[0][3] = 0;
	I[1][0] = 0;		  I[1][1] = cos(t) * 1; I[1][2] = 0;			I[1][3] = 0;
	I[2][0] = 0;		  I[2][1] = 0;		    I[2][2] = cos(t) * 1;	I[2][3] = 0;
	I[3][0] = 0;		  I[3][1] = 0;			I[3][2] = 0;			I[3][3] = 1;

	Affine result1 = Affine(mat + CP);
	return Affine(result1 + I);
}

Affine translate(const Vector& v)
{
	Affine mat;
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = v.x;
	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = v.y;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = v.z;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;

	return Affine(mat);
}

Affine scale(float r)
{
	Affine mat;
	mat[0][0] = r; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
	mat[1][0] = 0; mat[1][1] = r; mat[1][2] = 0; mat[1][3] = 0;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = r; mat[2][3] = 0;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;

	return Affine(mat);
}

Affine scale(float rx, float ry, float rz)
{
	Affine mat;
	mat[0][0] = rx; mat[0][1] = 0;  mat[0][2] = 0;  mat[0][3] = 0;
	mat[1][0] = 0;  mat[1][1] = ry; mat[1][2] = 0;  mat[1][3] = 0;
	mat[2][0] = 0;  mat[2][1] = 0;  mat[2][2] = rz; mat[2][3] = 0;
	mat[3][0] = 0;	mat[3][1] = 0;	mat[3][2] = 0;	mat[3][3] = 1;

	return Affine(mat);
}

//Affine inverse(const Affine& A)
//{
//	Affine m;
//	m[0][0] = A[1][1] * A[2][2] - (A[2][1] * A[1][2]);
//	m[0][1] = A[1][0] * A[2][2] - (A[2][0] * A[1][2]);
//	m[0][2] = A[1][0] * A[2][1] - (A[2][0] * A[1][1]);
//	m[1][0] = A[0][1] * A[2][2] - (A[2][1] * A[0][2]);
//	m[1][1] = A[0][0] * A[2][2] - (A[0][2] * A[2][0]);
//	m[1][2] = A[0][0] * A[2][1] - (A[0][1] * A[2][0]);
//	m[2][0] = A[0][1] * A[1][2] - (A[0][2] * A[1][1]);
//	m[2][1] = A[0][0] * A[1][2] - (A[0][1] * A[0][2]);
//	m[2][2] = A[0][0] * A[1][1] - (A[0][1] * A[1][0]);
//
//	Vector v;
//	v[0] = -A[0][3];
//	v[1] = -A[1][3];
//	v[2] = -A[2][3];
//
//	Affine c;
//	c[0][0] = m[0][0];  c[0][1] = -m[0][1]; c[0][2] = m[0][2];
//	c[1][0] = -m[1][0]; c[1][1] = m[1][1];  c[1][2] = -m[1][2];
//	c[2][0] = m[2][0];  c[2][1] = -m[2][1]; c[2][2] = m[2][2];
//
//	Affine l;
//	l[0][0] = c[0][0]; l[0][1] = c[1][0]; l[0][2] = c[2][0];
//	l[1][0] = c[0][1]; l[1][1] = c[1][1]; l[1][2] = c[2][1];
//	l[2][0] = c[0][2]; l[2][1] = c[1][2]; l[2][2] = c[2][2];
//
//	Vector l1;
//	Vector c1;
//
//	l1[0] = A[0][0];
//	l1[1] = A[0][1];
//	l1[2] = A[0][2];
//
//	c1[0] = c[0][0];
//	c1[1] = c[0][1];
//	c1[2] = c[0][2];
//
//	float det = math::dot(l1, c1);
//
//	Affine afin;
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			afin[i][j] = (1 / det) * l[i][j];
//		}
//	}
//
//	Affine T = math::translate(v);
//	Affine Result = afin * T;
//
//	return (Result);
//}

Hcoord::Hcoord(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Point::Point(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	w = 1;
}

Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	w = 0;
}
