#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "player.h"
//------------------------------------
#include "NinLog.h"
#include "json.h"

void Init();

void Uninit();

void Update();

void Draw();

extern "C" int nnMain()
{
    //------------------------------------
    JsonFile d;
    LoadJsonFile(&d, "rom:/test.json");

    NN_LOG("the chinese string: %s\n", d["string1"].GetString());
    NN_LOG("the japanese string: %s\n", d["string2"].GetString());
    NN_LOG("the int type value: %d\n", d["int1"].GetInt());
    NN_LOG("the float type value: %f\n", d["float1"].GetFloat());
    NN_LOG("the bool type value: %s\n",
        d["bool1"].GetBool() ? "true" : "false");
    NN_LOG("the null value: %s\n",
        d["null1"].IsNull() ? "null" : "not null");
    for (int i = 0; i < d["array1"].Size(); i++)
    {
        NN_LOG("array value in index %d is %d\n",
            i, d["array1"][i].GetInt());
    }
    //------------------------------------

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

    InitController();

    InitBG();
    InitPlayer();
}


void Uninit()
{
    UninitBG();
    UninitPlayer();

    UninitController();
    UninitSystem();
}


void Update()
{
    UpdateController();

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
