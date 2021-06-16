//---------------------------------------------------------------
// File: ATimerComponent.h
// Proj: NinAtHome
// Info: ACTOR���֥������Ȥ˕r�g�y�����v���ƤΥ���ݩ`�ͥ��
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"
#include <unordered_map>
#include <vector>

class Timer
{
    // TEMP-----------------
    int mTemp;
    // TEMP-----------------
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