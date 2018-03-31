#pragma once
#include <iostream>

class Vector2D
{
public:
	float x, y;
	Vector2D();
	Vector2D(float x, float y);
	float length();
	Vector2D operator + (Vector2D &v) const;
	Vector2D operator += (Vector2D &v);
	Vector2D operator - (Vector2D &v) const;
	Vector2D operator -= (Vector2D &v);
	Vector2D operator * (int scalar) const;
	Vector2D operator *= (int scalar);
	Vector2D operator / (float scalar) const;
	Vector2D operator /= (float scalar);
	friend std::ostream &operator<<(std::ostream &stream, Vector2D &vec);
	void normalize();
	~Vector2D();
};

