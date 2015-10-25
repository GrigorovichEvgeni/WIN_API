#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


	if (!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход

	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("Каркас  Windows приложения"),	// заголовок окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
		кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна

	// получение очередного сообщения из очереди сообщений
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);	// трансляция сообщения
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
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
			wsprintf(str, TEXT("Внутри"));
			SetWindowText(hWnd, str);
		}
		else if ((LOWORD(lParam) < 10 && HIWORD(lParam) < 10000) || (LOWORD(lParam) < 10000 && HIWORD(lParam) < 10)){
			wsprintf(str, TEXT("Снаружи"));
			SetWindowText(hWnd, str);
		} else if (LOWORD(lParam) == 10 || HIWORD(lParam) == 10){
			wsprintf(str, TEXT("Граница"));
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