#pragma once

#include "WndBase.h"

#if defined(_WINDLL)
#define CMLIB_API __declspec(dllexport)
#else
#define CMLIB_API __declspec(dllimport)
#endif

class CMLIB_API CWndFrame : public CWndBase
{
public:
	CWndFrame();
	virtual ~CWndFrame();

	virtual inline size_t GetClassPtrHash() const;
protected:
	static const unsigned int FRAME_DEFAULT_WIDTH = 320;
	static const unsigned int FRAME_DEFAULT_HEIGHT = 200;

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	MSG_DECL(OnDestroy);
};
