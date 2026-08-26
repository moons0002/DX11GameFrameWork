#include "Matrix.h"

FMatrix::FMatrix()
	: m(DirectX::XMMatrixIdentity())
{
}

FMatrix::FMatrix(const FMatrix& _m)
	: m(_m.m)
{
}

FMatrix::FMatrix(FMatrix&& _m) noexcept
	: m(_m.m)	
{
}

FMatrix::FMatrix(const DirectX::XMMATRIX& _m)
	: m(_m)
{
}

FMatrix::FMatrix(const FVector4D _v[4])
{
	memcpy(v, _v, sizeof(FVector4D)*4);
}

const FMatrix& FMatrix::operator=(const FMatrix& _m)
{
	m = _m.m;
	return *this;
}

const FMatrix& FMatrix::operator=(const DirectX::XMMATRIX& _m)
{
	m = _m;
	return *this;
}

const FMatrix& FMatrix::operator=(const FVector4D _v[4])
{
	memcpy(v, _v, sizeof(FVector4D)*4);
	return *this;
}

FMatrix FMatrix::operator*(const FMatrix& _m) const
{
	return FMatrix(m * _m.m);
}

FMatrix FMatrix::operator*(const DirectX::XMMATRIX& _m) const
{
	return FMatrix(m * _m);
}

void FMatrix::Identity()
{
	m = DirectX::XMMatrixIdentity();
}

void FMatrix::Transpose()
{
	m = DirectX::XMMatrixTranspose(m);
}

void FMatrix::Inverse()
{
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);
	m = DirectX::XMMatrixInverse(&det, m);
}

void FMatrix::Scaling(const FVector3D& _v)
{
	m = DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
}

void FMatrix::Scaling(const FVector2D & _v)
{
	m = DirectX::XMMatrixScaling(_v.x, _v.y, 1);
}

void FMatrix::Scaling(float x,float y,float z)
{
	m = DirectX::XMMatrixScaling(x, y, z);
}

void FMatrix::Scaling(float x,float y)
{
	m = DirectX::XMMatrixScaling(x, y, 1);
}

void FMatrix::Rotation(const FVector3D & _v)
{
	float x = DirectX::XMConvertToRadians(_v.x);
	float y = DirectX::XMConvertToRadians(_v.y);
	float z = DirectX::XMConvertToRadians(_v.z);

	DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x,y,z);

	m = DirectX::XMMatrixRotationQuaternion(Quat);
}

void FMatrix::Rotation(float _x,float _y,float _z)
{
	float x = DirectX::XMConvertToRadians(_x);
	float y = DirectX::XMConvertToRadians(_y);
	float z = DirectX::XMConvertToRadians(_z);

	DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x,y,z);

	m = DirectX::XMMatrixRotationQuaternion(Quat);
}

void FMatrix::RotationX(float _x)
{
	float x = DirectX::XMConvertToRadians(_x);
		
	m = DirectX::XMMatrixRotationX(x);
}

void FMatrix::RotationY(float _y)
{
	float y = DirectX::XMConvertToRadians(_y);
		
	m = DirectX::XMMatrixRotationY(y);
}

void FMatrix::RotationZ(float _z)
{
	float z = DirectX::XMConvertToRadians(_z);
		
	m = DirectX::XMMatrixRotationZ(z);
}

void FMatrix::RotationAxis(const FVector3D & Axis,float Angle)
{
	float angle = DirectX::XMConvertToRadians(Angle);
	DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

	m =DirectX::XMMatrixRotationAxis(_Axis, angle);
}

void FMatrix::Translation(const FVector3D & _v)
{
	m = DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
}

void FMatrix::Translation(float x,float y,float z)
{
	m = DirectX::XMMatrixTranslation(x, y, z);
}

void FMatrix::Translation(const FVector2D & _v)
{
	m = DirectX::XMMatrixTranslation(_v.x, _v.y, 0);
}

void FMatrix::Translation(float x,float y)
{
	m = DirectX::XMMatrixTranslation(x, y, 0);
}
