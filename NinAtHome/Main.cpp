#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "player.h"

void Init();

void Uninit();

void Update();

void Draw();

extern "C" int nnMain()
{
    Init();

    while (true)
    {
        Update();
        Draw();

#ifdef RUN_WITHOUT_NINSDK
        if (ShouldQuit())
        {
            break;
        }
#endif // RUN_WITHOUT_NINSDK
    }

    Uninit();

    return 0;
}

void Init()
{
    InitSystem();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);

    //InitController();

    InitBG();
    InitPlayer();
}


void Uninit()
{
    UninitBG();
    UninitPlayer();

    //UninitController();
    UninitSystem();
}


void Update()
{
    //UpdateController();

    UpdateBG();
    UpdatePlayer();
}


void Draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawBG();
    DrawPlayer();

    SwapBuffers();
}
