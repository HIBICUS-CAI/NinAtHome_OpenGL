#include "SpriteHelper.h"
#include "main.h"

struct VERTEX_3D
{
    Float3 Position;
    Float4 Color;
    Float2 TexCoord;
};

void DrawSprite(ID3D11Buffer* const* ppVertexBuffers,
    ID3D11Buffer* ppIndexBuffers,
    float x, float y, float width, float height,
    float tx, float ty, float tw, float th,
    Float4 color)
{
    D3D11_MAPPED_SUBRESOURCE msr;
    GetDxHelperPtr()->GetImmediateContextPtr()->Map(
        *ppVertexBuffers, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

    float hw, hh;
    hw = width * 0.5f;
    hh = height * 0.5f;

    vertex[0].Position = MakeFloat3(x - hw, y + hh, 0.0f);
    vertex[1].Position = MakeFloat3(x + hw, y + hh, 0.0f);
    vertex[2].Position = MakeFloat3(x + hw, y - hh, 0.0f);
    vertex[3].Position = MakeFloat3(x - hw, y - hh, 0.0f);

    vertex[0].Color = color;
    vertex[1].Color = color;
    vertex[2].Color = color;
    vertex[3].Color = color;

    vertex[0].TexCoord = MakeFloat2(tx, ty + th);
    vertex[1].TexCoord = MakeFloat2(tx + tw, ty + th);
    vertex[2].TexCoord = MakeFloat2(tx + tw, ty);
    vertex[3].TexCoord = MakeFloat2(tx, ty);

    GetDxHelperPtr()->GetImmediateContextPtr()->Unmap(
        *ppVertexBuffers, 0);

    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    GetDxHelperPtr()->GetImmediateContextPtr()->
        IASetVertexBuffers(0, 1, ppVertexBuffers,
            &stride, &offset);
    GetDxHelperPtr()->GetImmediateContextPtr()->
        IASetIndexBuffer(ppIndexBuffers,
            DXGI_FORMAT_R32_UINT, 0);

    GetDxHelperPtr()->GetImmediateContextPtr()->
        DrawIndexed(6, 0, 0);
}
