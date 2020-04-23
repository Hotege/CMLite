#include "WndFrame.h"
#include <typeinfo>


CWndFrame::CWndFrame()
{
	memset(m_pTitle, 0, sizeof(TCHAR) * TITLE_SIZE);
	::UnregisterClass(GetClassPtrWndClass(), ::GetModuleHandle(nullptr));
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW,
		WndProc, 0, 0,
		::GetModuleHandle(nullptr),
		nullptr,
		::LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)::GetStockObject(LTGRAY_BRUSH),
		nullptr,
		GetClassPtrWndClass(),
		nullptr
	};
	::RegisterClassEx(&wcex);
	m_hWnd = ::CreateWindowEx(WS_EX_APPWINDOW, GetClassPtrWndClass(), m_pTitle, WS_POPUP,
		0, 0, FRAME_DEFAULT_WIDTH, FRAME_DEFAULT_HEIGHT,
		nullptr, nullptr, ::GetModuleHandle(nullptr), this);
	m_pSysMenu = new CWndSysMenu(this);
	int cx = ::GetSystemMetrics(SM_CXSCREEN), cy = ::GetSystemMetrics(SM_CYSCREEN);
	::SetWindowPos(m_hWnd, 0, (cx - FRAME_DEFAULT_WIDTH) / 2, (cy - FRAME_DEFAULT_HEIGHT) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}


CWndFrame::~CWndFrame()
{
	delete m_pSysMenu; m_pSysMenu = nullptr;
}


size_t CWndFrame::GetClassPtrHash() const
{
	return typeid(this).hash_code();
}


MESSAGE_MAP_BEGIN(CWndFrame)
	MSG_CALL(WM_MOUSEMOVE, OnMouseMove)
	MSG_CALL(WM_LBUTTONDOWN, OnLButtonDown)
	MSG_CALL(WM_SIZE, OnSize)
	MSG_CALL(WM_DESTROY, OnDestroy)
MESSAGE_MAP_END()


MSG_IMPL(CWndFrame, OnDestroy)
{
	::PostQuitMessage(0);
	return 0;
}


MSG_IMPL(CWndFrame, OnMouseMove)
{
	POINT pt;
	::GetCursorPos(&pt);
	RECT rt;
	::GetWindowRect(m_hWnd, &rt);
	if (pt.x >= rt.right - FRAME_BORDER_SIZE)
	{
		if (pt.y >= rt.bottom - FRAME_BORDER_SIZE)
			::SetCursor(::LoadCursor(nullptr, IDC_SIZENWSE));
		else if (pt.y <= rt.top + FRAME_BORDER_SIZE)
			::SetCursor(::LoadCursor(nullptr, IDC_SIZENESW));
		else
			::SetCursor(::LoadCursor(nullptr, IDC_SIZEWE));
		return 0;
	}
	if (pt.y >= rt.bottom - FRAME_BORDER_SIZE)
	{
		::SetCursor(::LoadCursor(nullptr, IDC_SIZENS));
		return 0;
	}
	if (pt.y <= rt.top + FRAME_BORDER_SIZE)
	{
		::SetCursor(::LoadCursor(nullptr, IDC_SIZENS));
		return 0;
	}
	return 0;
}


MSG_IMPL(CWndFrame, OnLButtonDown)
{
	POINT pt;
	::GetCursorPos(&pt);
	RECT rt;
	::GetWindowRect(m_hWnd, &rt);
	if (pt.x >= rt.right - FRAME_BORDER_SIZE)
	{
		if (pt.y >= rt.bottom - FRAME_BORDER_SIZE)
		{
			::SetCursor(::LoadCursor(nullptr, IDC_SIZENWSE));
			::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, 0);
		}
		else if (pt.y <= rt.top + FRAME_BORDER_SIZE)
		{
			::SetCursor(::LoadCursor(nullptr, IDC_SIZENESW));
			::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, 0);
		}
		else
		{
			::SetCursor(::LoadCursor(nullptr, IDC_SIZEWE));
			::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTRIGHT, 0);
		}
		return 0;
	}
	if (pt.y >= rt.bottom - FRAME_BORDER_SIZE)
	{
		::SetCursor(::LoadCursor(nullptr, IDC_SIZENS));
		::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTBOTTOM, 0);
		return 0;
	}
	if (pt.y <= rt.top + FRAME_BORDER_SIZE)
	{
		::SetCursor(::LoadCursor(nullptr, IDC_SIZENS));
		::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTTOP, 0);
		return 0;
	}
	return 0;
}


MSG_IMPL(CWndFrame, OnSize)
{
	RECT rtThis, rtSysMenu;
	::GetWindowRect(m_hWnd, &rtThis);
	::GetWindowRect(m_pSysMenu->GetHWND(), &rtSysMenu);
	::SetWindowPos(m_pSysMenu->GetHWND(), 0, 0, 0, rtSysMenu.right - rtSysMenu.left, rtThis.bottom - rtThis.top, SWP_NOZORDER | SWP_NOMOVE);
	return 0;
}
