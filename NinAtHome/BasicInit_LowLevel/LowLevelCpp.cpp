#include "main.h"
#include "GlProcess.h"
#include "GlHelper.h"
#include <iostream>

GlHelper* gp_GlHelper = nullptr;

bool InitSystem(int width, int height, const char* title)
{
	if (!InitGlAndCreateWindow(width,height,title))
	{
		std::cout << "failed to init basic" << std::endl;
		return false;
	}

	gp_GlHelper = new GlHelper();
	if (!gp_GlHelper->StartUp())
	{
		std::cout << "failed to init gl" << std::endl;
		delete gp_GlHelper;
		gp_GlHelper = nullptr;
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
