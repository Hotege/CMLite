#pragma once

#include "WndBase.h"
#include "WndSysMenu.h"

class CMLIB_API CWndFrame : public CWndBase
{
public:
	CWndFrame();
	virtual ~CWndFrame();

	virtual inline size_t GetClassPtrHash() const;
protected:
	static const unsigned int FRAME_DEFAULT_WIDTH = 800;
	static const unsigned int FRAME_DEFAULT_HEIGHT = 600;
	static const int FRAME_BORDER_SIZE = 8;

	CWndSysMenu *m_pSysMenu = nullptr;

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	MSG_DECL(OnDestroy);
	MSG_DECL(OnMouseMove);
	MSG_DECL(OnLButtonDown);
	MSG_DECL(OnSize);
};
