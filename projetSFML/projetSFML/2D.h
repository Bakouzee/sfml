#pragma once
#include <string>

struct Vector2
{
public:
	float x = 0;
	float y = 0;

	// Operators
		// Plus
	Vector2 operator+(Vector2 vec);
	Vector2 operator+=(Vector2 vec);
		// Minus
	Vector2 operator-(Vector2 vec);
	Vector2 operator-=(Vector2 vec);
		// Multiply
	Vector2 operator*(float multiplier);
	Vector2 operator*=(float multiplier);
	Vector2 operator*(Vector2 vec);
	Vector2 operator*=(Vector2 vec);
		// Divide
	Vector2 operator/(float divider);
	Vector2 operator/=(float divider);
	Vector2 operator/(Vector2 vec);
	Vector2 operator/=(Vector2 vec);

		// Assign
	::Vector2& operator=(Vector2 vec);

	// Constructors
	Vector2();
	Vector2(float x, float y);

	static float GetDistance(Vector2 a, Vector2 b);
	std::string ToString();
}; 

// std::ostream.operator<< variant working with Vector2
std::ostream& operator<<(std::ostream& os, const Vector2 vec);