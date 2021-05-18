#include "main.h"

extern "C" int main()
{
    InitSystem();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);

    while (true)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SwapBuffers();

#ifdef RUN_WITHOUT_NINSDK
        if (ShouldQuit())
        {
            break;
        }
#endif // RUN_WITHOUT_NINSDK

    }

    UninitSystem();
    

    return 0;
}
