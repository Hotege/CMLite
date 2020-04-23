#include "WndBase.h"
#include <typeinfo>


TCHAR CWndBase::m_pClass[32];


CWndBase::CWndBase()
{
	memset(m_pTitle, 0, sizeof(TCHAR) * TITLE_SIZE);
	m_hWnd = nullptr;
}


CWndBase::~CWndBase()
{
}


HWND CWndBase::GetHWND()
{
	return m_hWnd;
}


TCHAR *CWndBase::GetClassPtrWndClass() const
{
	memset(m_pClass, 0, sizeof(TCHAR) * CLASS_SIZE);
	wsprintf(m_pClass, L"cm-obj-control-wnd-%lu", GetClassPtrHash());
	return m_pClass;
}


BOOL CWndBase::UpdateWindow()
{
	return ::UpdateWindow(m_hWnd);
}


BOOL CWndBase::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(m_hWnd, nCmdShow);
}


VOID CWndBase::Run()
{
	MSG msg;
	if (m_hWnd)
		while (::GetMessage(&msg, 0, 0, 0))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
}


LRESULT CALLBACK CWndBase::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		::CREATESTRUCT *pCS = (::CREATESTRUCT*)lParam;
		CWndBase *pWnd = (CWndBase*)pCS->lpCreateParams;
		pWnd->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
	}
	CWndBase *pWnd = (CWndBase*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (pWnd)
		return pWnd->HandleMessage(message, wParam, lParam);
	else
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	return 0;
}


MESSAGE_MAP_BEGIN(CWndBase)
MESSAGE_MAP_END()
