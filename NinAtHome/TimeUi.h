#pragma once

#include "Ui_all.h"

void TimeUiRegister(ObjectFactory* _factory);

void TimeUiInit(UInteractionComponent* _uitc);

void TimeUiUpdate(UInteractionComponent* _uitc, float _deltatime);

void TimeUiDestory(UInteractionComponent* _uitc);
