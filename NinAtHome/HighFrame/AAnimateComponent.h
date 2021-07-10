//---------------------------------------------------------------
// File: AAnimateComponent.h
// Proj: NinAtHome
// Info: ACTORオブジェクトにアニメーションに関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"
#include <unordered_map>

struct ANIMATE_INFO
{
    std::string TexPath = "";
    ID3D11ShaderResourceView* Texture = nullptr;
    Float2 Stride = MakeFloat2(0.f, 0.f);
    unsigned int MaxCut = 0;
    bool RepeatFlg = false;
    float SwitchTime = 0.f;
};

class AAnimateComponent :
    public AComponent
{
public:
    AAnimateComponent(std::string _name, class ActorObject* _owner,
        int _order);
    virtual ~AAnimateComponent();

    void LoadAnimate(std::string _name, std::string _path,
        Float2 _stride, unsigned int _maxCount,
        bool _repeat, float _switchTime);

    void DeleteAnimate(std::string _name);

    void ResetCurrentAnimateCut();

    void ClearCurrentAnimate();

    void ChangeAnimateTo(std::string _name);

private:
    void SetThisAnimateToTextureComp(ANIMATE_INFO* _animte,
        unsigned int _currentCut);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::unordered_map<std::string, ANIMATE_INFO*> mAnimates;

    unsigned int mCurrentAnimateCut;

    ANIMATE_INFO* mCurrentAnimate;

    bool mAnimateChangedFlg;

    float mTimeCounter;
};
