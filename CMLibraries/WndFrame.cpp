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
		CW_USEDEFAULT, CW_USEDEFAULT, FRAME_DEFAULT_WIDTH, FRAME_DEFAULT_HEIGHT, nullptr, nullptr, ::GetModuleHandle(nullptr), this);
}


CWndFrame::~CWndFrame()
{
}


size_t CWndFrame::GetClassPtrHash() const
{
	return typeid(this).hash_code();
}


MESSAGE_MAP_BEGIN(CWndFrame)
	MSG_CALL(WM_DESTROY, OnDestroy)
MESSAGE_MAP_END()


MSG_IMPL(CWndFrame, OnDestroy)
{
	PostQuitMessage(0);
	return 0;
}
