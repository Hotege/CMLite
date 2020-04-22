#pragma once

#include <Windows.h>

#if defined(_WINDLL)
#define CMLIB_API __declspec(dllexport)
#else
#define CMLIB_API __declspec(dllimport)
#endif

class CMLIB_API CWndBase
{
public:
	CWndBase();
	virtual ~CWndBase();

	inline HWND GetHWND();
	virtual inline size_t GetClassPtrHash() const = 0;
	virtual TCHAR *GetClassPtrWndClass() const;

	BOOL UpdateWindow();
	BOOL ShowWindow(int nCmdShow);

	VOID Run();
protected:
	static const unsigned int CLASS_SIZE = 32;
	static const unsigned int TITLE_SIZE = 256;
	static TCHAR m_pClass[CLASS_SIZE];

	HWND m_hWnd;
	TCHAR m_pTitle[TITLE_SIZE];

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
