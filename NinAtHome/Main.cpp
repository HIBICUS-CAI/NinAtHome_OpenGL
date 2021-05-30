#include "main.h"
#include "texture.h"
#include "sprite.h"

struct VERTEX_3D
{
    Float3 Position;
    Float4 Color;
    Float2 TexCoord;
};

extern "C" int nnMain()
{
    InitSystem();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);

    unsigned int tex1 = LoadTexture("rom:/cat.png");
    unsigned int tex2 = LoadTexture("rom:/sadcat.TGA");

    while (true)
    {
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SetTexture(tex1);
        DrawSprite(-200.f, 0.f, 100.f, 100.f,
            0.f, 0.f, 1.f, 1.f,
            MakeFloat4(1.f, 1.f, 1.f, 1.f));

        SetTexture(tex2);
        DrawSprite(200.f, 0.f, 100.f, 100.f,
            0.f, 0.f, 1.f, 1.f,
            MakeFloat4(1.f, 1.f, 1.f, 1.f));

        SwapBuffers();

#ifdef RUN_WITHOUT_NINSDK
        if (ShouldQuit())
        {
            break;
        }
#endif // RUN_WITHOUT_NINSDK

    }

    UnloadTexture(tex1);
    UnloadTexture(tex2);
    UninitSystem();


    return 0;
}
