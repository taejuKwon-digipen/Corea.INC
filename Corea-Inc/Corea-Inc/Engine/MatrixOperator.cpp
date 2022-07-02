#include "MatrixOperator.h"
#include <vector>

#include "Sprite.h"


coconut::math::Hcoord::Hcoord(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

coconut::math::Point::Point(float X, float Y, float Z) : Hcoord{ X, Y, Z, 1 } {}

coconut::math::Vector::Vector(float X, float Y, float Z) : Hcoord{ X, Y, Z, 0 } {}

coconut::math::Affine::Affine()
{
	row[0] = Hcoord{ 1, 0, 0, 0 };
	row[1] = Hcoord{ 0, 1, 0, 0 };
	row[2] = Hcoord{ 0, 0, 1, 0 };
	row[3] = Hcoord{ 0, 0, 0, 1 };
}

coconut::math::Affine::Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D)
{
	row[0] = Hcoord{ Lx.x, Lx.y, Lx.z, Lx.w };
	row[1] = Hcoord{ Ly.x, Ly.y, Ly.z, Ly.w };
	row[2] = Hcoord{ Lz.x, Lz.y, Lz.z, Lz.w };
	row[3] = Hcoord{ D.x, D.y, D.z, D.w };
}

coconut::math::Hcoord coconut::math::operator+(const Hcoord& u, const Hcoord& v)
{
	return Hcoord{ u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w };
}

coconut::math::Hcoord coconut::math::operator-(const Hcoord& u, const Hcoord& v)
{
	return Hcoord{ u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w };
}

coconut::math::Hcoord coconut::math::operator-(const Hcoord& v)
{
	return Hcoord{ -v.x, -v.y, -v.z, -v.w };
}

coconut::math::Hcoord coconut::math::operator*(float r, const Hcoord& v)
{
	return Hcoord{ r * v.x, r * v.y, r * v.z, r * v.w };
}

coconut::math::Hcoord coconut::math::operator*(const Matrix& A, const Hcoord& v)
{
	float c1 = ((A.row[0].x * v.x) + (A.row[0].y * v.y) + (A.row[0].z * v.z) + (A.row[0].w * v.w));
	float c2 = ((A.row[1].x * v.x) + (A.row[1].y * v.y) + (A.row[1].z * v.z) + (A.row[1].w * v.w));
	float c3 = ((A.row[2].x * v.x) + (A.row[2].y * v.y) + (A.row[2].z * v.z) + (A.row[2].w * v.w));
	float c4 = ((A.row[3].x * v.x) + (A.row[3].y * v.y) + (A.row[3].z * v.z) + (A.row[3].w * v.w));
	return Hcoord(c1, c2, c3, c4);
}

coconut::math::Matrix coconut::math::operator*(const Matrix& A, const Matrix& B)
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

float coconut::math::dot(const Vector& u, const Vector& v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w);
}

float coconut::math::abs(const Vector& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

coconut::math::Vector coconut::math::normalize(const Vector& v)
{
	return Vector(v.x / abs(v), v.y / abs(v), v.z / abs(v));
}

coconut::math::Vector coconut::math::cross(const Vector& u, const Vector& v)
{
	float x = (u.y * v.z) - (u.z * v.y);
	float y = -((u.x * v.z) - (u.z * v.x));
	float z = (u.x * v.y) - (u.y * v.x);
	return Vector(x, y, z);
}

coconut::math::Affine coconut::math::rotate(float t, const Vector& v)
{
	Affine A;

	float a = cos(t);
	float b = (1 - a) / (abs(v) * abs(v));
	float c = sin(t) / abs(v);

	Matrix U;
	float XX = v.x * v.x; float XY = v.x * v.y; float XZ = v.x * v.z;
	float YY = v.y * v.y; float YZ = v.y * v.z; float ZZ = v.z * v.z;
	U[0] = Hcoord{ XX, XY, XZ, 0 };
	U[1] = Hcoord{ XY, YY, YZ, 0 };
	U[2] = Hcoord{ XZ, YZ, ZZ, 0 };
	U[3] = Hcoord{ 0, 0, 0, 1 };

	Matrix V;
	V[0] = Hcoord{ 0, -v.z, v.y, 0 };
	V[1] = Hcoord{ v.z, 0, -v.x, 0 };
	V[2] = Hcoord{ -v.y, v.x, 0, 0 };
	V[3] = Hcoord{ 0, 0, 0, 1 };

	A[0] = Hcoord{ a + b * U[0].x, b * U[0].y + c * V[0].y, b * U[0].z + c * V[0].z, 0 };
	A[1] = Hcoord{ b * U[1].x + c * V[1].x, a + b * U[1].y, b * U[1].z + c * V[1].z, 0 };
	A[2] = Hcoord{ b * U[2].x + c * V[2].x, b * U[2].y + c * V[2].y, a + b * U[2].z, 0 };
	A[3] = Hcoord{ 0, 0, 0, 1 };

	return A;
}

coconut::math::Affine coconut::math::translate(const Vector& v)
{
	Affine mat;
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = v.x;
	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = v.y;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = v.z;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;

	return Affine(mat);
}

coconut::math::Affine coconut::math::scale(float r)
{
	Affine mat;
	mat[0][0] = r; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
	mat[1][0] = 0; mat[1][1] = r; mat[1][2] = 0; mat[1][3] = 0;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = r; mat[2][3] = 0;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;

	return Affine(mat);
}

coconut::math::Affine coconut::math::scale(float rx, float ry, float rz)
{
	Affine mat;
	mat[0][0] = rx; mat[0][1] = 0;  mat[0][2] = 0;  mat[0][3] = 0;
	mat[1][0] = 0;  mat[1][1] = ry; mat[1][2] = 0;  mat[1][3] = 0;
	mat[2][0] = 0;  mat[2][1] = 0;  mat[2][2] = rz; mat[2][3] = 0;
	mat[3][0] = 0;	mat[3][1] = 0;	mat[3][2] = 0;	mat[3][3] = 1;

	return Affine(mat);
}

coconut::math::Affine coconut::math::inverse(const Affine& A)
{
	Affine m;
	m[0][0] = A[1][1] * A[2][2] - (A[2][1] * A[1][2]);
	m[0][1] = A[1][0] * A[2][2] - (A[2][0] * A[1][2]);
	m[0][2] = A[1][0] * A[2][1] - (A[2][0] * A[1][1]);
	m[1][0] = A[0][1] * A[2][2] - (A[2][1] * A[0][2]);
	m[1][1] = A[0][0] * A[2][2] - (A[0][2] * A[2][0]);
	m[1][2] = A[0][0] * A[2][1] - (A[0][1] * A[2][0]);
	m[2][0] = A[0][1] * A[1][2] - (A[0][2] * A[1][1]);
	m[2][1] = A[0][0] * A[1][2] - (A[0][1] * A[0][2]);
	m[2][2] = A[0][0] * A[1][1] - (A[0][1] * A[1][0]);

	Vector v;
	v[0] = -A[0][3];
	v[1] = -A[1][3];
	v[2] = -A[2][3];

	Affine c;
	c[0][0] = m[0][0];  c[0][1] = -m[0][1]; c[0][2] = m[0][2];
	c[1][0] = -m[1][0]; c[1][1] = m[1][1];  c[1][2] = -m[1][2];
	c[2][0] = m[2][0];  c[2][1] = -m[2][1]; c[2][2] = m[2][2];

	Affine l;
	l[0][0] = c[0][0]; l[0][1] = c[1][0]; l[0][2] = c[2][0];
	l[1][0] = c[0][1]; l[1][1] = c[1][1]; l[1][2] = c[2][1];
	l[2][0] = c[0][2]; l[2][1] = c[1][2]; l[2][2] = c[2][2];

	Vector l1;
	Vector c1;

	l1[0] = A[0][0];
	l1[1] = A[0][1];
	l1[2] = A[0][2];

	c1[0] = c[0][0];
	c1[1] = c[0][1];
	c1[2] = c[0][2];

	float det = coconut::math::dot(l1, c1);

	Affine afin;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			afin[i][j] = (1 / det) * l[i][j];
		}
	}

	Affine T = coconut::math::translate(v);
	Affine Result = afin * T;

	return (Result);
}


coconut::math::TransformMatrix::TransformMatrix()
{
	Reset();
}

void coconut::math::TransformMatrix::Reset()
{
	matrix[0][0] = 1.0;		matrix[0][1] = 0.0;		matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;		matrix[1][1] = 1.0;		matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;		matrix[2][1] = 0.0;		matrix[2][2] = 1.0;
}

coconut::math::TranslateMatrix::TranslateMatrix(glm::ivec2 translate)
{
	matrix[0][0] = 1.0;		matrix[0][1] = 0.0;		matrix[0][2] = translate.x;
	matrix[1][0] = 0.0;		matrix[1][1] = 1.0;		matrix[1][2] = translate.y;
	matrix[2][0] = 0.0;		matrix[2][1] = 0.0;		matrix[2][2] = 1.0;
}

coconut::math::TranslateMatrix::TranslateMatrix(glm::vec2 translate)
{
	matrix[0][0] = 1.0;		matrix[0][1] = 0.0;		matrix[0][2] = translate.x;
	matrix[1][0] = 0.0;		matrix[1][1] = 1.0;		matrix[1][2] = translate.y;
	matrix[2][0] = 0.0;		matrix[2][1] = 0.0;		matrix[2][2] = 1.0;
}

coconut::math::RotateMatrix::RotateMatrix(double radians)
{
	matrix[0][0] = std::cos(radians);		matrix[0][1] = -std::sin(radians);		matrix[0][2] = 0.0;
	matrix[1][0] = std::sin(radians);		matrix[1][1] = std::cos(radians);		matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;						matrix[2][1] = 0.0;						matrix[2][2] = 1.0;
}

coconut::math::ScaleMatrix::ScaleMatrix(glm::vec2 scale)
{
	matrix[0][0] = scale.x;		matrix[0][1] = 0.0;			matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;			matrix[1][1] = scale.y;		matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;			matrix[2][1] = 0.0;			matrix[2][2] = 1.0;
}

coconut::math::TransformMatrix coconut::math::TransformMatrix::operator*(TransformMatrix rhs) const
{
	TransformMatrix result;
	
	result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
	result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
	result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
	result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
	result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
	result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
	result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
	result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
	result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

	return result;
}

glm::vec2 coconut::math::TransformMatrix::operator*(glm::vec2 rhs) const
{
	glm::vec2 result;
	double rhsX = rhs.x;
	double rhsY = rhs.y;

	result.x = float(matrix[0][0] * rhsX + matrix[0][1] * rhsY + matrix[0][2] * 1);
	result.y = float(matrix[1][0] * rhsX + matrix[1][1] * rhsY + matrix[1][2] * 1);

	return result;
}

coconut::math::TransformMatrix& coconut::math::TransformMatrix::operator*=(TransformMatrix rhs)
{
	(*this) = (*this) * rhs;
	return (*this);
}