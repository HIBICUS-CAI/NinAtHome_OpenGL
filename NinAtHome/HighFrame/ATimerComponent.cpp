//---------------------------------------------------------------
// File: ATimerComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトに時間測定に関してのコンポーネント
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
    for (auto& timer : mTimerArray)
    {
        if (timer->Active)
        {
            timer->Time += _deltatime;
        }
    }
}

void ATimerComponent::CompDestory()
{
    for (auto& timer : mTimerArray)
    {
        delete timer;
    }

    mTimerArray.clear();
    mTimerMap.clear();
}

void ATimerComponent::AddTimer(std::string _name)
{
    Timer* t = new Timer;
    t->Name = _name;
    t->Active = false;
    t->Time = 0.f;

    mTimerArray.push_back(t);
    mTimerMap.insert(std::make_pair(_name, t));
}

void ATimerComponent::StartTimer(std::string _name)
{
    Timer* timer = GetTimer(_name);
    if (timer)
    {
        timer->Active = true;
    }
}

void ATimerComponent::PauseTimer(std::string _name)
{
    Timer* timer = GetTimer(_name);
    if (timer)
    {
        timer->Active = false;
    }
}

void ATimerComponent::ResetTimer(std::string _name)
{
    Timer* timer = GetTimer(_name);
    if (timer)
    {
        timer->Time = 0.f;
    }
}

void ATimerComponent::DeleteTimer(std::string _name)
{
    Timer* timer = GetTimer(_name);
    if (timer)
    {
        timer->Time = 0.f;
        mTimerMap.erase(_name);
    }
    else
    {
        return;
    }

    for (auto iter = mTimerArray.begin();
        iter != mTimerArray.end(); iter++)
    {
        if ((*iter)->Name == _name)
        {
            Timer* p = (*iter);
            delete p;
            mTimerArray.erase(iter);
            break;
        }
    }
}

Timer* ATimerComponent::GetTimer(std::string _name)
{
    if (mTimerMap.find(_name) == mTimerMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this timer : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mTimerMap[_name];
}
