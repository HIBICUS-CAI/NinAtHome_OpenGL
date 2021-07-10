#include "ResultBtn.h"
#include "controller.h"

void ResultBtnRegister(ObjectFactory* _factory)
{
    auto pool = _factory->GetUiInputPool();
    pool->insert(std::make_pair(
        FUNC_NAME(RetryBtnInput), RetryBtnInput));
    pool->insert(std::make_pair(
        FUNC_NAME(TitleBtnInput), TitleBtnInput));
}

void RetryBtnInput(UInputComponent* _uic, float _deltatime)
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

    if (ubmc && ubmc->IsBeingSelected())
    {
        if (GetControllerTrigger(GP_RIGHTBTN))
        {
            _uic->GetUiObjOwner()->GetSceneNodePtr()->
                GetSceneManagerPtr()->LoadSceneNode(
                    "run-scene",
                    "rom:/Configs/Scenes/run-scene.json");
        }
    }
}

void TitleBtnInput(UInputComponent* _uic, float _deltatime)
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

    if (ubmc && ubmc->IsBeingSelected())
    {
        if (GetControllerTrigger(GP_RIGHTBTN))
        {
            _uic->GetUiObjOwner()->GetSceneNodePtr()->
                GetSceneManagerPtr()->LoadSceneNode(
                    "title-scene",
                    "rom:/Configs/Scenes/title-scene.json");
        }
    }
}
