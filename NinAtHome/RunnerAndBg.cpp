#include "RunnerAndBg.h"
#include "controller.h"
#include "BulletCoin.h"

void HiddenCommandInput(AInputComponent* _aic, float _deltatime)
{
    if (GetControllerTrigger(NpadButton::StickL::Index))
    {
        _aic->GetActorObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->LoadSceneNode(
                "result-success-scene",
                "rom:/Configs/Scenes/result-success-scene.json");
    }
    else if (GetControllerTrigger(NpadButton::StickR::Index))
    {
        _aic->GetActorObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->LoadSceneNode(
                "result-fail-scene",
                "rom:/Configs/Scenes/result-fail-scene.json");
    }
}

static float g_Gravity = 0.f;
static float g_VVel = 0.f;
static float g_HVel = 0.f;
static bool g_CanJump = true;

void RunnerInput(AInputComponent* _aic, float _deltatime)
{
    ActorObject* owner = _aic->GetActorObjOwner();

    if (GetControllerPress(NpadButton::StickLLeft::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(-g_HVel * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    -g_HVel * _deltatime, 0.f));
        }
    }
    else if (GetControllerPress(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(g_HVel * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    g_HVel * _deltatime, 0.f));
        }
    }
    else
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("stand");
        }
    }

    if (GetControllerTrigger(NpadButton::StickLLeft::Index) ||
        GetControllerTrigger(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("walk");
        }
    }

    static bool shouldSetWalk = true;
    if (GetControllerTrigger(NpadButton::B::Index))
    {
        if (owner && g_CanJump)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateYAsix(-15.f);
            g_CanJump = false;
            g_VVel = 600.f;
            shouldSetWalk = true;
        }
    }

    if (!g_CanJump)
    {
        ((AAnimateComponent*)(owner->
            GetAComponent("runner-actor-animate")))->
            ChangeAnimateTo("jump");
    }
    else
    {
        if (shouldSetWalk)
        {
            shouldSetWalk = false;
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("walk");
        }
    }

    if (GetControllerTrigger(NpadButton::ZR::Index) && owner)
    {
        CreateNewBullet(((ATransformComponent*)(owner->
            GetAComponent("runner-actor-transform")))->
            GetPosition(), owner->GetSceneNodePtr());
    }
}

void RunnerInit(AInteractionComponent* _aitc)
{
    g_Gravity = -1500.f;
    g_VVel = 0.f;
    g_HVel = 300.f;
}

bool CheckWithLand(ActorObject* _runner, ActorObject* _land,
    float _deltatime)
{
    if (!_land)
    {
        return false;
    }

    bool shouldFall = true;

    std::string landTransName = _land->GetObjectName() +
        "-transform";

    bool canStand = false;
    float deltaX = 0.f;
    float deltaY = 0.f;
    {
        float thisX = ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            GetPosition().x;
        float thatX = ((ATransformComponent*)(_land->
            GetAComponent(landTransName)))->GetPosition().x;
        deltaX = thisX - thatX;

        float thatY = ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            GetPosition().y;
        float thisY = ((ATransformComponent*)(_land->
            GetAComponent(landTransName)))->GetPosition().y;
        deltaY = thisY - thatY;
        deltaY -= 84.f;

        float width = 25.f + ((ACollisionComponent*)(_land->
            GetAComponent(_land->GetObjectName() +
                "-collision")))->GetCollisionSize().x;

        if (deltaX > -width && deltaX < width && deltaY > 7.5f)
        {
            canStand = true;
        }
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && canStand)
    {
        g_VVel = 0.f;
        shouldFall = false;
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && !canStand)
    {
        if (deltaX > 195.f)
        {
            if (deltaY < 7.5f)
            {
                ((ATransformComponent*)(_runner->
                    GetAComponent("runner-actor-transform")))->
                    TranslateXAsix(5.f);
                _runner->GetSceneNodePtr()->GetCamera()->
                    TranslateCameraPos(MakeFloat2(
                        5.f, 0.f));
            }
        }
        else if (deltaX < -195.f)
        {
            if (deltaY < 7.5f)
            {
                ((ATransformComponent*)(_runner->
                    GetAComponent("runner-actor-transform")))->
                    TranslateXAsix(-5.f);
                _runner->GetSceneNodePtr()->GetCamera()->
                    TranslateCameraPos(MakeFloat2(
                        -5.f, 0.f));
            }
        }
        else
        {
            g_VVel = 0.f;
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateYAsix(5.f);
        }
    }

    return shouldFall;
}

void CheckWithBoard(ActorObject* _runner, ActorObject* _board,
    float _deltatime)
{
    if (!_board)
    {
        return;
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_board))
    {
        std::string boardTransName = _board->GetObjectName() +
            "-transform";
        float deltaX = 0.f;
        {
            Float3 thisB = ((ATransformComponent*)
                (_board->GetAComponent(boardTransName)))->GetPosition();
            Float3 runP = ((ATransformComponent*)
                (_runner->GetAComponent("runner-actor-transform")))->
                GetPosition();
            deltaX = runP.x - thisB.x;
        }
        if (deltaX > 0.f)
        {
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(5.f);
            _runner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    5.f, 0.f));
        }
        else
        {
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(-5.f);
            _runner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    -5.f, 0.f));
        }
    }
}

void RunnerUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();

    ActorObject* land = nullptr;
    bool shouldFall = true;
    for (int i = 0; i < 20; i++)
    {
        std::string name =
            "midland-" + std::to_string(i + 1) + "-actor";
        land = owner->GetSceneNodePtr()->
            GetActorObject(name);
        bool thisShould = CheckWithLand(owner, land, _deltatime);
        shouldFall = shouldFall && thisShould;
    }

    if (shouldFall)
    {
        float distance = g_VVel * _deltatime -
            g_Gravity * _deltatime * _deltatime;
        g_VVel = g_VVel + g_Gravity * _deltatime;

        ((ATransformComponent*)(owner->
            GetAComponent("runner-actor-transform")))->
            TranslateYAsix(-distance);
    }

    if (shouldFall)
    {
        g_CanJump = false;
    }
    else
    {
        g_CanJump = true;
    }

    ActorObject* board = nullptr;
    for (int i = 0; i < 7; i++)
    {
        std::string name =
            "wood-" + std::to_string(i + 1) + "-actor";
        board = owner->GetSceneNodePtr()->
            GetActorObject(name);
        CheckWithBoard(owner, board, _deltatime);
    }

    if (((ATransformComponent*)(owner->
        GetAComponent("runner-actor-transform")))->
        GetPosition().y > 600.f)
    {
        owner->GetSceneNodePtr()->GetSceneManagerPtr()->
            LoadSceneNode(
                "result-fail-scene",
                "rom:/Configs/Scenes/result-fail-scene.json");
    }
}

void RunnerDestory(AInteractionComponent* _aitc)
{

}
