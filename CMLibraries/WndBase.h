#pragma once

#include <Windows.h>

#if defined(_WINDLL)
#define CMLIB_API __declspec(dllexport)
#else
#define CMLIB_API __declspec(dllimport)
#endif

#define MSG_DECL(f) \
virtual LRESULT f(UINT message, WPARAM wParam, LPARAM lParam);

#define MSG_IMPL(control, f) \
LRESULT control::f(UINT message, WPARAM wParam, LPARAM lParam)

#define MESSAGE_MAP_BEGIN(control) \
LRESULT control::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) \
{ \
	switch (message) \
	{

#define MSG_CALL(msg, f) \
	case msg: \
		return f(message, wParam, lParam);

#define MESSAGE_MAP_END() \
	default: \
		return ::DefWindowProc(m_hWnd, message, wParam, lParam); \
	} \
	return 0; \
}

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
	MSG_DECL(OnDestroy);
};
