// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include "time.h"
#include "stdio.h"
#include "conio.h"
#include "graphics.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

COLORREF color = RGB(230, 90, 0);				// 文字颜色为橙色
unsigned long times1 = 0;                       //定义时间差量规定输入时间
unsigned long times2 = 0;
unsigned long times = 0;                        // 游戏运行时间
HFONT Font;
HDC hdc;

int health = 4;
// 玩家生命点数
int score = 0;									// 玩家得分


char c;											// 待输入的字母
WCHAR str[64];									// 输出字符串，使用扩展的字符存储方式，可以用于国际化文字存储中
char hit;										// 当前用户的按键字母

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	srand((unsigned)time(NULL));
	c = rand() % 52;			   // 随机生成一个新的小写待输入字母
	if (c > 25)
	{
		c = c - 25 + 'a';
	}
	else
		c = c + 'A';               // 随机生成一个新的大写待输入字母

	times = GetTickCount();        // 得到程序启动时的时间（毫秒）
	times1 = GetTickCount();

	if (health <= 0)				// 如果生命点耗尽,则计算总耗时
		times = GetTickCount() - times;

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_RBUTTONDOWN:					// 鼠标右键按下消息
		health = 0;                         //为了让玩家可以通过右击直接结束游戏查看打字速度
		times = GetTickCount() - times;
		color = RGB(230, 90, 0);			// 将字体颜色变换为橙色(变换为初始界面颜色)
		InvalidateRect(hWnd, NULL, TRUE);	// 发出重绘消息
		break;

	case WM_KEYDOWN:						// 键盘按下消息
		hit = wParam;						// 得到当前用户的按键
		if (health <= 0)	// 如果生命点耗尽,则不处理键盘消息
		{
			break;
			times = GetTickCount() - times;
		}
		times1 = GetTickCount() - times2;
		times2 = GetTickCount();                    //设置规定时间间隔,并且让time2更新为上一次输入时的时间,形成循环

		if (hit == c || hit == c + -32)						// 如果是正确的按键
		{

			if (times1 <= 2000)                //如何输入时间小于两秒
			{
				srand((unsigned)time(NULL));//i用来控制产生的字母是大写还是小写
				c = rand() % 52;			// 随机生成一个新的待输入字母
				if (c > 25)
				{
					c = c - 25 + 'a';		// 随机生成一个新的待输入字母
					score = score + 1;
					color = RGB(0, 150, 50);// 文字颜色为青色
				}
				else
				{
					c = c + 'A';
					score = score + 1;				// 得分加1
					color = RGB(0, 0, 255);// 文字颜色为蓝色
				}

			}
			else
			{

				TextOut(hdc, 5, 100, L"用时超过两秒，生命减一", 11);
				color = RGB(255, 0, 0);
				health = health - 1;


				Sleep(300);
				if (health > 0)
				{
					srand((unsigned)time(NULL));//i用来控制产生的字母是大写还是小写

					c = rand() % 52;			// 随机生成一个新的待输入字母
					if (c > 25)
					{
						c = c - 25 + 'a';		// 随机生成一个新的待输入字母
						score = score + 1;
						color = RGB(0, 150, 50);// 文字颜色为青色
					}
					else
					{
						c = c + 'A';
						score = score + 1;				// 得分加1
						color = RGB(0, 0, 255);// 文字颜色为蓝色
					}
				}
				else
				{
					times = GetTickCount() - times;   //生命为0,游戏结束,显示打字速度
				}
			}
		}
		else								// 否则,减少生命点
		{
			color = RGB(255, 0, 0);           //变成红色表示输入错误
			health = health - 1;

			if (health > 0)
			{
				srand((unsigned)time(NULL));//i用来控制产生的字母是大写还是小写
				c = rand() % 52;			// 随机生成一个新的待输入字母
				if (c > 25)
				{
					c = c - 25 + 'a';		// 随机生成一个新的待输入字母
					score = score + 1;
				}
				else
				{
					c = c + 'A';
					score = score + 1;				// 得分加1
				}
			}

			else			// 如果生命点耗尽,则计算总耗时
				times = GetTickCount() - times;
		}
		InvalidateRect(hWnd, NULL, TRUE);	// 重绘屏幕
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		Font = CreateFont(                            //设置字体
			35,                                  //高度
			14,                                  //宽度
			0,
			0,
			700,
			FALSE,
			FALSE,
			0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			_T("楷书"));
		SelectObject(hdc, Font);
		TextOut;

		SetTextColor(hdc, color);			// 设定文字颜色
		TextOut(hdc, 280, 150, L"请输入正确的字母!", 9);
		TextOut(hdc, 350, 500, L"点击右键结束游戏查看打字速度!", 14);
		TextOut(hdc, 350, 590, L"蓝色为大写字母，青色为小写字母", 15);

		swprintf_s(str, L"生命数：%d", health);	// 将待输出的信息格式化存储到字符串中
		TextOut(hdc, 600, 150, str, wcslen(str));	// 输出游戏信息

		swprintf_s(str, L"得分：%d", score);	// 将待输出的信息格式化存储到字符串中
		TextOut(hdc, 900, 150, str, wcslen(str));	// 输出游戏信息


		if (health <= 0)					// 游戏结束信息
		{
			swprintf_s(str, L"游戏结束,打字速度: %.2f 个每秒", float(score * 1000) / times);
		}

		else
			swprintf_s(str, L"%c", c);		// 当前待输入的字符
		TextOut(hdc, 650, 250, str, wcslen(str));
		EndPaint(hWnd, &ps);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}