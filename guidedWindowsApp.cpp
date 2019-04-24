// guidedWindowsApp.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include "framework.h"
#include "guidedWindowsApp.h"
#include "resource.h"
#include <cstring>
#include <string>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
LPSTR command1 = new CHAR[100];
LPSTR command2 = new CHAR[100];
LPSTR command3 = new CHAR[100];
LPSTR command4 = new CHAR[100];

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GUIDEDWINDOWSAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUIDEDWINDOWSAPP));
	//DialogBox(NULL, MAKEINTRESOURCE(IDD_MainPageBOX), hInstance, About);

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUIDEDWINDOWSAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GUIDEDWINDOWSAPP);
//	wcex.lpszMenuName = MAKEINTRESOURCEW(IDD_MainPageBOX);
	
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, L"CKRGB", WS_OVERLAPPEDWINDOW,
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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case ID_NEW:
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

// “关于”框的消息处理程序。
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
        } else
		if (LOWORD(wParam) == IDC_Run)
		{
			LPSTR lpString = new CHAR[100];
			int n = GetDlgItemTextA(hDlg, IDC_EDIT1, lpString, 50);
			MessageBoxA(NULL, lpString, "running", 0);
			//MessageBox(hDlg, L"Running current script",L"Running",0);
			//char nc = n;
			//std::string test1 = std::to_string(n);
			//MessageBoxA(NULL, test1.c_str(), "testx", MB_OK);
		} else
		if (LOWORD(wParam) == IDC_Save_Com1)
		{
			int n = GetDlgItemTextA(hDlg, IDC_EDIT1, command1, 50);
			MessageBoxA(NULL, command1, "Command1 saved", 0);
		} else
		if (LOWORD(wParam) == IDC_Save_Com2)
		{
			int n = GetDlgItemTextA(hDlg, IDC_EDIT1, command2, 50);
			MessageBoxA(NULL, command2, "Command2 saved", 0);
		} else
		if (LOWORD(wParam) == IDC_Save_Com3)
		{
			int n = GetDlgItemTextA(hDlg, IDC_EDIT1, command3, 50);
			MessageBoxA(NULL, command3, "Command3 saved", 0);
		}
		else
		if (LOWORD(wParam) == IDC_Save_Com4)
		{
			int n = GetDlgItemTextA(hDlg, IDC_EDIT1, command4, 50);
			MessageBoxA(NULL, command4, "Command4 saved", 0);
		}
		else
		if (LOWORD(wParam) == IDC_Get_Com1)
		{
			SetDlgItemTextA(hDlg, IDC_EDIT1, command1);
		}
		else
		if (LOWORD(wParam) == IDC_Get_Com2)
		{
			SetDlgItemTextA(hDlg, IDC_EDIT1, command2);
		}
		else
		if (LOWORD(wParam) == IDC_Get_Com3)
		{
			SetDlgItemTextA(hDlg, IDC_EDIT1, command3);
		}
		else
		if (LOWORD(wParam) == IDC_Get_Com4)
		{
			SetDlgItemTextA(hDlg, IDC_EDIT1, command4);
		}
		else
		if (LOWORD(wParam) == IDC_Save_File)
		{
			//to do the third function
		}
		else
		if (LOWORD(wParam) == IDOK)
		{
			//to do the third function
		}
		
		{
        break;

		}
	
		

    }
    return (INT_PTR)FALSE;
}
