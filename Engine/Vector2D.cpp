#include "pch.h"
#include "Vector2D.h"

Vector2D Vector2D::Zero = Vector2D(0, 0);
Vector2D Vector2D::Up = Vector2D(0, -1);
Vector2D Vector2D::Left = Vector2D(-1, 0);
Vector2D Vector2D::Down = Vector2D(0, 1);
Vector2D Vector2D::Right = Vector2D(1, 0);

float Vector2D::mVectorEpsilon = 0.8f;

float Vector2D::GetMagnitude() const
{
	return sqrtf(powf(mX, 2) + powf(mY, 2));
}

Vector2D& Vector2D::Normalize()
{
	float length = this->GetMagnitude();

	this->mX = this->mX / length;
	this->mY = this->mY / length;

	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	float x = this->mX + other.mX;
	float y = this->mY + other.mY;

	return Vector2D(x, y);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	float x = this->mX - other.mX;
	float y = this->mY - other.mY;

	return Vector2D(x, y);
}

Vector2D Vector2D::operator/(float scalar)
{
	float x = this->mX / scalar;
	float y = this->mY / scalar;

	return Vector2D(x, y);
}

bool Vector2D::operator==(Vector2D& other) const
{
	return (abs(this->mX - other.mX) < mVectorEpsilon)
		&& (abs(this->mY - other.mY) < mVectorEpsilon) ? true : false;
}

bool Vector2D::operator!=(Vector2D& other) const
{
	return !(*this == other);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	this->mX += other.mX;
	this->mY += other.mY;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	this->mX -= other.mX;
	this->mY -= other.mY;

	return *this;
}

Vector2D Vector2D::operator=(Vector2D other)
{
	this->mX = other.mX;
	this->mY = other.mY;

	return *this;
}

float Vector2D::DistanceTo(Vector2D& to) const
{
	Vector2D wayVec = Vector2D(this->mX - to.mX, this->mY - to.mY);

	return wayVec.GetMagnitude();
}

float Vector2D::DotProduct(Vector2D other)
{
	return this->mX * other.mX + this->mY * other.mY;
}

Vector2D operator*(float scalar, Vector2D vector)
{
	return Vector2D(scalar * vector.GetX(), scalar * vector.GetY());
}

Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(scalar * mX, scalar * mY);
}
