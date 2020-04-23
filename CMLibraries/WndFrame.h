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

	CWndSysMenu *m_pSysMenu;

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	MSG_DECL(OnDestroy);
};
