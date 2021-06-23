//---------------------------------------------------------------
// File: HFCommon.h
// Proj: NinAtHome
// Info: HighFrame�ˌ����Ʊ�Ҫ�ʥإå��`�ե�����
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "main.h"

#define APP_FPS (30)
#define MAX_DELTA (float)((double)1 / (double)APP_FPS)

//#define SHOW_LOADING

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
