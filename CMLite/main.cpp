
#include "../CMLibraries/WndFrame.h"


#if defined(_DEBUG)
int main()
#else
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	CWndFrame wf;
	wf.UpdateWindow();
	wf.ShowWindow(SW_SHOW);
	wf.Run();
	return 0;
}