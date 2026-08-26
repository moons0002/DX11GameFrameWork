#include "Vector3D.h"
#include "Matrix.h"

FVector3D::FVector3D()
{

}
FVector3D::FVector3D(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}
FVector3D::FVector3D(const FVector3D& _v)
	: x(_v.x), y(_v.y), z(_v.z)
{
}
FVector3D::FVector3D(FVector3D&& _v) noexcept
	: x(_v.x), y(_v.y), z(_v.z)
{
}
FVector3D::FVector3D(const DirectX::XMVECTOR& v)
{
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
}

const FVector3D& FVector3D::operator=(const FVector3D& _v)
{
	x = _v.x;
	y = _v.y;
	z = _v.z;
	return *this;
}

const FVector3D& FVector3D::operator=(double Value)
{
	x = static_cast<float>(Value);
	y = static_cast<float>(Value);
	z = static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator=(int Value)
{
	x = static_cast<float>(Value);
	y = static_cast<float>(Value);
	z = static_cast<float>(Value);
	return *this;
}

FVector3D FVector3D::operator+(const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x + _v.x;
	result.y = y + _v.y;
	result.z = z + _v.z;
	return result;
}

FVector3D FVector3D::operator+(double Value) const
{
	FVector3D result;
	result.x = x + static_cast<float>(Value);
	result.y = y + static_cast<float>(Value);
	result.z = z + static_cast<float>(Value);
	return result;
}

FVector3D FVector3D::operator+(int Value) const
{
	FVector3D result;
	result.x = x + static_cast<float>(Value);
	result.y = y + static_cast<float>(Value);
	result.z = z + static_cast<float>(Value);
	return result;
}

const FVector3D& FVector3D::operator+=(const FVector3D& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

const FVector3D& FVector3D::operator+=(double Value)
{
	x += static_cast<float>(Value);
	y += static_cast<float>(Value);
	z += static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator+=(int Value)
{
	x += static_cast<float>(Value);
	y += static_cast<float>(Value);
	z += static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator++()
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return *this;
}

const FVector3D& FVector3D::operator++(int)
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return *this;
}

FVector3D FVector3D::operator-(const FVector3D& _v) const
{
	FVector3D result;
	result.x = x - _v.x;
	result.y = y - _v.y;
	result.z = z - _v.z;
	return result;
}

FVector3D FVector3D::operator-(double Value) const
{
	FVector3D result;
	result.x = x - static_cast<float>(Value);
	result.y = y - static_cast<float>(Value);
	result.z = z - static_cast<float>(Value);
	return result;
}

FVector3D FVector3D::operator-(int Value) const
{
	FVector3D result;
	result.x = x - static_cast<float>(Value);
	result.y = y - static_cast<float>(Value);
	result.z = z - static_cast<float>(Value);
	return result;
}

FVector3D FVector3D::operator-() const
{
	return FVector3D(-x, -y, -z);
}

const FVector3D& FVector3D::operator-=(const FVector3D& _v)
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator-=(double Value)
{
	x -= static_cast<float>(Value);
	y -= static_cast<float>(Value);
	z -= static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator-=(int Value)
{
	x -= static_cast<float>(Value);
	y -= static_cast<float>(Value);
	z -= static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator--()
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}

const FVector3D& FVector3D::operator--(int)
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}

FVector3D FVector3D::operator*(const FVector3D& _v) const
{
	FVector3D result;
	result.x = x * _v.x;
	result.y = y * _v.y;
	result.z = z * _v.z;
	return result;
}

FVector3D FVector3D::operator*(double Value) const
{
	FVector3D result;
	result.x = x * static_cast<float>(Value);
	result.y = y * static_cast<float>(Value);
	result.z = z * static_cast<float>(Value);
	return result;
}

FVector3D FVector3D::operator*(int  Value) const
{
	FVector3D result;
	result.x = x * static_cast<float>(Value);
	result.y = y * static_cast<float>(Value);
	result.z = z * static_cast<float>(Value);
	return result;
}

const FVector3D& FVector3D::operator*=(const FVector3D& _v)
{
	x *= _v.x;
	y *= _v.y;
	z *= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator*=(double Value)
{
	x *= static_cast<float>(Value);
	y *= static_cast<float>(Value);
	z *= static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator *= (int Value)
{
	x *= static_cast<float>(Value);
	y *= static_cast<float>(Value);
	z *= static_cast<float>(Value);
	return *this;
}

FVector3D FVector3D::operator/(const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x / _v.x;
	result.y = y / _v.y;
	result.z = z / _v.z;
	return result;
}

FVector3D FVector3D::operator/(double Value) const
{
	FVector3D result;
	result.x = x / static_cast<float>(Value);
	result.y = y / static_cast<float>(Value);
	result.z = z / static_cast<float>(Value);
	return result;
}

FVector3D FVector3D::operator/(int  Value) const
{
	FVector3D result;
	result.x = x / static_cast<float>(Value);
	result.y = y / static_cast<float>(Value);
	result.z = z / static_cast<float>(Value);
	return result;
}

const FVector3D& FVector3D::operator/=(const FVector3D& _v)
{
	x /= _v.x;
	y /= _v.y;
	z /= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator/=(double Value)
{
	x /= static_cast<float>(Value);
	y /= static_cast<float>(Value);
	z /= static_cast<float>(Value);
	return *this;
}

const FVector3D& FVector3D::operator/=(int Value)
{
	x /= static_cast<float>(Value);
	y /= static_cast<float>(Value);
	z /= static_cast<float>(Value);
	return *this;
}

float FVector3D::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

void FVector3D::Normalize()
{
	float size = Length();
	if (0.f == size)
	{
		return;
	}

	x /= size;
	y /= size;
	z /= size;
}

FVector3D FVector3D::Normalize(const FVector3D & _v)
{
	FVector3D result;

	float size = _v.Length();

	if (size == 0.f)
		return result;

	result.x = _v.x / size;
	result.y = _v.y / size;
	result.z = _v.z / size;
	return result;
}

float FVector3D::Dot(const FVector3D& _v) const
{
	return x * _v.x + y * _v.y + z*_v.z;
}

FVector3D FVector3D::Cross(const FVector3D& _v) const
{
	FVector3D result;
	result.x = y * _v.z - z * _v.y;
	result.y = z * _v.x - x * _v.z;
	result.z = x * _v.y - y * _v.x;
	return result;
}

float FVector3D::Distance(const FVector3D& _v) const
{
	FVector3D diff = *this - _v;

	return diff.Length();
}

DirectX::XMVECTOR FVector3D::Convert() const
{
	return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this);
}

FVector3D FVector3D::TransformNormal(FMatrix& mat) const
{
	DirectX::XMVECTOR result = DirectX::XMVector3TransformNormal(Convert(), mat.m);
	return result;
}

FVector3D FVector3D::TransformCoord(FMatrix& mat) const
{
	DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(Convert(), mat.m);
	return result;
}

FVector3D FVector3D::GetRotation(const FVector3D& Rot) const
{
	FMatrix matRot;
	matRot.Rotation(Rot);

	return TransformNormal(matRot);
}

FVector3D FVector3D::Rotation(const FVector3D& _v)
{
	float x = DirectX::XMConvertToRadians(_v.x);
	float y = DirectX::XMConvertToRadians(_v.y);
	float z = DirectX::XMConvertToRadians(_v.z);

	FMatrix matRot = DirectX::XMMatrixRotationRollPitchYaw(x,y,z);

	return TransformCoord(matRot);
}