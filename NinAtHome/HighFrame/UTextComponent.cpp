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
#include "texture.h"
#include "sprite.h"

UTextComponent::UTextComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order), mTextString(""),
    mTextPosition(MakeFloat3(0.f, 0.f, 0.f)),
    mFontSize(MakeFloat2(0.f, 0.f)), mFontTexture(0),
    mTextColor(MakeFloat4(1.f, 1.f, 1.f, 1.f)), mTextPtr(nullptr),
    mKanaUV({})
{
    mKanaUV.clear();

    mKanaUV.insert(std::make_pair(
        "あ", MakeFloat3(0.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "い", MakeFloat3(1.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "う", MakeFloat3(2.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "え", MakeFloat3(3.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "お", MakeFloat3(4.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "か", MakeFloat3(5.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "き", MakeFloat3(6.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "く", MakeFloat3(7.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "け", MakeFloat3(8.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "こ", MakeFloat3(9.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "さ", MakeFloat3(10.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "し", MakeFloat3(11.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "す", MakeFloat3(12.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "せ", MakeFloat3(13.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "そ", MakeFloat3(14.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "た", MakeFloat3(15.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ち", MakeFloat3(16.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "つ", MakeFloat3(17.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "て", MakeFloat3(18.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "と", MakeFloat3(0.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "な", MakeFloat3(1.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "に", MakeFloat3(2.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ぬ", MakeFloat3(3.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ね", MakeFloat3(4.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "の", MakeFloat3(5.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "は", MakeFloat3(6.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ひ", MakeFloat3(7.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ふ", MakeFloat3(8.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "へ", MakeFloat3(9.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ほ", MakeFloat3(10.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ま", MakeFloat3(11.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "み", MakeFloat3(12.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "む", MakeFloat3(13.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "め", MakeFloat3(14.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "も", MakeFloat3(15.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "や", MakeFloat3(16.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ゆ", MakeFloat3(17.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "よ", MakeFloat3(18.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ら", MakeFloat3(0.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "り", MakeFloat3(1.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "る", MakeFloat3(2.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "れ", MakeFloat3(3.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ろ", MakeFloat3(4.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "わ", MakeFloat3(5.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "を", MakeFloat3(6.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ん", MakeFloat3(7.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ア", MakeFloat3(8.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "イ", MakeFloat3(9.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ウ", MakeFloat3(10.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "エ", MakeFloat3(11.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "オ", MakeFloat3(12.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "カ", MakeFloat3(13.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "キ", MakeFloat3(14.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ク", MakeFloat3(15.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ケ", MakeFloat3(16.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "コ", MakeFloat3(17.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "サ", MakeFloat3(18.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "シ", MakeFloat3(0.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ス", MakeFloat3(1.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "セ", MakeFloat3(2.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ソ", MakeFloat3(3.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "タ", MakeFloat3(4.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "チ", MakeFloat3(5.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ツ", MakeFloat3(6.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "テ", MakeFloat3(7.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ト", MakeFloat3(8.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ナ", MakeFloat3(9.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "二", MakeFloat3(10.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ヌ", MakeFloat3(11.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ネ", MakeFloat3(12.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ノ", MakeFloat3(13.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ハ", MakeFloat3(14.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ヒ", MakeFloat3(15.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "フ", MakeFloat3(16.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ヘ", MakeFloat3(17.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ホ", MakeFloat3(18.0f * MOJI_U, 8.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "マ", MakeFloat3(0.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ミ", MakeFloat3(1.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ム", MakeFloat3(2.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "メ", MakeFloat3(3.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "モ", MakeFloat3(4.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ヤ", MakeFloat3(5.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ユ", MakeFloat3(6.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ヨ", MakeFloat3(7.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ラ", MakeFloat3(8.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "リ", MakeFloat3(9.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ル", MakeFloat3(10.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "レ", MakeFloat3(11.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ロ", MakeFloat3(12.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ワ", MakeFloat3(13.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ヲ", MakeFloat3(14.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ン", MakeFloat3(15.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ー", MakeFloat3(16.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "°", MakeFloat3(17.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "゛", MakeFloat3(18.0f * MOJI_U, 9.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ぁ", MakeFloat3(0.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ぃ", MakeFloat3(1.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ぅ", MakeFloat3(2.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ぇ", MakeFloat3(3.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ぉ", MakeFloat3(4.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "っ", MakeFloat3(17.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ゃ", MakeFloat3(16.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ゅ", MakeFloat3(17.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ょ", MakeFloat3(18.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ゎ", MakeFloat3(5.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ァ", MakeFloat3(0.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ィ", MakeFloat3(1.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ゥ", MakeFloat3(2.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ェ", MakeFloat3(3.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ォ", MakeFloat3(4.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ッ", MakeFloat3(17.0f * MOJI_U, 5.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ャ", MakeFloat3(16.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ュ", MakeFloat3(17.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));
    mKanaUV.insert(std::make_pair(
        "ョ", MakeFloat3(18.0f * MOJI_U, 6.0f * MOJI_V, 1.0f)));

    mKanaUV.insert(std::make_pair(
        "ヮ", MakeFloat3(5.0f * MOJI_U, 7.0f * MOJI_V, 1.0f)));
}

UTextComponent::~UTextComponent()
{

}

void UTextComponent::CompInit()
{
    
}

void UTextComponent::CompUpdate(float _deltatime)
{
    mTextPtr = mTextString.c_str();
}

void UTextComponent::CompDestory()
{
    if (mFontTexture)
    {
        UnloadTexture(mFontTexture);
    }
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

void UTextComponent::LoadFontTexture(std::string _path)
{
    mFontTexture = LoadTexture(_path);
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
    SetTexture(mFontTexture);
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

#ifdef NIN_AT_HOME
                {
                    float zeroMove[16] =
                    {
                        1.f,0.f,0.f,0.f,
                        0.f,1.f,0.f,0.f,
                        0.f,0.f,1.f,0.f,
                        0.f,0.f,0.f,1.f
                    };
                    glUniformMatrix4fv(
                        glGetUniformLocation(
                            GetGlHelperPtr()->GetShaderID("default"),
                            "uWorld"), 1, GL_TRUE, zeroMove);
                }
#else

#endif // NIN_AT_HOME

                DrawSprite(nowPosition.x, nowPosition.y,
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

#ifdef NIN_AT_HOME
            {
                float zeroMove[16] =
                {
                    1.f,0.f,0.f,0.f,
                    0.f,1.f,0.f,0.f,
                    0.f,0.f,1.f,0.f,
                    0.f,0.f,0.f,1.f
                };
                glUniformMatrix4fv(
                    glGetUniformLocation(
                        GetGlHelperPtr()->GetShaderID("default"),
                        "uWorld"), 1, GL_TRUE, zeroMove);
            }
#else

#endif // NIN_AT_HOME

            DrawSprite(nowPosition.x, nowPosition.y,
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
