#include "TempTest.h"

void TestInit(AInteractionComponent* _aitc)
{
    MY_NN_LOG(LOG_DEBUG, "init test!!!!!!!!\n");
}

void TestUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    auto ac = _aitc->GetActorObjOwner();
    auto acc = (ACollisionComponent*)(ac->
        GetAComponent(ac->GetObjectName() + "-collision"));
    if (acc)
    {
        acc->CheckCollisionWith(ac->GetSceneNodePtr()->
            GetActorObject("test2"));
    }

    Float4 color = MakeFloat4(1.f, 1.f, 1.f, 1.f);
    auto atic = (ATimerComponent*)(ac->
        GetAComponent("test-timer"));
    if (atic)
    {
        if (atic->GetTimer("r")->IsGreaterThan(5.f))
        {
            color.x = 0.5f;
        }
        if (atic->GetTimer("g")->IsGreaterThan(10.f))
        {
            color.y = 0.5f;
        }
        if (atic->GetTimer("b")->IsGreaterThan(15.f))
        {
            color.z = 0.5f;
        }
    }

    auto asc = (ASpriteComponent*)(ac->
        GetAComponent("test-sprite"));
    if (asc)
    {
        asc->SetOffsetColor(color);
    }
}

void TestDestory(AInteractionComponent* _aitc)
{
    MY_NN_LOG(LOG_DEBUG, "test destory!!!!!!!!\n");
}

void TestUiInit(UInteractionComponent* _aitc)
{
    MY_NN_LOG(LOG_DEBUG, "ui init test!!!!!!!!\n");
}

void TestUiUpdate(UInteractionComponent* _aitc, float _deltatime)
{
    auto scene = _aitc->GetUiObjOwner()->GetSceneNodePtr();
    if (GetControllerTrigger(NpadButton::R::Index))
    {
        if (scene->GetUiObject("test-ui")->IsObjectActive() ==
            STATUS::ACTIVE)
        {
            scene->GetUiObject("test-ui")->
                SetObjectActive(STATUS::PAUSE);
        }
        else if (scene->GetUiObject("test-ui")->IsObjectActive() ==
            STATUS::PAUSE)
        {
            scene->GetUiObject("test-ui")->
                SetObjectActive(STATUS::ACTIVE);
        }
    }
}

void TestUiDestory(UInteractionComponent* _aitc)
{
    MY_NN_LOG(LOG_DEBUG, "ui test destory!!!!!!!!\n");
}

void TempUiInput(UInputComponent* _uic, float _deltatime)
{
    UiObject* owner = _uic->GetUiObjOwner();

    std::string btnmapName =
        owner->GetObjectName() + "-btnmap";
    UBtnMapComponent* ubmc = nullptr;
    ubmc = (UBtnMapComponent*)owner->GetUComponent(btnmapName);

    if (GetControllerTrigger(NpadButton::Left::Index))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectLeftBtn();
        }
    }
    else if (GetControllerTrigger(NpadButton::Right::Index))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectRightBtn();
        }
    }
    else if (GetControllerTrigger(NpadButton::Up::Index))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectUpBtn();
        }
    }
    else if (GetControllerTrigger(NpadButton::Down::Index))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectDownBtn();
        }
    }
}

void TempMove(AInputComponent* _aic, float _deltatime)
{
    ActorObject* owner = _aic->GetActorObjOwner();

    if (GetControllerTrigger(NpadButton::X::Index))
    {
        if (owner)
        {
            auto aac = (AAnimateComponent*)(owner->
                GetAComponent("test-animate"));
            if (aac)
            {
                aac->ChangeAnimateTo("run");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::Y::Index))
    {
        if (owner)
        {
            auto aac = (AAnimateComponent*)(owner->
                GetAComponent("test-animate"));
            if (aac)
            {
                aac->ChangeAnimateTo("number");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::A::Index))
    {
        if (owner)
        {
            auto atic = (ATimerComponent*)(owner->
                GetAComponent("test-timer"));
            if (atic)
            {
                atic->StartTimer("r");
                atic->StartTimer("g");
                atic->StartTimer("b");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::B::Index))
    {
        if (owner)
        {
            auto atic = (ATimerComponent*)(owner->
                GetAComponent("test-timer"));
            if (atic)
            {
                atic->ResetTimer("r");
                atic->ResetTimer("g");
                atic->ResetTimer("b");
            }
        }
    }
    if (GetControllerPress(NpadButton::StickLLeft::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateXAsix(-200.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    -200.f * _deltatime, 0.f));
        }
    }
    if (GetControllerPress(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateXAsix(200.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    200.f * _deltatime, 0.f));
        }
    }
    if (GetControllerPress(NpadButton::StickLUp::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateYAsix(-200.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    0.f, -200.f * _deltatime));
        }
    }
    if (GetControllerPress(NpadButton::StickLDown::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateYAsix(200.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    0.f, 200.f * _deltatime));
        }
    }
}
