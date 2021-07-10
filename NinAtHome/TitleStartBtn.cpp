#include "TitleStartBtn.h"
#include "controller.h"

void StartBtnRegister(ObjectFactory* _factory)
{
    auto pool = _factory->GetUiInputPool();
    pool->insert(std::make_pair(
        FUNC_NAME(StartBtnInput), StartBtnInput));
}

void StartBtnInput(UInputComponent* _uic, float _deltatime)
{
    bool selected = ((UBtnMapComponent*)
        (_uic->GetUiObjOwner()->GetUComponent(
            "start-btn-ui-btnmap")))->IsBeingSelected();
    if (selected)
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
