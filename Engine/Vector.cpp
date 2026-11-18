#include "Vector.h"
#include <math.h>

Vector::Vector() {
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
}
Vector::Vector(double dX, double dY, double dZ) {
	m_dX = dX;
	m_dY = dY;
	m_dZ = dZ;
}

double Vector::magnitude() {
	return sqrt(m_dX * m_dX + m_dY * m_dY);
}

double Vector::magnitude3d() {
	return sqrt(m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ);
}

Vector Vector::normal() {
	double mag = magnitude();
	if (mag == 0)
		return *this;
	m_dX /= mag;
	m_dY /= mag;

	return *this;
}

Vector Vector::normal3d() {
	double mag = magnitude3d();
	if (mag == 0)
		return *this;
	m_dX /= mag;
	m_dY /= mag;
	m_dZ /= mag;

	return *this;
}



Vector Vector::operator+(Vector v) {
	return Vector(m_dX + v.m_dX, 
		m_dY + v.m_dY, 
		m_dZ + v.m_dZ);
}
void Vector::operator+=(Vector v) {
	m_dX += v.m_dX;
	m_dY += v.m_dY;
	m_dZ += v.m_dZ;
}

Vector Vector::operator-(Vector v) {
	return Vector(m_dX - v.m_dX, 
		m_dY - v.m_dY, 
		m_dZ - v.m_dZ);
}
void Vector::operator-=(Vector v) {
	m_dX -= v.m_dX;
	m_dY -= v.m_dY;
	m_dZ -= v.m_dZ;
}

Vector Vector::operator*(double d) {
	return Vector(m_dX * d, 
		m_dY * d, 
		m_dZ * d);
}
void Vector::operator*=(double d) {
	m_dX *= d;
	m_dY *= d;
	m_dZ *= d;
}

Vector Vector::operator/(double d) {
	return Vector(m_dX / d, 
		m_dY / d, 
		m_dZ / d);
}
void Vector::operator/=(double d) {
	m_dX /= d;
	m_dY /= d;
	m_dZ /= d;
}

bool Vector::operator==(Vector v) {
	return m_dX == v.m_dX 
		&& m_dY == v.m_dY 
		&& m_dZ == v.m_dZ;
}

bool Vector::operator!=(Vector v) {
	return m_dX != v.m_dX 
		|| m_dY != v.m_dY 
		|| m_dZ != v.m_dZ;
}

bool Vector::same2dPos(Vector v)
{
	return m_dX == v.m_dX
		&& m_dY == v.m_dY;
}

