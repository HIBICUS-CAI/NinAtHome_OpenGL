#pragma once

#include "Actor_all.h"

void BoardInit(AInteractionComponent* _aitc);

void BoardUpdate(AInteractionComponent* _aitc, float _deltatime);

void BoardDestory(AInteractionComponent* _aitc);

void SetToExplosion(ActorObject* _board);
