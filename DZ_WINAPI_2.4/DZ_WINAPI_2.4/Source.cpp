#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); 

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);	
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	
	wcl.lpfnWndProc = WindowProc;	
	wcl.cbClsExtra = 0;		
	wcl.cbWndExtra = 0; 	
	wcl.hInstance = hInst;	
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	


	if (!RegisterClassEx(&wcl))
		return 0;	

	
	hWnd = CreateWindowEx(
		0,		
		szClassWindow,	
		TEXT("Каркас  Windows приложения"),	
		
		WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,
		NULL,			
		NULL,			
		hInst,		
		NULL);		

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	

	
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);	
		DispatchMessage(&lpMsg);	
	}

	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[50];
	RECT rect;
	switch (uMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
			MoveWindow(hWnd, 0, 0, 300, 300, 1);

		else if (wParam == VK_LEFT){
			GetWindowRect(hWnd, &rect);
			int LEFT = rect.left - 1;
			int TOP = rect.top;
			int RIGHT = rect.right - rect.left;
			int BOTTOM = rect.bottom - rect.top;
			MoveWindow(hWnd, LEFT, TOP, RIGHT, BOTTOM, 1);
		}
		else if (wParam == VK_RIGHT){
			GetWindowRect(hWnd, &rect);
			int LEFT = rect.left + 1;
			int TOP = rect.top;
			int RIGHT = rect.right - rect.left;
			int BOTTOM = rect.bottom - rect.top;
			MoveWindow(hWnd, LEFT, TOP, RIGHT, BOTTOM, 1);
		}
		else if (wParam == VK_UP){
			GetWindowRect(hWnd, &rect);
			int LEFT = rect.left;
			int TOP = rect.top - 1;
			int RIGHT = rect.right - (rect.left);
			int BOTTOM = rect.bottom - (rect.top + 1);
			MoveWindow(hWnd, LEFT, TOP, RIGHT, BOTTOM, 1);
		}
		else if (wParam == VK_DOWN){
			GetWindowRect(hWnd, &rect);
			int LEFT = rect.left;
			int TOP = rect.top + 1;
			int RIGHT = rect.right - (rect.left);
			int BOTTOM = rect.bottom - (rect.top -1);
			MoveWindow(hWnd, LEFT, TOP, RIGHT, BOTTOM, 1);
		}
		break;
	case WM_LBUTTONDOWN:
		
		if (LOWORD(lParam)>10 && HIWORD(lParam)>10){
			wsprintf(str, TEXT("Внутри"));
			SetWindowText(hWnd, str);
		}
		else if ((LOWORD(lParam) < 10 && HIWORD(lParam) < 10000) || (LOWORD(lParam) < 10000 && HIWORD(lParam) < 10)){
			wsprintf(str, TEXT("Снаружи"));
			SetWindowText(hWnd, str);
		}
		else if (LOWORD(lParam) == 10 || HIWORD(lParam) == 10){
			wsprintf(str, TEXT("Граница"));
			SetWindowText(hWnd, str);
		}
		break;

	case WM_RBUTTONDOWN:
		GetClientRect(hWnd, &rect);
		wsprintf(str, TEXT("Ширина=%d Высота=%d"), rect.right, rect.bottom);
		SetWindowText(hWnd, str);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:

		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}