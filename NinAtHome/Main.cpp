#include "main.h"
#include "texture.h"

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

    unsigned int tex1 = LoadTexture("rom\\cat.png");
    unsigned int tex2 = LoadTexture("rom\\sadcat.TGA");

    while (true)
    {
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            //--------------------
            SetTexture(tex1);

            VERTEX_3D vertex[4];

            vertex[0].Position = MakeFloat3(+100.0f, -200.0f, 0.0f);
            vertex[1].Position = MakeFloat3(-100.0f, -200.0f, 0.0f);
            vertex[2].Position = MakeFloat3(+100.0f, +0.0f, 0.0f);
            vertex[3].Position = MakeFloat3(-100.0f, +0.0f, 0.0f);

            vertex[0].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[1].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[2].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[3].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);

            vertex[0].TexCoord = MakeFloat2(1.0f, 0.0f);
            vertex[1].TexCoord = MakeFloat2(0.0f, 0.0f);
            vertex[2].TexCoord = MakeFloat2(1.0f, 1.0f);
            vertex[3].TexCoord = MakeFloat2(0.0f, 1.0f);

#ifdef RUN_WITHOUT_NINSDK
            VERTEX* v = new VERTEX[ARRAYSIZE(vertex)];
            for (int i = 0; i < ARRAYSIZE(vertex); i++)
            {
                v[i].Position = vertex[i].Position;
                v[i].Color = vertex[i].Color;
                v[i].TexCoord = vertex[i].TexCoord;
            }
            SetVertexAttr(v, ARRAYSIZE(vertex));
            delete[] v;
#else
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);
#endif // RUN_WITHOUT_NINSDK

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            //--------------------
        }
        
        {
            //--------------------
            SetTexture(tex2);

            VERTEX_3D vertex[4];

            vertex[0].Position = MakeFloat3(-200.0f, -200.0f, 0.0f);
            vertex[1].Position = MakeFloat3(-400.0f, -200.0f, 0.0f);
            vertex[2].Position = MakeFloat3(-200.0f, +0.0f, 0.0f);
            vertex[3].Position = MakeFloat3(-400.0f, +0.0f, 0.0f);

            vertex[0].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[1].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[2].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);
            vertex[3].Color = MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f);

            vertex[0].TexCoord = MakeFloat2(1.0f, 0.0f);
            vertex[1].TexCoord = MakeFloat2(0.0f, 0.0f);
            vertex[2].TexCoord = MakeFloat2(1.0f, 1.0f);
            vertex[3].TexCoord = MakeFloat2(0.0f, 1.0f);

#ifdef RUN_WITHOUT_NINSDK
            VERTEX* v = new VERTEX[ARRAYSIZE(vertex)];
            for (int i = 0; i < ARRAYSIZE(vertex); i++)
            {
                v[i].Position = vertex[i].Position;
                v[i].Color = vertex[i].Color;
                v[i].TexCoord = vertex[i].TexCoord;
            }
            SetVertexAttr(v, ARRAYSIZE(vertex));
            delete[] v;
#else
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);
#endif // RUN_WITHOUT_NINSDK

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            //--------------------
        }

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
