#include "BulletCoin.h"
#include "Board.h"

struct BULLET_INFO
{
    bool canUse = false;
    ActorObject* actor = nullptr;
};

static BULLET_INFO g_AllBullets[3];

void BulletCoinRegister(ObjectFactory* _factory)
{
    auto init = _factory->GetActorInterInitPool();
    auto update = _factory->GetActorInterUpdatePool();
    auto destory = _factory->GetActorInterDestoryPool();

    init->insert(std::make_pair(
        FUNC_NAME(BulletInit), BulletInit));
    update->insert(std::make_pair(
        FUNC_NAME(BulletUpdate), BulletUpdate));
    destory->insert(std::make_pair(
        FUNC_NAME(BulletDestory), BulletDestory));
}

void CreateNewBullet(Float3 _pos, SceneNode* _scene)
{
    for (int i = 0; i < 3; i++)
    {
        if (g_AllBullets[i].canUse)
        {
            g_AllBullets[i].canUse = false;
            ActorObject* bullet = g_AllBullets[i].actor;
            ((ATimerComponent*)(bullet->GetAComponent(
                bullet->GetObjectName() + "-timer")))->
                StartTimer("life-time");
            ((ATransformComponent*)(bullet->GetAComponent(
                bullet->GetObjectName() + "-transform")))->
                SetPosition(_pos);
            break;
        }
    }
}

void BulletInit(AInteractionComponent* _aitc)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        for (int i = 0; i < 3; i++)
        {
            if (!g_AllBullets[i].canUse && !g_AllBullets[i].actor)
            {
                g_AllBullets[i].canUse = true;
                g_AllBullets[i].actor = owner;
                break;
            }
        }
    }
}

void BulletCheckWithBoard(ActorObject* _bullet, ActorObject* _board,
    float _deltatime)
{
    if (!_board)
    {
        return;
    }

    std::string bulletName = _bullet->GetObjectName();
    if (((ACollisionComponent*)(_bullet->
        GetAComponent(bulletName + "-collision")))->
        CheckCollisionWith(_board))
    {
        MY_NN_LOG(LOG_DEBUG, "BOOM!\n");

        SetToExplosion(_board);

        for (int i = 0; i < 3; i++)
        {
            if (g_AllBullets[i].actor == _bullet)
            {
                g_AllBullets[i].canUse = false;

                ((ATimerComponent*)(g_AllBullets[i].actor->GetAComponent(
                    g_AllBullets[i].actor->GetObjectName() + "-timer")))->
                    ResetTimer("life-time");
                ((ATimerComponent*)(g_AllBullets[i].actor->GetAComponent(
                    g_AllBullets[i].actor->GetObjectName() + "-timer")))->
                    PauseTimer("life-time");
                ((ATransformComponent*)(g_AllBullets[i].actor->GetAComponent(
                    g_AllBullets[i].actor->GetObjectName() + "-transform")))->
                    SetPosition(MakeFloat3(-10000.f, 0.f, 0.f));
                g_AllBullets[i].canUse = true;
                break;
            }
        }
    }
}

void BulletUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        std::string name = owner->GetObjectName();
        if (((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            GetTimer("life-time")->IsGreaterThan(0.016f))
        {
            ((ATransformComponent*)(owner->
                GetAComponent(name + "-transform")))->
                TranslateXAsix(700.f * _deltatime);
        }

        if (((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            GetTimer("life-time")->IsGreaterThan(1.f))
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_AllBullets[i].actor == owner)
                {
                    g_AllBullets[i].canUse = false;

                    ((ATimerComponent*)(g_AllBullets[i].actor->GetAComponent(
                        g_AllBullets[i].actor->GetObjectName() + "-timer")))->
                        ResetTimer("life-time");
                    ((ATimerComponent*)(g_AllBullets[i].actor->GetAComponent(
                        g_AllBullets[i].actor->GetObjectName() + "-timer")))->
                        PauseTimer("life-time");
                    ((ATransformComponent*)(g_AllBullets[i].actor->GetAComponent(
                        g_AllBullets[i].actor->GetObjectName() + "-transform")))->
                        SetPosition(MakeFloat3(-10000.f, 0.f, 0.f));
                    g_AllBullets[i].canUse = true;
                    break;
                }
            }
        }

        ActorObject* board = nullptr;
        for (int i = 0; i < 7; i++)
        {
            std::string name =
                "wood-" + std::to_string(i + 1) + "-actor";
            board = owner->GetSceneNodePtr()->
                GetActorObject(name);
            BulletCheckWithBoard(owner, board, _deltatime);
        }
    }
}

void BulletDestory(AInteractionComponent* _aitc)
{
    for (int i = 0; i < 3; i++)
    {
        if (g_AllBullets[i].actor == _aitc->GetActorObjOwner())
        {
            g_AllBullets[i].canUse = false;
            g_AllBullets[i].actor = nullptr;
        }
    }
}
