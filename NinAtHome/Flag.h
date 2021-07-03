#pragma once

#include "Actor_all.h"

void FlagRegister(ObjectFactory* _factory);

void FlagInit(AInteractionComponent* _aitc);

void FlagUpdate(AInteractionComponent* _aitc, float _deltatime);

void FlagDestory(AInteractionComponent* _aitc);
