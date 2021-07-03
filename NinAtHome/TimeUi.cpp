#include "TimeUi.h"

static float g_TimeLimit = 45.f;
static Float4 g_Color;

void TimeUiRegister(ObjectFactory* _factory)
{
    auto init = _factory->GetUiInterInitPool();
    auto update = _factory->GetUiInterUpdatePool();
    auto destory = _factory->GetUiInterDestoryPool();

    init->insert(std::make_pair(
        FUNC_NAME(TimeUiInit), TimeUiInit));
    update->insert(std::make_pair(
        FUNC_NAME(TimeUiUpdate), TimeUiUpdate));
    destory->insert(std::make_pair(
        FUNC_NAME(TimeUiDestory), TimeUiDestory));
}

void TimeUiInit(UInteractionComponent* _uitc)
{
    g_TimeLimit = 45.f;
    g_Color = MakeFloat4(0.f, 0.f, 0.f, 1.f);
}

void TimeUiUpdate(UInteractionComponent* _uitc, float _deltatime)
{
    std::string showTime = "REST : " +
        std::to_string(g_TimeLimit) + " sec";
    float redOffset = (g_TimeLimit / 45.f);
    Float4 colorOffset = MakeFloat4(
        1.f - redOffset, 0.f, 0.f, 1.f);
    ((UTextComponent*)
        (_uitc->GetUiObjOwner()->
            GetUComponent("time-ui-text")))->
        ChangeTextString(showTime);
    ((UTextComponent*)
        (_uitc->GetUiObjOwner()->
            GetUComponent("time-ui-text")))->
        SetTextColor(colorOffset);
    g_TimeLimit -= _deltatime;

    if (showTime == "REST : 0.000000 sec" ||
        g_TimeLimit < 0.f)
    {
        _uitc->GetUiObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->LoadSceneNode(
                "result-fail-scene",
                "rom:/Configs/Scenes/result-fail-scene.json");
    }
}

void TimeUiDestory(UInteractionComponent* _uitc)
{

}
