#pragma once
#include <math.h>

class FVector2D
{
public:
	float x = 0.f;
	float y = 0.f;

	FVector2D();
	FVector2D(float _x, float _y);
	FVector2D(const FVector2D& _v);
	FVector2D(FVector2D&& _v) noexcept;

	const FVector2D& operator=(const FVector2D& _v);
	const FVector2D& operator=(double Value);
	const FVector2D& operator=(int Value);

	FVector2D operator+(const FVector2D& _v) const;
	FVector2D operator+(double Value) const;
	FVector2D operator+(int  Value) const;

	const FVector2D& operator+=(const FVector2D& _v);
	const FVector2D& operator+=(double Value);
	const FVector2D& operator+=(int Value);

	const FVector2D& operator++();
	const FVector2D& operator++(int);

	FVector2D operator-(const FVector2D& _v) const;
	FVector2D operator-(double Value) const;
	FVector2D operator-(int Value) const;

	const FVector2D& operator-=(const FVector2D& _v);
	const FVector2D& operator-=(double Value);
	const FVector2D& operator-=(int Value);

	const FVector2D& operator--();
	const FVector2D& operator--(int);

	FVector2D operator*(const FVector2D& _v) const;
	FVector2D operator*(double Value) const;
	FVector2D operator*(int  Value) const;

	const FVector2D& operator*=(const FVector2D& _v);
	const FVector2D& operator*=(double Value);
	const FVector2D& operator*=(int Value);

	FVector2D operator/(const FVector2D& _v) const;
	FVector2D operator/(double Value) const;
	FVector2D operator/(int  Value) const;

	const FVector2D& operator/=(const FVector2D& _v);
	const FVector2D& operator/=(double Value);
	const FVector2D& operator/=(int Value);
 
	float Length() const;

	void Normalize();
	static FVector2D Normalize(const FVector2D& _v);

	float Dot(const FVector2D& _v);

	float Distance(const FVector2D& _v);
};

