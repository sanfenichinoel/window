#include <windows.h>
#include <stdio.h>
#include <conio.h>

// 设置窗口大小
void SetWindowSize(int lines, int cols)
{
    system("title sss");
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
    system(cmd);


    int scrWidth,scrHeight;
    //获得屏幕尺寸
    scrWidth = GetSystemMetrics(SM_CXSCREEN);
    scrHeight = GetSystemMetrics(SM_CYSCREEN);
    //取得窗口尺寸
    HWND hwnd = GetForegroundWindow();
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int sizelr = rect.right - rect.left;
    int sizetb = rect.bottom - rect.top;
    //重新设置rect里的值
    rect.left = (scrWidth - sizelr) / 2;
    rect.top = (scrHeight - sizetb) / 2;

    //移动窗口到指定的位置
    SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, sizelr, sizetb, SWP_SHOWWINDOW);
}

// 设置指针位置
void SetCursorPosition(const int y, const int x)
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// 设置颜色
// 0：黑，1：深蓝，2：绿，3：浅蓝，4：红
// 5：紫，6：黄，7：白，8：灰，9：蓝，10：绿
// 11：天蓝，12：浅红，13：浅紫，14：浅黄，15：亮白
void SetColor(int colorID)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

// 这个键是否被点击（按下到松开） key是虚拟键码
bool IsPressThisKey(int key)
{
    return GetAsyncKeyState(key)&0x8000;
}

// 将鼠标卡在原处， esc键退出
void SteadyMouse()
{
    POINT o;
    GetCursorPos(&o);
    while(1){
        if(_kbhit()){
            char x = getch();
            if(x == 0x1b){
                break;
            }
        }
        SetCursorPos(o.x, o.y);
    }
}
