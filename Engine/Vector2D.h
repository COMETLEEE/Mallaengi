#pragma once

/// <summary>
/// 2022. 02. 08. MG
/// Vector2D를 넣으면 가져다 쓸 때 혜성쓰 손발 여섯개씩 된다!
/// </summary>
class Vector2D
{
public:
	Vector2D() { this->mX = 0.f; this->mY = 0.f; }
	Vector2D(const Vector2D& other) { this->mX = other.mX; this->mY = other.mY; }
	Vector2D(float x, float y) { this->mX = x; this->mY = y; }
	~Vector2D() { };

public:
	float mX;		// x
	float mY;		// y

	static float mVectorEpsilon;	// 벡터의 비교 연산에 있어 오차 허용 범위

public:
	inline float GetX() const { return this->mX; }
	inline float GetY() const { return this->mY; }

	float GetMagnitude() const;			// 벡터의 크기를 구하는 함수
	Vector2D& Normalize();				// 벡터의 크기를 1로 만드는 함수

	Vector2D operator + (const Vector2D& other);
	Vector2D operator - (const Vector2D& other);
	Vector2D operator / (float scalar);
	bool operator == (Vector2D& other) const;
	bool operator != (Vector2D& other) const;
	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D operator = (Vector2D other);
	Vector2D operator * (float scalar);

	float DistanceTo(Vector2D& to) const;			// 벡터간의 거리 구하는 함수

	float DotProduct(Vector2D other);				// 벡터간의 내적

	friend Vector2D operator * (float scalar, Vector2D vector);

	// 기본 제공하는 벡터
	static Vector2D Zero;
	static Vector2D Up;
	static Vector2D Left;
	static Vector2D Down;
	static Vector2D Right;
};