#include "Vector2D.h"

FVector2D::FVector2D()
{
}

FVector2D::FVector2D(float _x,float _y)
	: x(_x), y(_y)
{
}

FVector2D::FVector2D(const FVector2D& _v)
	: x(_v.x), y(_v.y)
{
}

FVector2D::FVector2D(FVector2D&& _v) noexcept
	: x(_v.x), y(_v.y)
{
}

const FVector2D& FVector2D::operator=(const FVector2D& _v)
{
	x = _v.x;
	y = _v.y;
	return *this;
}

const FVector2D& FVector2D::operator=(double Value)
{
	x = static_cast<float>(Value);
	y = static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator=(int Value)
{
	x = static_cast<float>(Value);
	y = static_cast<float>(Value);
	return *this;
}

FVector2D FVector2D::operator+(const FVector2D& _v) const
{
	FVector2D result;
	result.x = x + _v.x;
	result.y = y + _v.y;
	return result;
}

FVector2D FVector2D::operator+(double Value) const
{
	FVector2D result;
	result.x = x + static_cast<float>(Value);
	result.y = y + static_cast<float>(Value);
	return result;
}

FVector2D FVector2D::operator+(int Value) const
{
	FVector2D result;
	result.x = x + static_cast<float>(Value);
	result.y = y + static_cast<float>(Value);
	return result;
}

const FVector2D& FVector2D::operator+=(const FVector2D& _v)
{
	x += _v.x;
	y += _v.y;
	return *this;
}

const FVector2D& FVector2D::operator+=(double Value)
{
	x += static_cast<float>(Value);
	y += static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator+=(int Value)
{
	x += static_cast<float>(Value);
	y += static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator++()
{
	x += 1.f;
	y += 1.f;
	return *this;
}

const FVector2D& FVector2D::operator++(int)
{
	x += 1.f;
	y += 1.f;
	return *this;
}

FVector2D FVector2D::operator-(const FVector2D& _v) const
{
	FVector2D result;
	result.x = x - _v.x;
	result.y = y - _v.y;
	return result;
}

FVector2D FVector2D::operator-(double Value) const
{
	FVector2D result;
	result.x = x - static_cast<float>(Value);
	result.y = y - static_cast<float>(Value);
	return result;
}

FVector2D FVector2D::operator-(int Value) const
{
	FVector2D result;
	result.x = x - static_cast<float>(Value);
	result.y = y - static_cast<float>(Value);
	return result;
}

const FVector2D& FVector2D::operator-=(const FVector2D& _v)
{
	x -= _v.x;
	y -= _v.y;
	return *this;
}

const FVector2D& FVector2D::operator-=(double Value)
{
	x -= static_cast<float>(Value);
	y -= static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator-=(int Value)
{
	x -= static_cast<float>(Value);
	y -= static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator--()
{
	x -= 1.f;
	y -= 1.f;
	return *this;
}

const FVector2D& FVector2D::operator--(int)
{
	x -= 1.f;
	y -= 1.f;
	return *this;
}

FVector2D FVector2D::operator*(const FVector2D& _v) const
{
	FVector2D result;
	result.x = x * _v.x;
	result.y = y * _v.y;
	return result;
}

FVector2D FVector2D::operator*(double Value) const
{
	FVector2D result;
	result.x = x * static_cast<float>(Value);
	result.y = y * static_cast<float>(Value);
	return result;
}

FVector2D FVector2D::operator*(int Value) const
{
	FVector2D result;
	result.x = x * static_cast<float>(Value);
	result.y = y * static_cast<float>(Value);
	return result;
}

const FVector2D& FVector2D::operator*=(const FVector2D& _v)
{
	x *= _v.x;
	y *= _v.y;
	return *this;
}

const FVector2D& FVector2D::operator*=(double Value)
{
	x *= static_cast<float>(Value);
	y *= static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator*=(int Value)
{
	x *= static_cast<float>(Value);
	y *= static_cast<float>(Value);
	return *this;
}

FVector2D FVector2D::operator/(const FVector2D& _v) const
{
	FVector2D result;
	result.x = x / _v.x;
	result.y = y / _v.y;
	return result;
}

FVector2D FVector2D::operator/(double Value) const
{
	FVector2D result;
	result.x = x / static_cast<float>(Value);
	result.y = y / static_cast<float>(Value);
	return result;
}

FVector2D FVector2D::operator/(int Value) const
{
	FVector2D result;
	result.x = x / static_cast<float>(Value);
	result.y = y / static_cast<float>(Value);
	return result;
}

const FVector2D& FVector2D::operator/=(const FVector2D& _v)
{
	x /= _v.x;
	y /= _v.y;
	return *this;
}

const FVector2D& FVector2D::operator/=(double Value)
{
	x /= static_cast<float>(Value);
	y /= static_cast<float>(Value);
	return *this;
}

const FVector2D& FVector2D::operator/=(int Value)
{
	x /= static_cast<float>(Value);
	y /= static_cast<float>(Value);
	return *this;
}

float FVector2D::Length() const
{
	return sqrtf(x * x + y * y);
}

void FVector2D::Normalize()
{
	float size = Length();
	if (0.f == size)
	{
		return;
	}
	x /= size;
	y /= size;
}

FVector2D FVector2D::Normalize(const FVector2D& _v)
{
	FVector2D result;
	float size = _v.Length();
	if (size == 0.f)
		return result;

	result.x = _v.x / size;
	result.y = _v.y / size;

	return result;
}

float FVector2D::Dot(const FVector2D& _v)
{
	return x* _v.x + y * _v.y;
}

float FVector2D::Distance(const FVector2D & _v)
{
	FVector2D diff = *this - _v;

	return diff.Length();
}
