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

COLORREF color = RGB(230, 90, 0);				// ������ɫΪ��ɫ
unsigned long times1 = 0;                       //����ʱ������涨����ʱ��
unsigned long times2 = 0;
unsigned long times = 0;                        // ��Ϸ����ʱ��
HFONT Font;
HDC hdc;

int health = 4;
// �����������
int score = 0;									// ��ҵ÷�


char c;											// ���������ĸ
WCHAR str[64];									// ����ַ�����ʹ����չ���ַ��洢��ʽ���������ڹ��ʻ����ִ洢��
char hit;										// ��ǰ�û��İ�����ĸ

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
	c = rand() % 52;			   // �������һ���µ�Сд��������ĸ
	if (c > 25)
	{
		c = c - 25 + 'a';
	}
	else
		c = c + 'A';               // �������һ���µĴ�д��������ĸ

	times = GetTickCount();        // �õ���������ʱ��ʱ�䣨���룩
	times1 = GetTickCount();

	if (health <= 0)				// ���������ľ�,������ܺ�ʱ
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

	case WM_RBUTTONDOWN:					// ����Ҽ�������Ϣ
		health = 0;                         //Ϊ������ҿ���ͨ���һ�ֱ�ӽ�����Ϸ�鿴�����ٶ�
		times = GetTickCount() - times;
		color = RGB(230, 90, 0);			// ��������ɫ�任Ϊ��ɫ(�任Ϊ��ʼ������ɫ)
		InvalidateRect(hWnd, NULL, TRUE);	// �����ػ���Ϣ
		break;

	case WM_KEYDOWN:						// ���̰�����Ϣ
		hit = wParam;						// �õ���ǰ�û��İ���
		if (health <= 0)	// ���������ľ�,�򲻴��������Ϣ
		{
			break;
			times = GetTickCount() - times;
		}
		times1 = GetTickCount() - times2;
		times2 = GetTickCount();                    //���ù涨ʱ����,������time2����Ϊ��һ������ʱ��ʱ��,�γ�ѭ��

		if (hit == c || hit == c + -32)						// �������ȷ�İ���
		{

			if (times1 <= 2000)                //�������ʱ��С������
			{
				srand((unsigned)time(NULL));//i�������Ʋ�������ĸ�Ǵ�д����Сд
				c = rand() % 52;			// �������һ���µĴ�������ĸ
				if (c > 25)
				{
					c = c - 25 + 'a';		// �������һ���µĴ�������ĸ
					score = score + 1;
					color = RGB(0, 150, 50);// ������ɫΪ��ɫ
				}
				else
				{
					c = c + 'A';
					score = score + 1;				// �÷ּ�1
					color = RGB(0, 0, 255);// ������ɫΪ��ɫ
				}

			}
			else
			{

				TextOut(hdc, 5, 100, L"��ʱ�������룬������һ", 11);
				color = RGB(255, 0, 0);
				health = health - 1;


				Sleep(300);
				if (health > 0)
				{
					srand((unsigned)time(NULL));//i�������Ʋ�������ĸ�Ǵ�д����Сд

					c = rand() % 52;			// �������һ���µĴ�������ĸ
					if (c > 25)
					{
						c = c - 25 + 'a';		// �������һ���µĴ�������ĸ
						score = score + 1;
						color = RGB(0, 150, 50);// ������ɫΪ��ɫ
					}
					else
					{
						c = c + 'A';
						score = score + 1;				// �÷ּ�1
						color = RGB(0, 0, 255);// ������ɫΪ��ɫ
					}
				}
				else
				{
					times = GetTickCount() - times;   //����Ϊ0,��Ϸ����,��ʾ�����ٶ�
				}
			}
		}
		else								// ����,����������
		{
			color = RGB(255, 0, 0);           //��ɺ�ɫ��ʾ�������
			health = health - 1;

			if (health > 0)
			{
				srand((unsigned)time(NULL));//i�������Ʋ�������ĸ�Ǵ�д����Сд
				c = rand() % 52;			// �������һ���µĴ�������ĸ
				if (c > 25)
				{
					c = c - 25 + 'a';		// �������һ���µĴ�������ĸ
					score = score + 1;
				}
				else
				{
					c = c + 'A';
					score = score + 1;				// �÷ּ�1
				}
			}

			else			// ���������ľ�,������ܺ�ʱ
				times = GetTickCount() - times;
		}
		InvalidateRect(hWnd, NULL, TRUE);	// �ػ���Ļ
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		Font = CreateFont(                            //��������
			35,                                  //�߶�
			14,                                  //���
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
			_T("����"));
		SelectObject(hdc, Font);
		TextOut;

		SetTextColor(hdc, color);			// �趨������ɫ
		TextOut(hdc, 280, 150, L"��������ȷ����ĸ!", 9);
		TextOut(hdc, 350, 500, L"����Ҽ�������Ϸ�鿴�����ٶ�!", 14);
		TextOut(hdc, 350, 590, L"��ɫΪ��д��ĸ����ɫΪСд��ĸ", 15);

		swprintf_s(str, L"��������%d", health);	// �����������Ϣ��ʽ���洢���ַ�����
		TextOut(hdc, 600, 150, str, wcslen(str));	// �����Ϸ��Ϣ

		swprintf_s(str, L"�÷֣�%d", score);	// �����������Ϣ��ʽ���洢���ַ�����
		TextOut(hdc, 900, 150, str, wcslen(str));	// �����Ϸ��Ϣ


		if (health <= 0)					// ��Ϸ������Ϣ
		{
			swprintf_s(str, L"��Ϸ����,�����ٶ�: %.2f ��ÿ��", float(score * 1000) / times);
		}

		else
			swprintf_s(str, L"%c", c);		// ��ǰ��������ַ�
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