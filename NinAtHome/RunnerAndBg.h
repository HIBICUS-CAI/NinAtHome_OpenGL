#pragma once

#include "Actor_all.h"

void RunnerAndBgRegister(ObjectFactory* _factory);

void HiddenCommandInput(AInputComponent* _aic, float _deltatime);

void RunnerInput(AInputComponent* _aic, float _deltatime);

void RunnerInit(AInteractionComponent* _aitc);

void RunnerUpdate(AInteractionComponent* _aitc, float _deltatime);

void RunnerDestory(AInteractionComponent* _aitc);
