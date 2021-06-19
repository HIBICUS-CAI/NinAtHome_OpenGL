//---------------------------------------------------------------
// File: ATimerComponent.cpp
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë•régœy¶¨¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ATimerComponent.h"
#include "ActorObject.h"

ATimerComponent::ATimerComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order),
    mTimerMap({}), mTimerArray({})
{
    mTimerArray.clear();
    mTimerMap.clear();
}

ATimerComponent::~ATimerComponent()
{

}

void ATimerComponent::CompInit()
{

}

void ATimerComponent::CompUpdate(float _deltatime)
{

}

void ATimerComponent::CompDestory()
{

}

void ATimerComponent::AddTimer(std::string _name)
{

}

void ATimerComponent::StartTimer(std::string _name)
{

}

void ATimerComponent::PauseTimer(std::string _name)
{

}

void ATimerComponent::ResetTimer(std::string _name)
{

}

void ATimerComponent::DeleteTimer(std::string _name)
{

}

Timer* ATimerComponent::GetTimer(std::string _name)
{
    if (mTimerMap.find(_name) == mTimerMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this timer : [ %s ]\n", _name);
        return nullptr;
    }

    return mTimerMap[_name];
}
