//---------------------------------------------------------------
// File: AAnimateComponent.h
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥¢¥Ë¥á©`¥·¥ç¥ó¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"
#include <unordered_map>

struct ANIMATE_INFO
{
    unsigned int Texture;
    Float2 Stride;
    unsigned int MaxCut;
    bool RepeatFlg;
};

class AAnimateComponent :
    public AComponent
{
public:
    AAnimateComponent(std::string _name, class ActorObject* _owner,
        int _order);
    virtual ~AAnimateComponent();

    void LoadAnimate(std::string _name, std::string _path,
        Float2 _stride, unsigned int _maxCount);

    void DeleteAnimate(std::string _name);

    void ResetCurrentAnimateCut();

    void ChangeAnimateTo(std::string _name);

private:
    void SetThisAnimateToTextureComp(std::string _name);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::unordered_map<std::string, ANIMATE_INFO*> mAnimates;

    unsigned int mCurrentAnimateCut;
};
