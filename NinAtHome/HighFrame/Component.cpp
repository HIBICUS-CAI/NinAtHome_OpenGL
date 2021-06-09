//---------------------------------------------------------------
// File: Component.cpp
// Proj: NinAtHome
// Info: �����֥������Ȥ˴��d����륳��ݩ`�ͥ�ȳ���
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "Component.h"

Component::Component(std::string _name, STATUS _active) :
    mName(_name), mActive(_active)
{

}

Component::~Component()
{

}

std::string Component::GetComponentName() const
{
    return mName;
}

STATUS Component::IsCompActive() const
{
    return mActive;
}

void Component::SetCompActive(STATUS _active)
{
    mActive = _active;
}
