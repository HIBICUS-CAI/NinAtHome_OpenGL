#pragma once

#include "Actor_all.h"
#include "Ui_all.h"
#include "controller.h"

void TempTestRegister(ObjectFactory* _factory);

void TestInit(AInteractionComponent* _aitc);

void TestUpdate(AInteractionComponent* _aitc, float _deltatime);

void TestDestory(AInteractionComponent* _aitc);

void TestUiInit(UInteractionComponent* _aitc);

void TestUiUpdate(UInteractionComponent* _aitc, float _deltatime);

void TestUiDestory(UInteractionComponent* _aitc);

void TempUiInput(UInputComponent* _uic, float _deltatime);

void TempMove(AInputComponent* _aic, float _deltatime);
