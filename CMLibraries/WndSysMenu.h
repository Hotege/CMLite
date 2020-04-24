#pragma once

#include "WndBase.h"

class CMLIB_API CWndSysMenu : public CWndBase
{
public:
	CWndSysMenu(CWndBase *pParent);
	virtual ~CWndSysMenu();

	virtual inline size_t GetClassPtrHash() const;
protected:
	static const unsigned int SYSMENU_DEFAULT_WIDTH = 48;
	static const unsigned int SYSMENU_DEFAULT_HEIGHT = 600;
	static const int SYSMENU_BORDER_SIZE = 8;

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	MSG_DECL(OnPaint);
	MSG_DECL(OnMouseMove);
	MSG_DECL(OnLButtonDown);
	MSG_DECL(OnLButtonDbClk);
};