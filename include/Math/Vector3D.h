#pragma once

#include <math.h>
#include "EngineMath.h"
	
union FMatrix;

class FVector3D
{
public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	FVector3D();
	FVector3D(float _x, float _y, float _z);
	FVector3D(const FVector3D& _v);
	FVector3D(FVector3D&& _v) noexcept;
	FVector3D(const DirectX::XMVECTOR& v);

	const FVector3D& operator=(const FVector3D& _v);
	const FVector3D& operator=(double Value);
	const FVector3D& operator=(int Value);

	FVector3D operator+(const FVector3D& _v) const;
	FVector3D operator+(double Value) const;
	FVector3D operator+(int Value) const;

	const FVector3D& operator+=(const FVector3D& _v);
	const FVector3D& operator+=(double Value);
	const FVector3D& operator+=(int Value);

	const FVector3D& operator++();
	const FVector3D& operator++(int);

	FVector3D operator-(const FVector3D& _v) const;
	FVector3D operator-(double Value) const;
	FVector3D operator-(int Value) const;
	FVector3D operator-() const;

	const FVector3D& operator-=(const FVector3D& _v);
	const FVector3D& operator-=(double Value);
	const FVector3D& operator-=(int Value);

	const FVector3D& operator--();
	const FVector3D& operator--(int);

	FVector3D operator*(const FVector3D& _v) const;
	FVector3D operator*(double Value) const;
	FVector3D operator*(int Value) const;

	const FVector3D& operator*=(const FVector3D& _v);
	const FVector3D& operator*=(double Value);
	const FVector3D& operator*=(int Value);

	FVector3D operator/(const FVector3D& _v) const;
	FVector3D operator/(double Value) const;
	FVector3D operator/(int Value) const;

	const FVector3D& operator/=(const FVector3D& _v);
	const FVector3D& operator/=(double Value);
	const FVector3D& operator/=(int Value);

	float Length() const;

	void Normalize();
	static FVector3D Normalize(const FVector3D& _v);

	float Dot(const FVector3D& _v) const;
	FVector3D Cross(const FVector3D& _v) const;

	float Distance(const FVector3D& _v) const;

	DirectX::XMVECTOR Convert() const;

	FVector3D TransformNormal(FMatrix& mat) const;
	FVector3D TransformCoord(FMatrix& mat) const;

	FVector3D GetRotation(const FVector3D& Rot) const;

public:
	FVector3D Rotation(const FVector3D& _v);

};