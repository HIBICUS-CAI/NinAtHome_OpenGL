#include "Loading.h"
#include "sound.h"

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
    _uitc->GetUiObjOwner()->GetSceneNodePtr()->
        GetSceneManagerPtr()->SetLoadFinishedFlag(false);
}

void LoadingUpdate(UInteractionComponent* _uitc, float _deltatime)
{
    static bool sound = false;
    if (!sound)
    {
        sound = true;
        PlayBGM("loading");
    }

    unsigned int now = _uitc->GetUiObjOwner()->GetSceneNodePtr()->
        GetSceneManagerPtr()->GetHasLoaded();
    unsigned int all = _uitc->GetUiObjOwner()->GetSceneNodePtr()->
        GetSceneManagerPtr()->GetNeedToLoad();
    if (now != all)
    {
        _uitc->GetUiObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->SetLoadFinishedFlag(false);
    }
    else
    {
        _uitc->GetUiObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->SetLoadFinishedFlag(true);
        sound = false;
        StopBGM("loading");
    }

    MY_NN_LOG(LOG_DEBUG, "%d of %d\n", now, all);
}

void LoadingDestory(UInteractionComponent* _uitc)
{

}
