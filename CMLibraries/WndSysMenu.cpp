#include "WndSysMenu.h"
#include <typeinfo>


CWndSysMenu::CWndSysMenu(CWndBase *pParent)
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
	m_hWnd = ::CreateWindowEx(0, GetClassPtrWndClass(), m_pTitle, WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, SYSMENU_DEFAULT_WIDTH, SYSMENU_DEFAULT_HEIGHT,
		pParent->GetHWND(), nullptr, ::GetModuleHandle(nullptr), this);
	m_pParent = pParent;
}


CWndSysMenu::~CWndSysMenu()
{
}


size_t CWndSysMenu::GetClassPtrHash() const
{
	return typeid(this).hash_code();
}


MESSAGE_MAP_BEGIN(CWndSysMenu)
	MSG_CALL(WM_PAINT, OnPaint)
	MSG_CALL(WM_LBUTTONDOWN, OnLButtonDown);
MESSAGE_MAP_END()


MSG_IMPL(CWndSysMenu, OnPaint)
{
	RECT rt;
	GetClientRect(m_hWnd, &rt);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	FillRect(hdc, &rt, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
	EndPaint(m_hWnd, &ps);
	return 0;
}


MSG_IMPL(CWndSysMenu, OnLButtonDown)
{
	SendMessage(m_pParent->GetHWND(), WM_NCLBUTTONDOWN, HTCAPTION, 0);
	RECT rtParent;
	GetWindowRect(m_pParent->GetHWND(), &rtParent);
	if (rtParent.left < 0)
		SetWindowPos(m_pParent->GetHWND(), 0, 0, rtParent.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	if (rtParent.left + SYSMENU_DEFAULT_WIDTH > nScreenWidth)
		SetWindowPos(m_pParent->GetHWND(), 0, nScreenWidth - SYSMENU_DEFAULT_WIDTH, rtParent.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	return 0;
}
