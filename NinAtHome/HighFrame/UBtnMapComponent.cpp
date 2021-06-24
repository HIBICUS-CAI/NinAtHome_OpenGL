//---------------------------------------------------------------
// File: UBtnMapComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥Ü¥¿¥óµØ‡í¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
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
    mIsSelected(false)
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

    UpdateButtonMapWith(GetUiObjOwner());

    for (auto ui : *(scene->GetUiArray()))
    {
        std::string btnCompName = ui->GetObjectName() + "-btnmap";
        UBtnMapComponent* ubmc =
            (UBtnMapComponent*)(ui->GetUComponent(btnCompName));
        if (ubmc)
        {
            ubmc->UpdateButtonMapWith(GetUiObjOwner());
        }
    }
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

void UBtnMapComponent::SelectUpBtn()
{
    if (mSurroundBtns[UP_BTN])
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
    }
}

void UBtnMapComponent::SelectDownBtn()
{
    if (mSurroundBtns[DOWN_BTN])
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
    }
}

void UBtnMapComponent::SelectLeftBtn()
{
    if (mSurroundBtns[LEFT_BTN])
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
    }
}

void UBtnMapComponent::SelectRightBtn()
{
    if (mSurroundBtns[RIGHT_BTN])
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

void UBtnMapComponent::UpdateButtonMapWith(UiObject* _toAddUi)
{
    UTransformComponent* utcToAdd = nullptr;
    UTransformComponent* utcOther = nullptr;
    std::string utcNameToAdd = "";
    std::string utcNameOther = "";

    if (_toAddUi == GetUiObjOwner())
    {
        MY_NN_LOG(LOG_DEBUG,
            "start to get nearest of this obj [ %s ]\n",
            _toAddUi->GetObjectName().c_str());
        utcNameToAdd = _toAddUi->GetObjectName() + "-transform";
        utcToAdd = (UTransformComponent*)(_toAddUi->GetUComponent(
            utcNameToAdd));
        if (!utcToAdd)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get trans comp in obj : [ %s ]\n",
                _toAddUi->GetObjectName().c_str());
            return;
        }

        Float3 deltaPos = MakeFloat3(0.f, 0.f, 0.f);
        float nearestPos[4] = { 0.f,0.f,0.f,0.f };
        bool beginUpdate[4] = { false,false,false,false };

        for (auto ui : *(_toAddUi->GetSceneNodePtr()->GetUiArray()))
        {
            utcNameOther = ui->GetObjectName() + "-transform";
            utcOther = (UTransformComponent*)
                (ui->GetUComponent(utcNameOther));
            if (!utcOther)
            {
                MY_NN_LOG(LOG_ERROR,
                    "cannot get trans comp in obj : [ %s ]\n",
                    ui->GetObjectName().c_str());
                continue;
            }

            deltaPos = utcOther->GetPosition() -
                utcToAdd->GetPosition();
            float deltaX = deltaPos.x;
            float deltaY = deltaPos.y;
            if ((deltaX * deltaX) > (deltaY * deltaY))
            {
                if (deltaX > 0.f)
                {
                    if (!beginUpdate[RIGHT_BTN])
                    {
                        beginUpdate[RIGHT_BTN] = true;
                        nearestPos[RIGHT_BTN] = deltaX;
                        mSurroundBtns[RIGHT_BTN] = ui;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] right\n",
                            utcNameOther.c_str(), utcNameToAdd.c_str());
                    }
                    else
                    {
                        if (nearestPos[RIGHT_BTN] > deltaX)
                        {
                            nearestPos[RIGHT_BTN] = deltaX;
                            mSurroundBtns[RIGHT_BTN] = ui;
                            MY_NN_LOG(LOG_DEBUG,
                                "replace [ %s ] to [ %s ] right\n",
                                utcNameOther.c_str(), utcNameToAdd.c_str());
                        }
                    }
                }
                else
                {
                    if (!beginUpdate[LEFT_BTN])
                    {
                        beginUpdate[LEFT_BTN] = true;
                        nearestPos[LEFT_BTN] = deltaX;
                        mSurroundBtns[LEFT_BTN] = ui;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] left\n",
                            utcNameOther.c_str(), utcNameToAdd.c_str());
                    }
                    else
                    {
                        if (nearestPos[LEFT_BTN] < deltaX)
                        {
                            nearestPos[LEFT_BTN] = deltaX;
                            mSurroundBtns[LEFT_BTN] = ui;
                            MY_NN_LOG(LOG_DEBUG,
                                "replace [ %s ] to [ %s ] left\n",
                                utcNameOther.c_str(), utcNameToAdd.c_str());
                        }
                    }
                }
            }
            else
            {
                if (deltaY > 0.f)
                {
                    if (!beginUpdate[DOWN_BTN])
                    {
                        beginUpdate[DOWN_BTN] = true;
                        nearestPos[DOWN_BTN] = deltaY;
                        mSurroundBtns[DOWN_BTN] = ui;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] down\n",
                            utcNameOther.c_str(), utcNameToAdd.c_str());
                    }
                    else
                    {
                        if (nearestPos[DOWN_BTN] > deltaY)
                        {
                            nearestPos[DOWN_BTN] = deltaY;
                            mSurroundBtns[DOWN_BTN] = ui;
                            MY_NN_LOG(LOG_DEBUG,
                                "replace [ %s ] to [ %s ] down\n",
                                utcNameOther.c_str(), utcNameToAdd.c_str());
                        }
                    }
                }
                else
                {
                    if (!beginUpdate[UP_BTN])
                    {
                        beginUpdate[UP_BTN] = true;
                        nearestPos[UP_BTN] = deltaY;
                        mSurroundBtns[UP_BTN] = ui;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] up\n",
                            utcNameOther.c_str(), utcNameToAdd.c_str());
                    }
                    else
                    {
                        if (nearestPos[UP_BTN] < deltaY)
                        {
                            nearestPos[UP_BTN] = deltaY;
                            mSurroundBtns[UP_BTN] = ui;
                            MY_NN_LOG(LOG_DEBUG,
                                "replace [ %s ] to [ %s ] up\n",
                                utcNameOther.c_str(), utcNameToAdd.c_str());
                        }
                    }
                }
            }
        }
    }
    else
    {
        MY_NN_LOG(LOG_DEBUG,
            "start to work on replace of new obj [ %s ] and exist obj [ %s ]\n",
            _toAddUi->GetObjectName().c_str(), 
            GetUiObjOwner()->GetObjectName().c_str());
        utcNameToAdd = _toAddUi->GetObjectName() + "-transform";
        utcToAdd = (UTransformComponent*)(_toAddUi->GetUComponent(
            utcNameToAdd));
        if (!utcToAdd)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get trans comp in obj : [ %s ]\n",
                _toAddUi->GetObjectName().c_str());
            return;
        }

        std::string utcNameThis = GetUiObjOwner()->
            GetObjectName() + "-transform";
        UTransformComponent* utcThis =
            (UTransformComponent*)(GetUiObjOwner()->
                GetUComponent(utcNameThis));
        if (!utcThis)
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get trans comp in obj : [ %s ]\n",
                GetUiObjOwner()->GetObjectName().c_str());
            return;
        }

        Float3 deltaPos =
            utcToAdd->GetPosition() - utcThis->GetPosition();
        float deltaX = deltaPos.x;
        float deltaY = deltaPos.y;

        if ((deltaX * deltaX) > (deltaY * deltaY))
        {
            if (deltaX > 0.f)
            {
                if (mSurroundBtns[RIGHT_BTN])
                {
                    utcOther = (UTransformComponent*)
                        (mSurroundBtns[RIGHT_BTN]->
                        GetUComponent(mSurroundBtns[RIGHT_BTN]->
                            GetObjectName() + "-transform"));
                    if (!utcOther)
                    {
                        MY_NN_LOG(LOG_ERROR,
                            "cannot get trans comp in obj : [ %s ]\n",
                            mSurroundBtns[RIGHT_BTN]->GetObjectName().c_str());
                        return;
                    }

                    float nowDeltaX =
                        (utcOther->GetPosition() -
                            utcThis->GetPosition()).x;

                    if (deltaX < nowDeltaX)
                    {
                        mSurroundBtns[RIGHT_BTN] = _toAddUi;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] right instead of [ %s ]\n",
                            utcNameToAdd.c_str(), utcNameThis.c_str(),
                            utcOther->GetComponentName().c_str());
                    }
                }
                else
                {
                    mSurroundBtns[RIGHT_BTN] = _toAddUi;
                    MY_NN_LOG(LOG_DEBUG,
                        "set [ %s ] to [ %s ] right\n",
                        utcNameToAdd.c_str(), utcNameThis.c_str());
                }
            }
            else
            {
                if (mSurroundBtns[LEFT_BTN])
                {
                    utcOther = (UTransformComponent*)
                        (mSurroundBtns[LEFT_BTN]->
                        GetUComponent(mSurroundBtns[LEFT_BTN]->
                            GetObjectName() + "-transform"));
                    if (!utcOther)
                    {
                        MY_NN_LOG(LOG_ERROR,
                            "cannot get trans comp in obj : [ %s ]\n",
                            mSurroundBtns[LEFT_BTN]->GetObjectName().c_str());
                        return;
                    }

                    float nowDeltaX =
                        (utcOther->GetPosition() -
                            utcThis->GetPosition()).x;

                    if (deltaX > nowDeltaX)
                    {
                        mSurroundBtns[LEFT_BTN] = _toAddUi;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] left instead of [ %s ]\n",
                            utcNameToAdd.c_str(), utcNameThis.c_str(),
                            utcOther->GetComponentName().c_str());
                    }
                }
                else
                {
                    mSurroundBtns[LEFT_BTN] = _toAddUi;
                    MY_NN_LOG(LOG_DEBUG,
                        "set [ %s ] to [ %s ] left\n",
                        utcNameToAdd.c_str(), utcNameThis.c_str());
                }
            }
        }
        else
        {
            if (deltaY > 0.f)
            {
                if (mSurroundBtns[DOWN_BTN])
                {
                    utcOther = (UTransformComponent*)
                        (mSurroundBtns[DOWN_BTN]->
                        GetUComponent(mSurroundBtns[DOWN_BTN]->
                            GetObjectName() + "-transform"));
                    if (!utcOther)
                    {
                        MY_NN_LOG(LOG_ERROR,
                            "cannot get trans comp in obj : [ %s ]\n",
                            mSurroundBtns[DOWN_BTN]->GetObjectName().c_str());
                        return;
                    }

                    float nowDeltaY =
                        (utcOther->GetPosition() -
                            utcThis->GetPosition()).y;

                    if (deltaY < nowDeltaY)
                    {
                        mSurroundBtns[DOWN_BTN] = _toAddUi;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] down instead of [ %s ]\n",
                            utcNameToAdd.c_str(), utcNameThis.c_str(),
                            utcOther->GetComponentName().c_str());
                    }
                }
                else
                {
                    mSurroundBtns[DOWN_BTN] = _toAddUi;
                    MY_NN_LOG(LOG_DEBUG,
                        "set [ %s ] to [ %s ] down\n",
                        utcNameToAdd.c_str(), utcNameThis.c_str());
                }
            }
            else
            {
                if (mSurroundBtns[UP_BTN])
                {
                    utcOther = (UTransformComponent*)
                        (mSurroundBtns[UP_BTN]->
                        GetUComponent(mSurroundBtns[UP_BTN]->
                            GetObjectName() + "-transform"));
                    if (!utcOther)
                    {
                        MY_NN_LOG(LOG_ERROR,
                            "cannot get trans comp in obj : [ %s ]\n",
                            mSurroundBtns[UP_BTN]->GetObjectName().c_str());
                        return;
                    }

                    float nowDeltaY =
                        (utcOther->GetPosition() -
                            utcThis->GetPosition()).y;

                    if (deltaY > nowDeltaY)
                    {
                        mSurroundBtns[UP_BTN] = _toAddUi;
                        MY_NN_LOG(LOG_DEBUG,
                            "set [ %s ] to [ %s ] up instead of [ %s ]\n",
                            utcNameToAdd.c_str(), utcNameThis.c_str(),
                            utcOther->GetComponentName().c_str());
                    }
                }
                else
                {
                    mSurroundBtns[UP_BTN] = _toAddUi;
                    MY_NN_LOG(LOG_DEBUG,
                        "set [ %s ] to [ %s ] up\n",
                        utcNameToAdd.c_str(), utcNameThis.c_str());
                }
            }
        }
    }
}
