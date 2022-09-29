// encoding :  GBK

#define mwindows
#include <conio.h>
#include <iostream>
#include <cstring>
#include <tchar.h>
#include <string>
#include <windows.h>
#include "cpp_get_py_output.cpp"

char iSay[105];        
int myLen;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
    cpp_get_python_output(iSay);
    myLen = strlen(iSay);

    // 设计一个窗口类
    WNDCLASSEX wcex;
    // 类名称
    wcex.lpszClassName = _T("one");
    // 窗口句柄
    wcex.hInstance = hInstance;
    // 窗口过程函数
    wcex.lpfnWndProc = WndProc;
    // 类大小
    wcex.cbSize = sizeof(WNDCLASSEX);
    // 窗口样式
    wcex.style = CS_HREDRAW | CS_VREDRAW;     
    // 类图标
    wcex.hIcon = NULL;
    wcex.hIconSm = NULL;
    // 光标设置
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    // 类背景画刷
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // 类菜单 
    wcex.lpszMenuName = NULL;
    // 附加窗口类存储空间   
    wcex.cbClsExtra = 0; 
    // 附加窗口存储空间   
    wcex.cbWndExtra = 0;
 
    // 注册这个窗口类
    if (RegisterClassEx(&wcex) == ((ATOM)0)){
        MessageBox(NULL, _T("注册窗口类失败!"), _T("错误"), MB_YESNO | MB_ICONERROR);
        exit(-1);
    }
 
    int scrWidth = GetSystemMetrics(SM_CXSCREEN);
    int scrHeight = GetSystemMetrics(SM_CYSCREEN);
    HWND hWnd = CreateWindowEx(NULL, _T("one"), _T("窗口"), WS_OVERLAPPEDWINDOW, scrWidth*3/8, scrHeight*3/8, scrWidth/4, scrHeight/4, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL){
        MessageBox(NULL, _T("创建窗口失败!"), _T("错误"), MB_YESNO | MB_ICONERROR);
        exit(-1);
    }
 
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
 
    MSG msg = {0};
    BOOL bRet;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet != -1)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC      hdc ;
    PAINTSTRUCT     ps ;
    RECT            rect ;
    static int      cxChar, cyChar;
    
    switch (message)
    {
    case WM_CREATE :       
        cxChar = LOWORD (GetDialogBaseUnits ());
        cyChar = HIWORD (GetDialogBaseUnits ());
        break;

    case WM_DESTROY:
        PostQuitMessage(0); // 程序退出
        break;

    case WM_PAINT:
        hdc = BeginPaint (hWnd, &ps);
        GetClientRect(hWnd, &rect);

        TextOutA(
            hdc,
            rect.right / 2 - cxChar * myLen / 2,
            (rect.bottom - cyChar) / 2,
            (LPCSTR)(iSay),
            myLen
        );
        EndPaint (hWnd, &ps) ;
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
