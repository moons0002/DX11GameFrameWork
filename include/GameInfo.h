#pragma once

#include <Windows.h>

#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <algorithm>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "Math/Matrix.h"

#define SAFE_RELEASE(a) if(a) { a->Release(); a = nullptr; }
#define SAFE_DELETE_ARRAY(a) if(a) { delete[] a; a = nullptr; }
#define SAFE_DELETE(a) if(a) { delete a; a = nullptr; }

extern TCHAR gRootPath[MAX_PATH];
extern char gRootPathMultibyte[MAX_PATH];

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

struct FTransformBufferInfo
{
	FMatrix matWorld;
	FMatrix matView;
	FMatrix matProj;
	FMatrix matWV;
	FMatrix matWVP;
};

namespace EShaderBufferType
{
	enum Type
	{
		Vertex = 0x1,
		Pixel = 0x2,
		Hull = 0x4,
		Domain = 0x8,
		Geometry = 0x10,
		Compute = 0x20,
		Graphic = Vertex | Pixel | Hull | Domain | Geometry,
		All = Vertex | Pixel | Hull | Domain | Geometry | Compute
	};
}

struct FIndexBuffer
{
	ComPtr<ID3D11Buffer> Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	std::shared_ptr<void> Data = nullptr;
};

struct FVertexBuffer
{
	ComPtr<ID3D11Buffer> Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	std::shared_ptr<void> Data = nullptr;
};

struct FVertexColor
{
	FVector3D Pos;
	FVector4D Color;

	FVertexColor()
	{
	}
	
	FVertexColor(const FVector3D& _pos, const FVector4D& _color)
		: Pos(_pos), Color(_color)
	{
	}

	FVertexColor(float x, float y, float z, float r, float g, float b, float a)
		: Pos(x, y, z), Color(r, g, b, a)
	{
	}
};

struct FVertexTexture
{
	FVector3D Pos;
	FVector2D UV;

	FVertexTexture() = default;
	FVertexTexture(float x, float y, float z, float u, float v)
		: Pos(x,y,z), UV(u,v)
	{
	}
};

// RenderState Type
namespace ERenderStateType
{
	enum Type
	{
		Blend,
		Rasterizer,
		DepthStencil
	};
}

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 768;