//---------------------------------------------------------------
// File: AAnimateComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトにアニメーションに関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "AAnimateComponent.h"
#include "ActorObject.h"
#include "SceneNode.h"
#include "texture.h"
#include "ASpriteComponent.h"

AAnimateComponent::AAnimateComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order), mAnimates({}),
    mCurrentAnimateCut(0), mCurrentAnimate(nullptr),
    mAnimateChangedFlg(false), mTimeCounter(0.f)
{
    mAnimates.clear();
}

AAnimateComponent::~AAnimateComponent()
{

}

void AAnimateComponent::CompInit()
{
    for (auto& ani : mAnimates)
    {
        ID3D11ShaderResourceView* exist =
            GetActorObjOwner()->GetSceneNodePtr()->
            CheckIfTexExist(ani.second->TexPath);
        if (!exist)
        {
            ani.second->Texture = LoadTexture(ani.second->TexPath);
            GetActorObjOwner()->GetSceneNodePtr()->
                InsertNewTex(ani.second->TexPath,
                    ani.second->Texture);
        }
        else
        {
            ani.second->Texture = exist;
        }
    }
}

void AAnimateComponent::CompUpdate(float _deltatime)
{
    if (mAnimateChangedFlg)
    {
        mTimeCounter = 0.f;
        mAnimateChangedFlg = false;
        ResetCurrentAnimateCut();
        SetThisAnimateToTextureComp(mCurrentAnimate,
            mCurrentAnimateCut);
    }

    if (mCurrentAnimate)
    {
        if (mTimeCounter > mCurrentAnimate->SwitchTime)
        {
            mTimeCounter = 0.f;
            ++mCurrentAnimateCut;
            if (mCurrentAnimateCut >= mCurrentAnimate->MaxCut)
            {
                if (mCurrentAnimate->RepeatFlg)
                {
                    mCurrentAnimateCut = 0;
                }
                else
                {
                    --mCurrentAnimateCut;
                }
            }

            SetThisAnimateToTextureComp(mCurrentAnimate,
                mCurrentAnimateCut);
        }
        mTimeCounter += _deltatime;
    }
}

void AAnimateComponent::CompDestory()
{
    for (auto& ani : mAnimates)
    {
        delete ani.second;
    }

    mAnimates.clear();
}

void AAnimateComponent::LoadAnimate(std::string _name,
    std::string _path, Float2 _stride, unsigned int _maxCount,
    bool _repeat, float _switchTime)
{
    ANIMATE_INFO* ani = new ANIMATE_INFO;
    ani->TexPath = _path;
    ani->Texture = 0;
    ani->Stride = _stride;
    ani->MaxCut = _maxCount;
    ani->RepeatFlg = _repeat;
    ani->SwitchTime = _switchTime;

    mAnimates.insert(std::make_pair(_name, ani));
}

void AAnimateComponent::DeleteAnimate(std::string _name)
{
    if (mAnimates.find(_name) == mAnimates.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this animation : [ %s ]\n",
            _name.c_str());
        return;
    }

    ANIMATE_INFO* ani = mAnimates[_name];
    delete ani;
    mAnimates.erase(_name);
}

void AAnimateComponent::ResetCurrentAnimateCut()
{
    mCurrentAnimateCut = 0;
}

void AAnimateComponent::ClearCurrentAnimate()
{
    mCurrentAnimate = nullptr;
}

void AAnimateComponent::ChangeAnimateTo(std::string _name)
{
    if (mAnimates.find(_name) == mAnimates.end())
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find this animation : [ %s ]\n",
            _name.c_str());
        return;
    }

    mCurrentAnimate = mAnimates[_name];
    mAnimateChangedFlg = true;
}

void AAnimateComponent::SetThisAnimateToTextureComp(
    ANIMATE_INFO* _animte, unsigned int _currentCut)
{
    if (!_animte)
    {
        MY_NN_LOG(LOG_ERROR, "cannot pass this animate\n");
        return;
    }

    ASpriteComponent* asc = nullptr;
    {
        std::string name = GetActorObjOwner()->GetObjectName() +
            "-sprite";
        asc = (ASpriteComponent*)(GetActorObjOwner()->
            GetAComponent(name));
        if (!asc)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot find sprite component of this obj : [ %s ]\n",
                GetActorObjOwner()->GetObjectName().c_str());
            return;
        }
    }

    float startX = 0.f;
    float startY = 0.f;
    unsigned int maxX = (int)(1.f / _animte->Stride.x);
    maxX = (((1.f / _animte->Stride.x) - maxX) > 0.5f) ?
        (maxX + 1) : maxX;
    startX = (float)(_currentCut % maxX) * _animte->Stride.x;
    startY = (float)(_currentCut / maxX) * _animte->Stride.y;
    Float4 uv = MakeFloat4(startX, startY,
        _animte->Stride.x, _animte->Stride.y);

    asc->ResetTexture(_animte->Texture);
    asc->SetUVValue(uv);
}
