#pragma once

#pragma once

#include <map>
#include <vector>
#include <string>
#include <d3d11_1.h>
#include <DirectXMath.h>

using Float3 = DirectX::XMFLOAT3;
using Float4 = DirectX::XMFLOAT4;
using Float2 = DirectX::XMFLOAT2;
using Matrix4x4f = DirectX::XMFLOAT4X4;
using Float4x4 = DirectX::XMMATRIX;

void MatrixStore_DX(Float4x4* ptr, Matrix4x4f mat);
void CreateDefaultVertexIndexBuffer(
    ID3D11Buffer** ppVertexBuffer,
    ID3D11Buffer** ppIndexBuffer);

using MakeFloat2 = Float2;
using MakeFloat3 = Float3;
using MakeFloat4 = Float4;

typedef struct _VERTEX
{
    Float3 Position;
    Float4 Color;
    Float2 TexCoord;
}VERTEX;

struct ConstantBuffer
{
    Float4x4 mProjection;
};

struct ConstantUpdateBuffer
{
    Float4x4 mWorld;
};

class DxHelper
{
public:
    DxHelper();
    ~DxHelper();
    HRESULT StartUp(HWND wndHandle);
    void CleanAndStop();
    void BindVertexIndexBuffer(
        ID3D11Buffer* const* ppVertexBuffers,
        ID3D11Buffer* ppIndexBuffers);
    ID3D11VertexShader* GetVertexShader(std::string name);
    ID3D11PixelShader* GetPixelShader(std::string name);
    void ClearBuffer();
    void SwapBufferChain();
    ID3D11Device* GetDevicePtr();
    ID3D11DeviceContext* GetImmediateContextPtr();
    void PassWorldMatrixToVS(Matrix4x4f* world);

private:
    HRESULT CompileDefaultShaders();

    D3D_DRIVER_TYPE mDriverType;
    D3D_FEATURE_LEVEL mFeatLevel;
    ID3D11Device* mD3dDevicePtr;
    ID3D11Device1* mD3dDevice1Ptr;
    ID3D11DeviceContext* mImmediateContextPtr;
    ID3D11DeviceContext1* mImmediateContext1Ptr;
    IDXGISwapChain* mSwapChainPtr;
    IDXGISwapChain1* mSwapChain1Ptr;
    ID3D11RasterizerState* mRasterizerStatePtr;
    ID3D11RenderTargetView* mRenderTargetViewPtr;
    ID3D11Texture2D* mDepthStencilPtr;
    ID3D11DepthStencilState* mDepthStencilStatePtr;
    ID3D11DepthStencilView* mDepthStencilViewPtr;
    ID3D11BlendState* mBlendStatePtr;
    ID3D11InputLayout* mVertexLayoutPtr;
    ID3D11SamplerState* mSamplerLinearPtr;
    std::map<std::string, ID3D11VertexShader*> mVertShaders;
    std::map<std::string, ID3D11PixelShader*> mPixlShaders;
    ID3D11Buffer* mConstBufferPtr;
    ID3D11Buffer* mUpdateConstBufferPtr;
    Matrix4x4f mProjMatrix;
    ConstantBuffer mProjBuffer;
    ConstantUpdateBuffer mWorldBuffer;
};
