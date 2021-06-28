#include "BulletCoin.h"

void CreateNewBullet(Float3 _pos, SceneNode* _scene)
{
    int updateOrder = 0;
    static int nameID = 0;
    std::string name =
        "bullet-" + std::to_string(++nameID) + "-actor";

    ActorObject* bullet = new ActorObject(
        name, _scene, updateOrder);

    {
        ATransformComponent* atc = new ATransformComponent(
            name + "-transform", bullet, -1,
            MakeFloat3(0.f, 0.f, 0.f));
        atc->SetPosition(_pos);
        bullet->AddAComponent(atc);

        ASpriteComponent* asc = new ASpriteComponent(
            name + "-sprite", bullet, 0, 1);
        asc->LoadTextureByPath("rom:/Assets/Textures/coin.tga");
        asc->SetTexWidth(36.f);
        asc->SetTexHeight(36.f);
        bullet->AddAComponent(asc);

        AInteractionComponent* aitc = new AInteractionComponent(
            name + "-interaction", bullet, 0);
        aitc->SetInitFunc(BulletInit);
        aitc->SetUpdateFunc(BulletUpdate);
        aitc->SetDestoryFunc(BulletDestory);
        bullet->AddAComponent(aitc);

        ATimerComponent* atic = new ATimerComponent(
            name + "-timer", bullet, 0);
        atic->AddTimer("life-time");
        bullet->AddAComponent(atic);

        ACollisionComponent* acc = new ACollisionComponent(
            name + "-collision", bullet, 0);
        acc->SetCollisionStatus(COLLISION_TYPE::CIRCLE,
            MakeFloat2(18.f, 18.f), true);
        bullet->AddAComponent(acc);
    }

    _scene->AddActorObject(bullet);
}

void BulletInit(AInteractionComponent* _aitc)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        std::string name = owner->GetObjectName();
        ((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            StartTimer("life-time");
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
        _board->SetObjectActive(STATUS::NEED_DESTORY);
        _bullet->SetObjectActive(STATUS::NEED_DESTORY);
    }
}

void BulletUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        std::string name = owner->GetObjectName();
        ((ATransformComponent*)(owner->
            GetAComponent(name + "-transform")))->
            TranslateXAsix(700.f * _deltatime);

        if (((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            GetTimer("life-time")->IsGreaterThan(1.f))
        {
            owner->SetObjectActive(STATUS::NEED_DESTORY);
        }

        ActorObject* board = nullptr;
        for (int i = 0; i < 2; i++)
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

}
