// encoding :  GBK

#include <conio.h>
#include <iostream>
#include <cstring>
#include <tchar.h>
#include <string>
#include <windows.h>
#include "cpp_get_saying_on_txt.cpp"
// #include "cpp_get_py_output.cpp"

char iSay[105];        
int myLen;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
    // �ǳ��̵Ĳ���
    WinExec("./env/dist/get_saying.exe", SW_SHOWNORMAL);
    cpp_get_saying(iSay);
    myLen = strlen(iSay);

    // ���һ��������
    WNDCLASSEX wcex;
    // ������
    wcex.lpszClassName = _T("one");
    // ���ھ��
    wcex.hInstance = hInstance;
    // ���ڹ��̺���
    wcex.lpfnWndProc = WndProc;
    // ���С
    wcex.cbSize = sizeof(WNDCLASSEX);
    // ������ʽ
    wcex.style = CS_HREDRAW | CS_VREDRAW;     
    // ��ͼ��
    wcex.hIcon = NULL;
    wcex.hIconSm = NULL;
    // �������
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    // �౳����ˢ
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // ��˵� 
    wcex.lpszMenuName = NULL;
    // ���Ӵ�����洢�ռ�   
    wcex.cbClsExtra = 0; 
    // ���Ӵ��ڴ洢�ռ�   
    wcex.cbWndExtra = 0;
 
    // ע�����������
    if (RegisterClassEx(&wcex) == ((ATOM)0)){
        MessageBox(NULL, _T("ע�ᴰ����ʧ��!"), _T("����"), MB_YESNO | MB_ICONERROR);
        exit(-1);
    }
 
    int scrWidth = GetSystemMetrics(SM_CXSCREEN);
    int scrHeight = GetSystemMetrics(SM_CYSCREEN);
    HWND hWnd = CreateWindowEx(NULL, _T("one"), _T("����"), WS_OVERLAPPEDWINDOW, scrWidth/3, scrHeight*3/8, scrWidth/3, scrHeight/4, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL){
        MessageBox(NULL, _T("��������ʧ��!"), _T("����"), MB_YESNO | MB_ICONERROR);
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
        PostQuitMessage(0); // �����˳�
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
