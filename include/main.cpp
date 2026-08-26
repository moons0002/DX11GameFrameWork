#include "GameInfo.h"
#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    if (!CGameManager::GetInstance().Init(hInstance)) {
        return 0;
    }
    
    CGameManager::GetInstance().Run();
}