//---------------------------------------------------------------
// File: HFCommon.h
// Proj: NinAtHome
// Info: HighFrameに対して必要なヘッダーファイル
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "main.h"

#define APP_FPS (60)
#define MAX_DELTA (float)((double)1 / (double)APP_FPS)

#define SHOW_LOADING

enum class STATUS
{
    NEED_INIT,
    ACTIVE,
    PAUSE,
    NEED_DESTORY
};

enum class OBJ_TYPE
{
    ACTOR,
    UI,
    NULLTYPE
};

enum class COMP_TYPE
{
    ATRANSFORM,
    ATIMER,
    ASPRITE,
    ACOLLISION,
    AINPUT,
    AANIMATE,
    AINTERUPDATE,
    UTRANSFORM,
    UINPUT,
    UTEXT,
    USPRITE,
    UCHECK,
    UBTNMAP,
    NULLTYPE
};

using ActorInputProcessFuncType = void(*)(
    class AInputComponent*, float);

using ActorInterInitFuncType = void(*)(
    class AInteractionComponent*);
using ActorInterUpdateFuncType = void(*)(
    class AInteractionComponent*, float);
using ActorInterDestoryFuncType = void(*)(
    class AInteractionComponent*);

using UiInputProcessFuncType = void(*)(
    class UInputComponent*, float);

using UiInterInitFuncType = void(*)(
    class UInteractionComponent*);
using UiInterUpdateFuncType = void(*)(
    class UInteractionComponent*, float);
using UiInterDestoryFuncType = void(*)(
    class UInteractionComponent*);

#define FUNC_NAME(funcName) #funcName
