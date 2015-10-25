#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������"); /* ��� ������ ���� */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// ���� ������ �������� ��������� � ������� ������ (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// �������� ������������ �������
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���������� ���� ����� ������			
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����


	if (!RegisterClassEx(&wcl))
		return 0;	// ��� ��������� ����������� - �����

	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	// ��� ������ ����
		TEXT("������  Windows ����������"),	// ��������� ����
		/* ���������, �����, ����������� ������ �������, ��������� ����,
		������ ������������ � ���������� ����  */
		WS_OVERLAPPEDWINDOW,	// ����� ����
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// ����������� ����

	// ��������� ���������� ��������� �� ������� ���������
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);	// ���������� ���������
		DispatchMessage(&lpMsg);	// ��������������� ���������
	}
	
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[50];
	RECT rect;
	switch (uMessage)
	{
	case WM_LBUTTONDOWN:
		if (LOWORD(lParam)>10 && HIWORD(lParam)>10){
			wsprintf(str, TEXT("������"));
			SetWindowText(hWnd, str);
		}
		else if ((LOWORD(lParam) < 10 && HIWORD(lParam) < 10000) || (LOWORD(lParam) < 10000 && HIWORD(lParam) < 10)){
			wsprintf(str, TEXT("�������"));
			SetWindowText(hWnd, str);
		} else if (LOWORD(lParam) == 10 || HIWORD(lParam) == 10){
			wsprintf(str, TEXT("�������"));
			SetWindowText(hWnd, str);
		}
		break;

	case WM_RBUTTONDOWN:
		GetWindowRect(hWnd, &rect);
		wsprintf(str, TEXT("Left=%d Top=%d Right=%d Bottom=%d"), rect, rect, rect, rect, rect);
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