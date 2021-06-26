#include "TitleStartBtn.h"
#include "controller.h"

void StartBtnInput(UInputComponent* _uic, float _deltatime)
{
    bool selected = ((UBtnMapComponent*)
        (_uic->GetUiObjOwner()->GetUComponent(
            "start-btn-ui-btnmap")))->IsBeingSelected();
    if (selected)
    {
        if (GetControllerTrigger(NpadButton::A::Index))
        {
            _uic->GetUiObjOwner()->GetSceneNodePtr()->
                GetSceneManagerPtr()->LoadSceneNode(
                    "first-scene",
                    "rom:/Configs/Scenes/1-scene.json");
        }
    }
}
