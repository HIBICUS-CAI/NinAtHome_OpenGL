#include "Loading.h"

void LoadingRegister(ObjectFactory* _factory)
{
    auto init = _factory->GetUiInterInitPool();
    auto update = _factory->GetUiInterUpdatePool();
    auto destroy = _factory->GetUiInterDestoryPool();

    init->insert(std::make_pair(
        FUNC_NAME(LoadingInit), LoadingInit));
    update->insert(std::make_pair(
        FUNC_NAME(LoadingUpdate), LoadingUpdate));
    destroy->insert(std::make_pair(
        FUNC_NAME(LoadingDestory), LoadingDestory));
}

void LoadingInit(UInteractionComponent* _uitc)
{

}

void LoadingUpdate(UInteractionComponent* _uitc, float _deltatime)
{
    static int a = 0;

    MY_NN_LOG(LOG_DEBUG, "%d\n", a++);
}

void LoadingDestory(UInteractionComponent* _uitc)
{

}
