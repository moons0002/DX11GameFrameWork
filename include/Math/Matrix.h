#pragma once

#include <memory>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

__declspec(align(16)) union FMatrix
{
	DirectX::XMMATRIX m;

	struct
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};

	FVector4D v[4];

	FMatrix();
	FMatrix(const FMatrix& _m);
	FMatrix(FMatrix&& _m) noexcept;
	FMatrix(const DirectX::XMMATRIX& _m);
	FMatrix(const FVector4D _v[4]);

	const FMatrix& operator=(const FMatrix& _m);
	const FMatrix& operator=(const DirectX::XMMATRIX& _m);
	const FMatrix& operator=(const FVector4D _v[4]);

	FMatrix operator*(const FMatrix& _m) const;
	FMatrix operator*(const DirectX::XMMATRIX& _m) const;

	void Identity();

	void Transpose();

	void Inverse();

	void Scaling(const FVector3D& _v);
	void Scaling(const FVector2D& _v);
	void Scaling(float x, float y, float z);
	void Scaling(float x, float y);

	void Rotation(const FVector3D& _v);
	void Rotation(float _x, float _y, float _z);

	void RotationX(float _x);
	void RotationY(float _y);
	void RotationZ(float _z);

	void RotationAxis(const FVector3D& Axis, float Angle);

	void Translation(const FVector3D& _v);
	void Translation(float x, float y, float z);
	void Translation(const FVector2D& _v);
	void Translation(float x, float y);

	static FMatrix StaticIdentity()
	{
		return DirectX::XMMatrixIdentity(); 
	}

	static FMatrix StaticTranspose(const FMatrix& _m)
	{
		return DirectX::XMMatrixTranspose(_m.m);
	}

	static FMatrix StaticInverse(const FMatrix& _m)
	{
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(_m.m);
		return DirectX::XMMatrixInverse(&det, _m.m);
	}

	static FMatrix StaticScaling(const FVector3D& _v)
	{
		return DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
	}
	static FMatrix StaticScaling(const FVector2D& _v)
	{
		return DirectX::XMMatrixScaling(_v.x, _v.y, 1);
	}
	static FMatrix StaticScaling(float x, float y, float z)
	{
		return DirectX::XMMatrixScaling(x, y, z);
	}
	static FMatrix StaticScaling(float x, float y)
	{
		return DirectX::XMMatrixScaling(x, y, 1);
	}

	static FMatrix StaticRotation(const FVector3D& _v)
	{
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x,y,z);

		return DirectX::XMMatrixRotationQuaternion(Quat);
	}
	static FMatrix StaticRotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x,y,z);

		return DirectX::XMMatrixRotationQuaternion(Quat);
	}

	static FMatrix StaticRotationX(float _x)
	{
		float x = DirectX::XMConvertToRadians(_x);
		
		return DirectX::XMMatrixRotationX(x);
	}
	static FMatrix StaticRotationY(float _y)
	{
		float y = DirectX::XMConvertToRadians(_y);
		
		return DirectX::XMMatrixRotationY(y);
	}
	static FMatrix StaticRotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);
		
		return DirectX::XMMatrixRotationX(z);
	}

	static FMatrix StaticRotationAxis(const FVector3D& Axis, float Angle)
	{
		float angle = DirectX::XMConvertToRadians(Angle);
		DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

		return DirectX::XMMatrixRotationAxis(_Axis, angle);
	}

	static FMatrix StaticTranslation(const FVector3D& _v)
	{
		return DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
	}
	static FMatrix StaticTranslation(float x, float y, float z)
	{
		return DirectX::XMMatrixTranslation(x, y, z);
	}
	static FMatrix StaticTranslation(const FVector2D& _v)
	{
		return DirectX::XMMatrixTranslation(_v.x, _v.y, 0);
	}
	static FMatrix StaticTranslation(float x, float y)
	{
		return DirectX::XMMatrixTranslation(x, y, 0);
	}
};