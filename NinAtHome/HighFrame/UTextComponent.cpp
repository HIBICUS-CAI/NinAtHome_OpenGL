//---------------------------------------------------------------
// File: UTextComponent.cpp
// Proj: NinAtHome
// Info: UIオブジェクトに文字表示に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UTextComponent.h"
#include "UiObject.h"
#include "SceneNode.h"
#include "texture.h"
#include "sprite.h"
#include "json.h"

UTextComponent::UTextComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order), mTextString(""),
    mTextPosition(MakeFloat3(0.f, 0.f, 0.f)),
    mFontSize(MakeFloat2(0.f, 0.f)), mFontTexture(0),
    mTextColor(MakeFloat4(1.f, 1.f, 1.f, 1.f)), mTextPtr(nullptr),
    mKanaUV({}), mFontTexPath(""),
    mTextVertexBuffer(nullptr), mTextIndexBuffer(nullptr)
{
    mKanaUV.clear();

    JsonFile moji = {};
    LoadJsonFile(&moji, "rom:/Configs/moji.json");
    for (unsigned int i = 0; i < moji["moji"].Size(); i++)
    {
        mKanaUV.insert(std::make_pair(
            moji["moji"][i]["kana"].GetString(),
            MakeFloat3(
                moji["moji"][i]["start"][0].GetFloat() * MOJI_U,
                moji["moji"][i]["start"][1].GetFloat() * MOJI_V,
                moji["moji"][i]["size"].GetFloat())));
    }
}

UTextComponent::~UTextComponent()
{

}

void UTextComponent::CompInit()
{
    LoadFontTexture(mFontTexPath);

    CreateDefaultVertexIndexBuffer(&mTextVertexBuffer,
        &mTextIndexBuffer);
}

void UTextComponent::CompUpdate(float _deltatime)
{
    mTextPtr = mTextString.c_str();
}

void UTextComponent::CompDestory()
{
    
}

void UTextComponent::SetTextPosition(Float3 _pos)
{
    mTextPosition = _pos;
}

void UTextComponent::SetFontSize(Float2 _size)
{
    mFontSize = _size;
}

Float2 UTextComponent::GetFontSize() const
{
    return mFontSize;
}

void UTextComponent::SaveFontTexPath(std::string _path)
{
    mFontTexPath = _path;
}

void UTextComponent::LoadFontTexture(std::string _path)
{
    ID3D11ShaderResourceView* exist =
        GetUiObjOwner()->GetSceneNodePtr()->
        CheckIfTexExist(_path);
    if (!exist)
    {
        mFontTexture = LoadTexture(_path);
        GetUiObjOwner()->GetSceneNodePtr()->
            InsertNewTex(_path, mFontTexture);
    }
    else
    {
        mFontTexture = exist;
    }
}

void UTextComponent::ChangeTextString(std::string _text)
{
    mTextString = _text;
}

void UTextComponent::SetTextColor(Float4 _color)
{
    mTextColor = _color;
}

void UTextComponent::DrawUText()
{
    SetTexture(&mFontTexture);
    Float3 nowPosition = mTextPosition;

    for (auto i = mTextString.length() - mTextString.length();
        i < mTextString.length() + 1; i++)
    {
        std::string kana = "";
        std::string null = "";
        if ((i + 1) < (mTextString.length() + 1) &&
            mTextPtr[i + 1] != '\0')
        {
            char kanaStr[3] = "";
            kanaStr[0] = mTextPtr[i];
            kanaStr[1] = mTextPtr[i + 1];
            kanaStr[2] = '\0';
            kana = kanaStr;
        }

        if (mTextPtr[i] == '\0')
        {
            break;
        }
        else if (mTextPtr[i] == '\n')
        {
            nowPosition.x = mTextPosition.x;
            nowPosition.y += mFontSize.y;
            continue;
        }
        else if (kana != null)
        {
            if (mKanaUV.find(kana) != mKanaUV.end())
            {
                Float3 mojiData = mKanaUV[kana];
                Float2 uv = MakeFloat2(mojiData.x, mojiData.y);
                float sizeOffset = mojiData.z;

                {
                    Matrix4x4f zeroMove =
                    {
                        1.f,0.f,0.f,0.f,
                        0.f,1.f,0.f,0.f,
                        0.f,0.f,1.f,0.f,
                        0.f,0.f,0.f,1.f
                    };
                    GetDxHelperPtr()->
                        PassWorldMatrixToVS(&zeroMove);
                }

                DrawSprite(&mTextVertexBuffer, mTextIndexBuffer,
                    nowPosition.x, nowPosition.y,
                    mFontSize.x * sizeOffset,
                    mFontSize.y * sizeOffset,
                    uv.x, uv.y,
                    MOJI_U, MOJI_V, mTextColor);

                ++i;
                nowPosition.x += mFontSize.x;

                continue;
            }
        }

        if (mTextPtr[i] >= 32 && mTextPtr[i] <= 126)
        {
            unsigned int index = mTextPtr[i] - 32;
            Float2 uv = MakeFloat2(
                (float)(index % MOJI_TEX_H_NUM) * MOJI_U,
                (float)(index / MOJI_TEX_H_NUM) * MOJI_V);

            {
                Matrix4x4f zeroMove =
                {
                    1.f,0.f,0.f,0.f,
                    0.f,1.f,0.f,0.f,
                    0.f,0.f,1.f,0.f,
                    0.f,0.f,0.f,1.f
                };
                GetDxHelperPtr()->
                    PassWorldMatrixToVS(&zeroMove);
            }

            DrawSprite(&mTextVertexBuffer, mTextIndexBuffer,
                nowPosition.x, nowPosition.y,
                mFontSize.x, mFontSize.y, uv.x, uv.y,
                MOJI_U, MOJI_V, mTextColor);

            nowPosition.x += mFontSize.x;
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot support this char or moji in [ %s ]\n",
                mTextString.c_str());
        }
    }
}
