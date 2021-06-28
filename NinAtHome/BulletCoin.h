#pragma once

#include "Actor_all.h"

void BulletParentInit(AInteractionComponent* _aitc);

void CreateNewBullet(Float3 _pos, SceneNode* _scene);

void BulletInit(AInteractionComponent* _aitc);

void BulletUpdate(AInteractionComponent* _aitc, float _deltatime);

void BulletDestory(AInteractionComponent* _aitc);
