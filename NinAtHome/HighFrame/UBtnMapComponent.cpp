//---------------------------------------------------------------
// File: UBtnMapComponent.cpp
// Proj: NinAtHome
// Info: UIオブジェクトにボタン地図に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UBtnMapComponent.h"
#include "UiObject.h"
#include "SceneNode.h"
#include "UTransformComponent.h"

UBtnMapComponent::UBtnMapComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order),
    mSurroundBtns({ nullptr,nullptr,nullptr,nullptr }),
    mIsSelected(false), mSurroundName({ "","","","" }),
    mCanSelectOther(true)
{

}

UBtnMapComponent::~UBtnMapComponent()
{

}

void UBtnMapComponent::CompInit()
{
    SceneNode* scene = GetUiObjOwner()->GetSceneNodePtr();

    if (!scene)
    {
        MY_NN_LOG(LOG_ERROR, "cannot get scene in obj : [ %s ]\n",
            GetUiObjOwner()->GetObjectName().c_str());
        return;
    }

    std::string null = "";
    for (int i = 0; i < 4; i++)
    {
        if (mSurroundName[i] != null)
        {
            mSurroundBtns[i] =
                scene->GetUiObject(mSurroundName[i]);
        }
    }

    /*UpdateButtonMapWith(GetUiObjOwner());

    for (auto& ui : *(scene->GetUiArray()))
    {
        std::string btnCompName = ui->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(ui->GetUComponent(btnCompName));
        if (ubmc)
        {
            ubmc->UpdateButtonMapWith(GetUiObjOwner());
        }
    }*/
}

void UBtnMapComponent::CompUpdate(float _deltatime)
{

}

void UBtnMapComponent::CompDestory()
{

}

void UBtnMapComponent::SetIsSelected(bool _value)
{
    mIsSelected = _value;
}

bool UBtnMapComponent::IsBeingSelected() const
{
    return mIsSelected;
}

void UBtnMapComponent::SetCanSelectFlg(bool _value)
{
    mCanSelectOther = _value;
}

void UBtnMapComponent::SelectUpBtn()
{
    if (mSurroundBtns[UP_BTN] && mCanSelectOther)
    {
        std::string btnCompName =
            mSurroundBtns[UP_BTN]->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(mSurroundBtns[UP_BTN]->
                GetUComponent(btnCompName));

        if (!ubmc)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get btn's comp in obj : [ %s ]\n",
                mSurroundBtns[UP_BTN]->GetObjectName().c_str());
            return;
        }

        SetIsSelected(false);
        ubmc->SetIsSelected(true);

        int nowBtnOrder = 0;
        int nxtBtnOrder = 0;
        int count = 0;
        for (auto i = GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->begin();
            i != GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->end(); i++)
        {
            if ((*i) == GetUiObjOwner())
            {
                nowBtnOrder = count;
            }
            if ((*i) == ubmc->GetUiObjOwner())
            {
                nxtBtnOrder = count;
            }

            ++count;
        }

        if (nxtBtnOrder > nowBtnOrder)
        {
            ubmc->SetCanSelectFlg(false);
        }
    }

    if (!mCanSelectOther)
    {
        mCanSelectOther = true;
    }
}

void UBtnMapComponent::SelectDownBtn()
{
    if (mSurroundBtns[DOWN_BTN] && mCanSelectOther)
    {
        std::string btnCompName =
            mSurroundBtns[DOWN_BTN]->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(mSurroundBtns[DOWN_BTN]->
                GetUComponent(btnCompName));

        if (!ubmc)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get btn's comp in obj : [ %s ]\n",
                mSurroundBtns[DOWN_BTN]->GetObjectName().c_str());
            return;
        }

        SetIsSelected(false);
        ubmc->SetIsSelected(true);

        int nowBtnOrder = 0;
        int nxtBtnOrder = 0;
        int count = 0;
        for (auto i = GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->begin();
            i != GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->end(); i++)
        {
            if ((*i) == GetUiObjOwner())
            {
                nowBtnOrder = count;
            }
            if ((*i) == ubmc->GetUiObjOwner())
            {
                nxtBtnOrder = count;
            }

            ++count;
        }

        if (nxtBtnOrder > nowBtnOrder)
        {
            ubmc->SetCanSelectFlg(false);
        }
    }

    if (!mCanSelectOther)
    {
        mCanSelectOther = true;
    }
}

void UBtnMapComponent::SelectLeftBtn()
{
    if (mSurroundBtns[LEFT_BTN] && mCanSelectOther)
    {
        std::string btnCompName =
            mSurroundBtns[LEFT_BTN]->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(mSurroundBtns[LEFT_BTN]->
                GetUComponent(btnCompName));

        if (!ubmc)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get btn's comp in obj : [ %s ]\n",
                mSurroundBtns[LEFT_BTN]->GetObjectName().c_str());
            return;
        }

        SetIsSelected(false);
        ubmc->SetIsSelected(true);

        int nowBtnOrder = 0;
        int nxtBtnOrder = 0;
        int count = 0;
        for (auto i = GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->begin();
            i != GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->end(); i++)
        {
            if ((*i) == GetUiObjOwner())
            {
                nowBtnOrder = count;
            }
            if ((*i) == ubmc->GetUiObjOwner())
            {
                nxtBtnOrder = count;
            }

            ++count;
        }

        if (nxtBtnOrder > nowBtnOrder)
        {
            ubmc->SetCanSelectFlg(false);
        }
    }

    if (!mCanSelectOther)
    {
        mCanSelectOther = true;
    }
}

void UBtnMapComponent::SelectRightBtn()
{
    if (mSurroundBtns[RIGHT_BTN] && mCanSelectOther)
    {
        std::string btnCompName =
            mSurroundBtns[RIGHT_BTN]->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(mSurroundBtns[RIGHT_BTN]->
                GetUComponent(btnCompName));

        if (!ubmc)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get btn's comp in obj : [ %s ]\n",
                mSurroundBtns[RIGHT_BTN]->GetObjectName().c_str());
            return;
        }

        SetIsSelected(false);
        ubmc->SetIsSelected(true);

        int nowBtnOrder = 0;
        int nxtBtnOrder = 0;
        int count = 0;
        for (auto i = GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->begin();
            i != GetUiObjOwner()->GetSceneNodePtr()->
            GetUiArray()->end(); i++)
        {
            if ((*i) == GetUiObjOwner())
            {
                nowBtnOrder = count;
            }
            if ((*i) == ubmc->GetUiObjOwner())
            {
                nxtBtnOrder = count;
            }

            ++count;
        }

        if (nxtBtnOrder > nowBtnOrder)
        {
            ubmc->SetCanSelectFlg(false);
        }
    }

    if (!mCanSelectOther)
    {
        mCanSelectOther = true;
    }
}

UiObject* UBtnMapComponent::GetUpBtn() const
{
    return mSurroundBtns[UP_BTN];
}

UiObject* UBtnMapComponent::GetDownBtn() const
{
    return mSurroundBtns[DOWN_BTN];
}

UiObject* UBtnMapComponent::GetLeftBtn() const
{
    return mSurroundBtns[LEFT_BTN];
}

UiObject* UBtnMapComponent::GetRightBtn() const
{
    return mSurroundBtns[RIGHT_BTN];
}

void UBtnMapComponent::SetLeftName(std::string _name)
{
    mSurroundName[LEFT_BTN] = _name;
}

void UBtnMapComponent::SetRightName(std::string _name)
{
    mSurroundName[RIGHT_BTN] = _name;
}

void UBtnMapComponent::SetUpName(std::string _name)
{
    mSurroundName[UP_BTN] = _name;
}

void UBtnMapComponent::SetDownName(std::string _name)
{
    mSurroundName[DOWN_BTN] = _name;
}
