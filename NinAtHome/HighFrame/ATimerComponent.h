//---------------------------------------------------------------
// File: ATimerComponent.h
// Proj: NinAtHome
// Info: ACTORオブジェクトに時間測定に関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"
#include <unordered_map>
#include <vector>

struct Timer
{
    std::string Name = "";
    bool Active = false;
    float Time = 0.f;

    bool IsGreaterThan(float _value)
    {
        return (Time > _value);
    }
};

class ATimerComponent :
    public AComponent
{
public:
    ATimerComponent(std::string _name, class ActorObject* _owner,
        int _order);
    virtual ~ATimerComponent();

    void AddTimer(std::string _name);

    void StartTimer(std::string _name);

    void PauseTimer(std::string _name);

    void ResetTimer(std::string _name);

    void DeleteTimer(std::string _name);

    Timer* GetTimer(std::string _name);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::unordered_map<std::string, Timer*> mTimerMap;

    std::vector<Timer*> mTimerArray;
};
