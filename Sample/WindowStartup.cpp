#include <windows.h>


#include "../ProjectA/OverlappedWindow.h"
//#include "HelloWorld.cpp"
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

namespace Sample
{
	void ExecuteSample();
}



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace Sample;


	Sample::ExecuteSample();


	return 0;
}