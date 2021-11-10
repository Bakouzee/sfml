#pragma once
#include <iostream>
#include "2D.h"


std::string Vector2::ToString()
{
	return "{" + std::to_string(static_cast<double>(x)) + ", " + std::to_string(static_cast<double>(y)) + "}";
}


bool Vector2::IsZero()
{
	return x == 0.0 && y == 0.0;
}

// Operators
#pragma region Operators
#pragma region Addition / Soustraction

Vector2 Vector2::operator+(Vector2 vec)
{
	return { x + vec.x, y + vec.y };
}
Vector2 Vector2::operator+=(Vector2 vec)
{
	*this = *this + vec;
	return *this;
}

Vector2 Vector2::operator-(Vector2 vec)
{
	return { x - vec.x, y - vec.y };
}

Vector2 Vector2::operator-=(Vector2 vec)
{
	*this = *this - vec;
	return *this;
}
#pragma endregion

#pragma region Mulitplication
Vector2 Vector2::operator*(float multiplier)
{
	return { x * multiplier, y * multiplier };
}

Vector2 Vector2::operator*=(float multiplier)
{
	*this = *this * multiplier;
	return *this;
}

Vector2 Vector2::operator*(Vector2 vec)
{
	return { x * vec.x, y * vec.y };
}

Vector2 Vector2::operator*=(Vector2 vec)
{
	*this = *this * vec;
	return *this;
}
#pragma endregion

#pragma region Division
Vector2 Vector2::operator/(float divider)
{
	*this = *this * (1/divider);
	return *this;
}

Vector2 Vector2::operator/=(float divider)
{
	*this = *this / divider;
	return *this;
}

Vector2 Vector2::operator/(Vector2 vec)
{
	return { x / vec.x, y / vec.y };
}

Vector2 Vector2::operator/=(Vector2 vec)
{
	*this = *this / vec;
	return *this;
}
#pragma endregion

::Vector2& Vector2::operator=(Vector2 vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2 vec)
{
	os << "{ " << static_cast<double>(vec.x) << ", " << static_cast<double>(vec.y) << " }";
	return os;
}
#pragma endregion

// Constructors
#pragma region Constructors
Vector2::Vector2() { x = 0; y = 0; }
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
#pragma endregion

// Casts from/to sf::Vector2f
Vector2 Vector2::FromSFVector2f(sf::Vector2f vec2f)
{
	return { vec2f.x, vec2f.y };
}
sf::Vector2f Vector2::ToSFVector2f(Vector2 vec)
{
	return sf::Vector2f(vec.x, vec.y);
}
sf::Vector2f Vector2::ToSFVector2f()
{
	return sf::Vector2f(x, y);
}

float Vector2::GetDistance(Vector2 a, Vector2 b)
{
	return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Vector2 Vector2::Normalize()
{
	return *this / GetDistance(Vector2(0,0), *this);
}
