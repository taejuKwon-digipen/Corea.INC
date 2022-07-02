#pragma once
#include <cmath>
#include <cassert>
#include <glm/glm.hpp>

namespace coconut {
	namespace math
	{
		struct Hcoord
		{
			float x, y, z, w;
			explicit Hcoord(float X = 0, float Y = 0, float Z = 0, float W = 0);
			float& operator[](int i) { return *(&x + i); }
			float operator[](int i) const { return *(&x + i); }
			static bool near(float x, float y) { return std::abs(x - y) < 1e-5f; }
		};

		struct Point : Hcoord
		{
			explicit Point(float X = 0, float Y = 0, float Z = 0);
			Point(const Hcoord& v) : Hcoord(v) { assert(near(w, 1)); }
		};

		struct Vector : Hcoord
		{
			explicit Vector(float X = 0, float Y = 0, float Z = 0);
			Vector(const Hcoord& v) : Hcoord(v) { assert(near(w, 0)); }
		};

		struct Matrix
		{
			Hcoord row[4];
			Hcoord& operator[](int i) { return row[i]; }
			const Hcoord& operator[](int i) const { return row[i]; }
		};

		struct Affine : Matrix
		{
			Affine(void);
			Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D);
			Affine(const Matrix& M) : Matrix(M)
			{
				assert(Hcoord::near(M[3][0], 0) && Hcoord::near(M[3][1], 0) && Hcoord::near(M[3][2], 0) && Hcoord::near(M[3][3], 1));
			}
		};

		Hcoord operator+(const Hcoord& u, const Hcoord& v);
		Hcoord operator-(const Hcoord& u, const Hcoord& v);
		Hcoord operator-(const Hcoord& v);
		Hcoord operator*(float r, const Hcoord& v);
		Hcoord operator*(const Matrix& A, const Hcoord& v);
		Matrix operator*(const Matrix& A, const Matrix& B);
		float dot(const Vector& u, const Vector& v);
		float abs(const Vector& v);
		Vector normalize(const Vector& v);
		Vector cross(const Vector& u, const Vector& v);
		Affine rotate(float t, const Vector& v);
		Affine translate(const Vector& v);
		Affine scale(float r);
		Affine scale(float rx, float ry, float rz);
		Affine inverse(const Affine& A);

		class TransformMatrix
		{
		public:
			TransformMatrix();

			const double* operator[](int index) const { return matrix[index]; }
			TransformMatrix operator* (TransformMatrix rhs) const;
			TransformMatrix& operator*= (TransformMatrix rhs);
			glm::vec2 operator* (glm::vec2 rhs) const;
			void Reset();

		protected:
			double matrix[3][3];
		};

		class TranslateMatrix : public TransformMatrix
		{
		public:
			TranslateMatrix(glm::ivec2 translate);
			TranslateMatrix(glm::vec2 translate);
		};

		class RotateMatrix : public TransformMatrix
		{
		public:
			RotateMatrix(double radians);
		};

		class ScaleMatrix : public TransformMatrix
		{
		public: ScaleMatrix(glm::vec2 scale);
		};
	}
}