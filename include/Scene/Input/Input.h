#pragma once

#include "../../GameInfo.h"

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")

#define DIRECTINPUT_VERSION 0x0800

#define DIK_MOUSELBUTTON 0xfc
#define DIK_MOUSERBUTTON 0xfd
#define DIK_MOUSEWHEEL 0xfe

namespace EMouseButtonType
{
	enum Type
	{
		LButton,
		RButton,
		MButton,
		End
	};
}

namespace EInputType
{
	enum Type
	{
		Down,
		Hold,
		Up,
		End
	};
}

struct FKeyState
{
	unsigned char Key = 0;
	bool States[EInputType::End] = {false, false, false};
};

struct FBindFunction
{
	// 함수
	std::function<void(float)> Func;
};

struct FBindKey
{
	std::shared_ptr<FKeyState> Key = nullptr;
	std::vector<FBindFunction> FunctionList[EInputType::End];
};

class CInput
{
	friend class CScene;

public:
	CInput();
	~CInput();

private:
	HINSTANCE mhInst;
	HWND mhWnd;

	unsigned char mKeyState[256] = {};
	DIMOUSESTATE mMouseState = {};

	std::unordered_map<std::shared_ptr<FKeyState>, std::shared_ptr<FBindKey>> mKeyMap;
	
	bool mMouseDown[EMouseButtonType::End] = {};
	bool mMouseHold[EMouseButtonType::End] = {};
	bool mMouseUp[EMouseButtonType::End] = {};

	ComPtr<IDirectInput8> mInput = nullptr;
	ComPtr<IDirectInputDevice8> mKeyboard = nullptr;
	ComPtr<IDirectInputDevice8> mMouse = nullptr;

private:
	std::shared_ptr<FBindKey> AddKey(unsigned char Key);

public:
	bool Init();
	void Update(float Deltatime);

private:
	bool UpdateKeyboard();
	bool UpdateMouse();

	void UpdateInput(float DeltaTime);
	void UpdateBind(float DeltaTime);

public:
	template<typename T1, typename T2>
	void AddBindFunction(unsigned char Key, EInputType::Type Type,
		std::shared_ptr<T1> Object, void(T2::*Func)(float))
	{
		std::shared_ptr<FBindKey> BindKey = AddKey(Key);

		std::shared_ptr<T2> Casted = std::dynamic_pointer_cast<T2>(Object);
		std::weak_ptr<T2> WeakObj = Casted;

		FBindFunction BindFunc;

		BindFunc.Func = [WeakObj, Func] (float DeltaTime)
		{
			if (auto Obj = WeakObj.lock())
				(Obj.get()->*Func)(DeltaTime);
		};

		BindKey->FunctionList[Type].emplace_back(BindFunc);
	}

private:
	unsigned char ConvertKey(unsigned char Key);
};