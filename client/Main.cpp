#include "framework.h"
#include "client.h"

HINSTANCE hInst;
HWND g_hWnd;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//new
int count = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //new
    // 타이머를 이용해서 자동 그려지기 :: 30프레임
    SetTimer(g_hWnd, 1234, 1000 / 30, nullptr);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //new
        // 타이머 삭제
        count++;
        if (count > 1000)
        {
            KillTimer(g_hWnd, 1234);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    ...
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    ...
}

#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

POINT g_ptLT;
POINT g_ptRB;

bool bLbtnDown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        ...
    }
    break;
    case WM_PAINT:
    {
        ...
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            //old
            /*for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                g_vecInfo[i].g_ptObjPos.y -= 10;
            }*/
            break;
        case VK_DOWN:
            //old
            /*for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                g_vecInfo[i].g_ptObjPos.y += 10;
            }*/
            break;
        case VK_LEFT:
            //old
            /*for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                g_vecInfo[i].g_ptObjPos.x -= 10;
            }*/
            break;
        case VK_RIGHT:
            //old
            /*for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                g_vecInfo[i].g_ptObjPos.x += 10;
            }*/
            break;
        }
        //old
        /*InvalidateRect(hWnd, nullptr, true);*/
    }
    break;
    case WM_LBUTTONDOWN:
    {
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
    }
    break;
    case WM_MOUSEMOVE:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        //old
        //InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;
        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);

        bLbtnDown = false;
        //old
        //InvalidateRect(hWnd, nullptr, true);
    }
    break;
    //new
    case WM_TIMER:
    {
        wchar_t szBuff[50] = {};
        swprintf_s(szBuff, L"10초 동안 카운트 : %d", count);
        SetWindowText(hWnd, szBuff);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
