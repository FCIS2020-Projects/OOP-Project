#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
}
Vector2D::Vector2D(float x, float y)
{
	this->x = x, this->y = y;
}
float Vector2D::length()
{
	return sqrt(this->x*this->x + this->y * this->y); 
}

Vector2D Vector2D::operator + (Vector2D &v) const
{
	return Vector2D(this->x + v.x, this->y + v.y);
}
Vector2D Vector2D::operator += (Vector2D &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}
Vector2D Vector2D::operator - (Vector2D &v) const
{
	return Vector2D(this->x - v.x, this->y - v.y);
}
Vector2D Vector2D::operator -= (Vector2D &v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}
Vector2D Vector2D::operator * (int n) const
{
	return Vector2D(this->x *n, this->y *n);
}
Vector2D Vector2D::operator *= (int n)
{
	this->x *= n;
	this->y *= n;
	return *this;
}
Vector2D Vector2D::operator / (float n) const
{
	return Vector2D(this->x / n, this->y / n);
}
Vector2D Vector2D::operator /= (float n)
{
	this->x /= n;
	this->y /= n;
	return *this;
}
void Vector2D::normalize()
{
	float l = length();
	if (l > 0)
	{
		*this *= 1 / l;
	}
}
std::ostream &operator<<(std::ostream &stream, Vector2D &v)
{
	stream << "(" << v.x << "," << v.y << ")";
	return stream;
}
Vector2D::~Vector2D()
{
}
