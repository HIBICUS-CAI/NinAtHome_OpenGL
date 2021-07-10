#include "TempTest.h"

void TempTestRegister(ObjectFactory* _factory)
{
    auto aInputPoolPtr = _factory->GetActorInputPool();
    auto aInitPoolPtr = _factory->GetActorInterInitPool();
    auto aUpdatePoolPtr = _factory->GetActorInterUpdatePool();
    auto aDestoryPoolPtr = _factory->GetActorInterDestoryPool();
    auto uInputPoolPtr = _factory->GetUiInputPool();
    auto uInitPoolPtr = _factory->GetUiInterInitPool();
    auto uUpdatePoolPtr = _factory->GetUiInterUpdatePool();
    auto uDestoryPoolPtr = _factory->GetUiInterDestoryPool();

    aInitPoolPtr->insert(
        std::make_pair(FUNC_NAME(TestInit), TestInit));
    aUpdatePoolPtr->insert(
        std::make_pair(FUNC_NAME(TestUpdate), TestUpdate));
    aDestoryPoolPtr->insert(
        std::make_pair(FUNC_NAME(TestDestory), TestDestory));
    uInitPoolPtr->insert(
        std::make_pair(FUNC_NAME(TestUiInit), TestUiInit));
    uUpdatePoolPtr->insert(
        std::make_pair(FUNC_NAME(TestUiUpdate), TestUiUpdate));
    uDestoryPoolPtr->insert(
        std::make_pair(FUNC_NAME(TestUiDestory), TestUiDestory));
    aInputPoolPtr->insert(
        std::make_pair(FUNC_NAME(TempMove), TempMove));
    uInputPoolPtr->insert(
        std::make_pair(FUNC_NAME(TempUiInput), TempUiInput));
}

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
    if (GetControllerTrigger(GP_RIGHTFORESHDBTN))
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

    if (GetControllerTrigger(GP_LEFTDIRBTN))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectLeftBtn();
        }
    }
    else if (GetControllerTrigger(GP_RIGHTDIRBTN))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectRightBtn();
        }
    }
    else if (GetControllerTrigger(GP_UPDIRBTN))
    {
        if (ubmc && ubmc->IsBeingSelected())
        {
            ubmc->SelectUpBtn();
        }
    }
    else if (GetControllerTrigger(GP_DOWNDIRBTN))
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

    if (GetControllerTrigger(GP_TOPBTN))
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
    if (GetControllerTrigger(GP_LEFTBTN))
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
    if (GetControllerTrigger(GP_RIGHTBTN))
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
    if (GetControllerTrigger(GP_BOTTOMBTN))
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
    if (GetControllerLeftStick().x < 0)
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
    if (GetControllerLeftStick().x > 0)
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
    if (GetControllerLeftStick().y > 0)
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
    if (GetControllerLeftStick().y < 0)
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
