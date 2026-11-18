#pragma once
class Vector
{
public:
	double m_dX;
	double m_dY;
	double m_dZ;

	Vector();
	Vector(double dX, double dY, double dZ = 0);

	double magnitude();
	double magnitude3d();
	Vector normal();
	Vector normal3d();

	static Vector up()		{ return Vector(0 , 1); }
	static Vector down()	{ return Vector(0 ,-1); }
	static Vector left()	{ return Vector(-1, 0); }
	static Vector right()	{ return Vector(1 , 0); }
	static Vector zero()	{ return Vector(0 , 0); }

	Vector operator+(Vector v);
	void operator+=(Vector v);

	Vector operator-(Vector v);
	void operator-=(Vector v);

	Vector operator*(double d);
	void operator*=(double d);

	Vector operator/(double d);
	void operator/=(double d);

	bool operator==(Vector v);
	bool operator!=(Vector v);

	bool same2dPos(Vector v);
};

