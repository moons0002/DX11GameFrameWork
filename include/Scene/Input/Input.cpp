#include "Input.h"
#include "../../GameManager.h"
#include "../../Device.h"

CInput::CInput() {}

CInput::~CInput()
{
	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		SAFE_RELEASE(mKeyboard);
	}
	if (mMouse)
	{
		mMouse->Unacquire();
		SAFE_RELEASE(mMouse);
	}
}

std::shared_ptr<FBindKey> CInput::AddKey(unsigned char Key)
{
	for (std::pair<std::shared_ptr<FKeyState>, std::shared_ptr<FBindKey>> key : mKeyMap)
	{
		if (key.first->Key == Key)
			return key.second;
	}
	std::shared_ptr<FKeyState> newState = std::make_shared<FKeyState>();
	newState->Key = ConvertKey(Key);

	std::shared_ptr<FBindKey> newBindKey = std::make_shared<FBindKey>();;
	newBindKey->Key = newState;

	mKeyMap.insert(std::make_pair(newState, newBindKey));

	return newBindKey;
}

bool CInput::Init()
{
	mhInst = CGameManager::GetInstance().GetWindowInstance();
	mhWnd = CGameManager::GetInstance().GetWindowHandle();
	
	if (FAILED(DirectInput8Create(mhInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, nullptr)))
		return false;

	if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
		return false;
	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;
	if(FAILED(mKeyboard->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return false;
	//if(FAILED(mKeyboard->Acquire()))
	//	return false;

	if(FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
		return false;
	if(FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
		return false;
	if(FAILED(mMouse->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return false;
	//if (FAILED(mMouse->Acquire()))
	//	return false;

	return true;
}

void CInput::Update(float Deltatime)
{
	UpdateKeyboard();
	UpdateMouse();

	UpdateInput(Deltatime);
	UpdateBind(Deltatime);
}

bool CInput::UpdateKeyboard()
{
	if (!mKeyboard)
		return false;
	
	HRESULT result = mKeyboard->GetDeviceState(256, (LPVOID) & mKeyState);
	if(FAILED(result))
	{
		if(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mKeyboard->Acquire();
		}
	}
	return true;
}

bool CInput::UpdateMouse()
{
	if (!mMouse)
		return false;
	
	HRESULT result = mMouse->GetDeviceState(sizeof(mMouseState), (LPVOID) &mMouseState);
	if(FAILED(result))
	{
		if(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mMouse->Acquire();
		}
	}
	return true;
}

void CInput::UpdateInput(float DeltaTime)
{	
	for (int i = 0; i < EMouseButtonType::End; i++)
	{
		if (mMouseState.rgbButtons[i] & 0x80)
		{
			if(!mMouseDown[i] && !mMouseHold[i])
			{
				mMouseDown[i] = true;
				mMouseHold[i] = true;
			}
			else
			{
				mMouseDown[i] = false;
			}
		}
		else if (mMouseHold[i])
		{
			mMouseDown[i] = false;
			mMouseHold[i] = false;
			mMouseUp[i] = true;
		}
		else if(mMouseUp[i])
		{
			mMouseUp[i] = false;
		}
	}

	auto iter = mKeyMap.begin();
	auto iterEnd = mKeyMap.end();
	
	for (; iter != iterEnd; ++iter)
	{
		bool KeyPush = false;
		
		switch (iter->first->Key)
		{
			case DIK_MOUSELBUTTON:
				if (mMouseState.rgbButtons[EMouseButtonType::LButton] & 0x80)
					KeyPush = true;
				break;
			case DIK_MOUSERBUTTON:
				if (mMouseState.rgbButtons[EMouseButtonType::RButton] & 0x80)
					KeyPush = true;
				break;
			case DIK_MOUSEWHEEL:
				if (mMouseState.rgbButtons[EMouseButtonType::MButton] & 0x80)
					KeyPush = true;
				break;
			default:
				if (mKeyState[iter->first->Key] & 0x80)
					KeyPush = true;
				break;
		}

		if (KeyPush)
		{
			if (!iter->first->States[EInputType::Down] && !iter->first->States[EInputType::Hold])
			{
				iter->first->States[EInputType::Down] = true;
				iter->first->States[EInputType::Hold] = true;
			}
			else
			{
				iter->first->States[EInputType::Down] = false;
			}
		}
		else if (iter->first->States[EInputType::Hold])
		{
			iter->first->States[EInputType::Down] = false;
			iter->first->States[EInputType::Hold] = false;
			iter->first->States[EInputType::Up] = true;
		}
		else if (iter->first->States[EInputType::Up])
		{
			iter->first->States[EInputType::Up] = false;
		}
	}
}

void CInput::UpdateBind(float DeltaTime)
{
	auto iter = mKeyMap.begin();
	auto iterEnd = mKeyMap.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->first->States[EInputType::Down])
		{
			for (FBindFunction func : iter->second->FunctionList[EInputType::Down])
			{
				func.Func(DeltaTime);
			}
		}

		if (iter->first->States[EInputType::Hold])
		{
			for (FBindFunction func : iter->second->FunctionList[EInputType::Hold])
			{
				func.Func(DeltaTime);
			}
		}

		if (iter->first->States[EInputType::Up])
		{
			for (FBindFunction func : iter->second->FunctionList[EInputType::Up])
			{
				func.Func(DeltaTime);
			}
		}
	}
}

unsigned char CInput::ConvertKey(unsigned char Key)
{
		switch (Key)
		{
		case VK_LBUTTON:
			return DIK_MOUSELBUTTON;
		case VK_RBUTTON:
			return DIK_MOUSERBUTTON;
		case VK_MBUTTON:
			return DIK_MOUSEWHEEL;
		case VK_BACK:
			return DIK_BACK;
		case VK_TAB:
			return DIK_TAB;
		case VK_RETURN:
			return DIK_RETURN;
		case VK_LCONTROL:
			return DIK_LCONTROL;
		case VK_RCONTROL:
			return DIK_RCONTROL;
		case VK_LMENU:
			return DIK_LALT;
		case VK_RMENU:
			return DIK_RALT;
		case VK_LSHIFT:
			return DIK_LSHIFT;
		case VK_RSHIFT:
			return DIK_RSHIFT;
		case VK_PAUSE:
			return DIK_PAUSE;
		case VK_CAPITAL:
			return DIK_CAPSLOCK;
		case VK_ESCAPE:
			return DIK_ESCAPE;
		case VK_SPACE:
			return DIK_SPACE;
		case VK_NEXT:
			return DIK_PGDN;
		case VK_PRIOR:
			return DIK_PGUP;
		case VK_END:
			return DIK_END;
		case VK_HOME:
			return DIK_HOME;
		case VK_LEFT:
			return DIK_LEFT;
		case VK_UP:
			return DIK_UP;
		case VK_RIGHT:
			return DIK_RIGHT;
		case VK_DOWN:
			return DIK_DOWN;
		case VK_PRINT:
			return DIK_SYSRQ;
		case VK_INSERT:
			return DIK_INSERT;
		case VK_DELETE:
			return DIK_DELETE;
		case VK_HELP:
			return 0;
		case '0':
			return DIK_0;
		case '1':
			return DIK_1;
		case '2':
			return DIK_2;
		case '3':
			return DIK_3;
		case '4':
			return DIK_4;
		case '5':
			return DIK_5;
		case '6':
			return DIK_6;
		case '7':
			return DIK_7;
		case '8':
			return DIK_8;
		case '9':
			return DIK_9;
		case 'A':
			return DIK_A;
		case 'B':
			return DIK_B;
		case 'C':
			return DIK_C;
		case 'D':
			return DIK_D;
		case 'E':
			return DIK_E;
		case 'F':
			return DIK_F;
		case 'G':
			return DIK_G;
		case 'H':
			return DIK_H;
		case 'I':
			return DIK_I;
		case 'J':
			return DIK_J;
		case 'K':
			return DIK_K;
		case 'L':
			return DIK_L;
		case 'M':
			return DIK_M;
		case 'N':
			return DIK_N;
		case 'O':
			return DIK_O;
		case 'P':
			return DIK_P;
		case 'Q':
			return DIK_Q;
		case 'R':
			return DIK_R;
		case 'S':
			return DIK_S;
		case 'T':
			return DIK_T;
		case 'U':
			return DIK_U;
		case 'V':
			return DIK_V;
		case 'W':
			return DIK_W;
		case 'X':
			return DIK_X;
		case 'Y':
			return DIK_Y;
		case 'Z':
			return DIK_Z;
		case VK_OEM_3:
			return DIK_GRAVE;
		case VK_OEM_MINUS:
			return DIK_MINUS;
		case VK_OEM_NEC_EQUAL:
			return DIK_EQUALS;
		case VK_OEM_4:
			return DIK_LBRACKET;
		case VK_OEM_6:
			return DIK_RBRACKET;
		case VK_OEM_5:
			return DIK_BACKSLASH;
		case VK_OEM_1:
			return DIK_SEMICOLON;
		case VK_OEM_7:
			return DIK_APOSTROPHE;
		case VK_OEM_COMMA:
			return DIK_COMMA;
		case VK_OEM_PERIOD:
			return DIK_PERIOD;
		case VK_OEM_2:
			return DIK_SLASH;
		case VK_NUMPAD0:
			return DIK_NUMPAD0;
		case VK_NUMPAD1:
			return DIK_NUMPAD1;
		case VK_NUMPAD2:
			return DIK_NUMPAD2;
		case VK_NUMPAD3:
			return DIK_NUMPAD3;
		case VK_NUMPAD4:
			return DIK_NUMPAD4;
		case VK_NUMPAD5:
			return DIK_NUMPAD5;
		case VK_NUMPAD6:
			return DIK_NUMPAD6;
		case VK_NUMPAD7:
			return DIK_NUMPAD7;
		case VK_NUMPAD8:
			return DIK_NUMPAD8;
		case VK_NUMPAD9:
			return DIK_NUMPAD9;
		case VK_MULTIPLY:
			return DIK_MULTIPLY;
		case VK_ADD:
			return DIK_ADD;
		case VK_SEPARATOR:
			return DIK_NUMPADCOMMA;
		case VK_SUBTRACT:
			return DIK_SUBTRACT;
		case VK_DECIMAL:
			return DIK_DECIMAL;
		case VK_DIVIDE:
			return DIK_DIVIDE;
			//case VK_RETURN:		
			//return DIK_NUMPADENTER;
		case VK_F1:
			return DIK_F1;
		case VK_F2:
			return DIK_F2;
		case VK_F3:
			return DIK_F3;
		case VK_F4:
			return DIK_F4;
		case VK_F5:
			return DIK_F5;
		case VK_F6:
			return DIK_F6;
		case VK_F7:
			return DIK_F7;
		case VK_F8:
			return DIK_F8;
		case VK_F9:
			return DIK_F9;
		case VK_F10:
			return DIK_F10;
		case VK_F11:
			return DIK_F11;
		case VK_F12:
			return DIK_F12;
		case VK_F13:
			return DIK_F13;
		case VK_F14:
			return DIK_F14;
		case VK_F15:
			return DIK_F15;
		case VK_F16:
		case VK_F17:
		case VK_F18:
		case VK_F19:
		case VK_F20:
		case VK_F21:
		case VK_F22:
		case VK_F23:
		case VK_F24:
			return 0;
		case VK_NUMLOCK:
			return DIK_NUMLOCK;
		case VK_SCROLL:
			return DIK_SCROLL;
		case VK_LWIN:
			return DIK_LWIN;
		case VK_RWIN:
			return DIK_RWIN;
		case VK_APPS:
			return DIK_APPS;
		case VK_OEM_102:
			return DIK_OEM_102;
		}
	return 0xff;
}
