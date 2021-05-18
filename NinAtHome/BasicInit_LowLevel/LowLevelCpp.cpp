#include "main.h"
#include "GlProcess.h"
#include <iostream>

bool InitSystem(int width, int height, const char* title)
{
	if (!InitGlAndCreateWindow(width,height,title))
	{
		std::cout << "failed to init" << std::endl;
		return false;
	}

	return true;
}

void UninitSystem()
{
	TerminateGLFW();
}

void SwapBuffers()
{
	GoRunLoopProcess();
}

bool ShouldQuit()
{
	return ShouldGlfwQuit();
}
