#include "DxHelper.h"
#include "NinLog.h"
#include "main.h"
#include <d3dcompiler.h>
#include <DirectXColors.h>

ID3D11VertexShader* g_DefaultVertexShaderPtr = nullptr;
ID3D11PixelShader* g_DefaultPixelShaderPtr = nullptr;
Matrix4x4f g_InitValue =
{
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f
};

void MatrixStore_DX(Float4x4* ptr, Matrix4x4f mat)
{
    *ptr = DirectX::XMLoadFloat4x4(&mat);
}

HRESULT CompileShaderFromFile(const WCHAR* szFileName,
    LPCSTR szEntryPoint, LPCSTR szShaderModel,
    ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;

    hr = D3DCompileFromFile(
        szFileName, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(
                pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

DxHelper::DxHelper() :
    mD3dDevicePtr(nullptr), mD3dDevice1Ptr(nullptr),
    mImmediateContextPtr(nullptr), mImmediateContext1Ptr(nullptr),
    mSwapChainPtr(nullptr), mSwapChain1Ptr(nullptr),
    mRenderTargetViewPtr(nullptr), mVertexLayoutPtr(nullptr),
    mDepthStencilPtr(nullptr), mDepthStencilViewPtr(nullptr),
    mSamplerLinearPtr(nullptr), mDepthStencilStatePtr(nullptr),
    mBlendStatePtr(nullptr), mVertShaders({}), mPixlShaders({}),
    mConstBufferPtr(nullptr), mUpdateConstBufferPtr(nullptr),
    mProjMatrix(g_InitValue), mRasterizerStatePtr(nullptr),
    mDriverType(D3D_DRIVER_TYPE_UNKNOWN),
    mFeatLevel(D3D_FEATURE_LEVEL_1_0_CORE),
    mProjBuffer({}), mWorldBuffer({})
{

}

DxHelper::~DxHelper()
{
    mVertShaders.clear();
    mPixlShaders.clear();
}

HRESULT DxHelper::StartUp(HWND wndHandle)
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(wndHandle, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    UINT deviceCreateFlag = 0;
#ifdef _DEBUG
    deviceCreateFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_REFERENCE,
        D3D_DRIVER_TYPE_WARP
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    UINT numFeatLevels = ARRAYSIZE(featureLevels);
    mFeatLevel = featureLevels[0];

    for (UINT i = 0; i < numDriverTypes; i++)
    {
        mDriverType = driverTypes[i];
        hr = D3D11CreateDevice(nullptr, mDriverType,
            nullptr, deviceCreateFlag, featureLevels,
            numFeatLevels, D3D11_SDK_VERSION,
            &mD3dDevicePtr, &mFeatLevel,
            &mImmediateContextPtr);

        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDevice(nullptr, mDriverType,
                nullptr, deviceCreateFlag,
                featureLevels + 1, numFeatLevels - 1,
                D3D11_SDK_VERSION, &mD3dDevicePtr,
                &mFeatLevel, &mImmediateContextPtr);
        }

        if (SUCCEEDED(hr))
        {
            break;
        }
    }
    if (FAILED(hr))
    {
        return hr;
    }

    IDXGIFactory1* dxgiFactory1 = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = mD3dDevicePtr->QueryInterface(
            IID_PPV_ARGS(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(
                    IID_PPV_ARGS(&dxgiFactory1));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
    {
        return hr;
    }

    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory1->QueryInterface(
        IID_PPV_ARGS(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // 11.1+
        hr = mD3dDevicePtr->QueryInterface(
            IID_PPV_ARGS(&mD3dDevice1Ptr));
        if (SUCCEEDED(hr))
        {
            mImmediateContextPtr->QueryInterface(
                IID_PPV_ARGS(&mImmediateContext1Ptr));
        }
        DXGI_SWAP_CHAIN_DESC1 dc = {};
        dc.Width = width;
        dc.Height = height;
        dc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        dc.SampleDesc.Count = 1;
        dc.SampleDesc.Quality = 0;
        dc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        dc.BufferCount = 2;
        dc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        dc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

        hr = dxgiFactory2->CreateSwapChainForHwnd(
            mD3dDevicePtr, wndHandle,
            &dc, nullptr, nullptr, &mSwapChain1Ptr);
        if (SUCCEEDED(hr))
        {
            hr = mSwapChain1Ptr->QueryInterface(
                IID_PPV_ARGS(&mSwapChainPtr));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // 11.0
        DXGI_SWAP_CHAIN_DESC dc = {};
        dc.BufferCount = 2;
        dc.BufferDesc.Width = width;
        dc.BufferDesc.Height = height;
        dc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        dc.BufferDesc.RefreshRate.Numerator = 60;
        dc.BufferDesc.RefreshRate.Denominator = 1;
        dc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        dc.OutputWindow = wndHandle;
        dc.SampleDesc.Count = 1;
        dc.SampleDesc.Quality = 0;
        dc.Windowed = TRUE;
        dc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        dc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

        hr = dxgiFactory1->CreateSwapChain(
            mD3dDevicePtr, &dc, &mSwapChainPtr);
    }

    dxgiFactory1->Release();
    if (FAILED(hr))
    {
        return hr;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = mSwapChainPtr->GetBuffer(
        0, IID_PPV_ARGS(&pBackBuffer));
    if (FAILED(hr))
    {
        return hr;
    }

    hr = mD3dDevicePtr->CreateRenderTargetView(
        pBackBuffer, nullptr, &mRenderTargetViewPtr);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_TEXTURE2D_DESC texDepSte = {};
    texDepSte.Width = width;
    texDepSte.Height = height;
    texDepSte.MipLevels = 1;
    texDepSte.ArraySize = 1;
    texDepSte.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texDepSte.SampleDesc.Count = 1;
    texDepSte.SampleDesc.Quality = 0;
    texDepSte.Usage = D3D11_USAGE_DEFAULT;
    texDepSte.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texDepSte.CPUAccessFlags = 0;
    texDepSte.MiscFlags = 0;
    hr = mD3dDevicePtr->CreateTexture2D(
        &texDepSte, nullptr, &mDepthStencilPtr);
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC desDSV = {};
    desDSV.Format = texDepSte.Format;
    desDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    desDSV.Texture2D.MipSlice = 0;
    hr = mD3dDevicePtr->CreateDepthStencilView(
        mDepthStencilPtr, &desDSV, &mDepthStencilViewPtr);
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_DEPTH_STENCIL_DESC ddsd = {};
    ddsd.DepthEnable = FALSE;
    ddsd.StencilEnable = FALSE;
    hr = mD3dDevicePtr->CreateDepthStencilState(
        &ddsd, &mDepthStencilStatePtr);
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_RASTERIZER_DESC drd = {};
    drd.FillMode = D3D11_FILL_SOLID;
    drd.CullMode = D3D11_CULL_NONE;
    mD3dDevicePtr->CreateRasterizerState(
        &drd, &mRasterizerStatePtr);
    mImmediateContextPtr->
        RSSetState(mRasterizerStatePtr);

    D3D11_RENDER_TARGET_BLEND_DESC drtb = {};
    drtb.BlendEnable = TRUE;
    drtb.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    drtb.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    drtb.BlendOp = D3D11_BLEND_OP_ADD;
    drtb.SrcBlendAlpha = D3D11_BLEND_ONE;
    drtb.DestBlendAlpha = D3D11_BLEND_ZERO;
    drtb.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    drtb.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    D3D11_BLEND_DESC dbd = {};
    dbd.AlphaToCoverageEnable = FALSE;
    dbd.IndependentBlendEnable = FALSE;
    dbd.RenderTarget[0] = drtb;
    hr = mD3dDevicePtr->CreateBlendState(
        &dbd, &mBlendStatePtr);
    if (FAILED(hr))
    {
        return hr;
    }

    float factor[4] = { 0.f,0.f,0.f,0.f };
    mImmediateContextPtr->OMSetBlendState(mBlendStatePtr,
        factor, 0xFFFFFFFF);

    mImmediateContextPtr->OMSetDepthStencilState(
        mDepthStencilStatePtr, 1);

    mImmediateContextPtr->OMSetRenderTargets(
        1, &mRenderTargetViewPtr, mDepthStencilViewPtr);

    mImmediateContextPtr->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    D3D11_VIEWPORT vp = {};
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    mImmediateContextPtr->RSSetViewports(1, &vp);
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_SAMPLER_DESC desSam = {};
    desSam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desSam.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desSam.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desSam.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desSam.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desSam.MinLOD = 0;
    desSam.MaxLOD = D3D11_FLOAT32_MAX;
    hr = mD3dDevicePtr->CreateSamplerState(
        &desSam, &mSamplerLinearPtr);
    if (FAILED(hr))
    {
        return hr;
    }
    mImmediateContextPtr->PSSetSamplers(
        0, 1, &mSamplerLinearPtr);

    hr = CompileDefaultShaders();
    if (FAILED(hr))
    {
        return hr;
    }
    mImmediateContextPtr->VSSetShader(
        g_DefaultVertexShaderPtr, nullptr, 0);
    mImmediateContextPtr->PSSetShader(
        g_DefaultPixelShaderPtr, nullptr, 0);

    Float4x4 projMatrix = DirectX::XMMatrixOrthographicLH(
        SCREEN_WIDTH, -SCREEN_HEIGHT, 10000.f, -10000.f);
    DirectX::XMStoreFloat4x4(&mProjMatrix, projMatrix);
    mProjBuffer.mProjection = projMatrix;
    mImmediateContextPtr->UpdateSubresource(mConstBufferPtr,
        0, nullptr, &mProjBuffer, 0, 0);
    mImmediateContextPtr->VSSetConstantBuffers(
        0, 1, &mConstBufferPtr);

    return hr;
}

void DxHelper::CleanAndStop()
{
    if (mImmediateContextPtr)
    {
        mImmediateContextPtr->ClearState();
    }
    if (mConstBufferPtr)
    {
        mConstBufferPtr->Release();
    }
    if (mUpdateConstBufferPtr)
    {
        mUpdateConstBufferPtr->Release();
    }
    if (mVertexLayoutPtr)
    {
        mVertexLayoutPtr->Release();
    }
    for (auto& shader : mVertShaders)
    {
        shader.second->Release();
    }
    mVertShaders.clear();
    for (auto& shader : mPixlShaders)
    {
        shader.second->Release();
    }
    mPixlShaders.clear();
    if (mSamplerLinearPtr)
    {
        mSamplerLinearPtr->Release();
    }
    if (mDepthStencilViewPtr)
    {
        mDepthStencilViewPtr->Release();
    }
    if (mDepthStencilPtr)
    {
        mDepthStencilPtr->Release();
    }
    if (mRenderTargetViewPtr)
    {
        mRenderTargetViewPtr->Release();
    }
    if (mSwapChain1Ptr)
    {
        mSwapChain1Ptr->Release();
    }
    if (mSwapChainPtr)
    {
        mSwapChainPtr->Release();
    }
    if (mImmediateContext1Ptr)
    {
        mImmediateContext1Ptr->Release();
    }
    if (mImmediateContextPtr)
    {
        mImmediateContextPtr->Release();
    }

#ifdef _DEBUG
    ID3D11Debug* pDebug = nullptr;
    HRESULT hr = mD3dDevicePtr->QueryInterface(
        IID_PPV_ARGS(&pDebug));
    if (SUCCEEDED(hr))
    {
        hr = pDebug->ReportLiveDeviceObjects(
            D3D11_RLDO_DETAIL);
        pDebug->Release();
    }
#endif // _DEBUG

    if (mD3dDevice1Ptr)
    {
        mD3dDevice1Ptr->Release();
    }
    if (mD3dDevicePtr)
    {
        mD3dDevicePtr->Release();
    }
}

void DxHelper::BindVertexIndexBuffer(
    ID3D11Buffer* const* ppVertexBuffers,
    ID3D11Buffer* ppIndexBuffers)
{
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    mImmediateContextPtr->IASetVertexBuffers(0, 1,
        ppVertexBuffers, &stride, &offset);
    mImmediateContextPtr->IASetIndexBuffer(ppIndexBuffers,
        DXGI_FORMAT_R32_UINT, 0);
}

ID3D11VertexShader* DxHelper::GetVertexShader(std::string name)
{
    if (mVertShaders.find(name) == mVertShaders.end())
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find this shader : [ %s ]\n",
            name.c_str());
        return nullptr;
    }

    return mVertShaders[name];
}

ID3D11PixelShader* DxHelper::GetPixelShader(std::string name)
{
    if (mPixlShaders.find(name) == mPixlShaders.end())
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find this shader : [ %s ]\n",
            name.c_str());
        return nullptr;
    }

    return mPixlShaders[name];
}

HRESULT DxHelper::CompileDefaultShaders()
{
    ID3DBlob* pVSBlob = nullptr;
    HRESULT hr = CompileShaderFromFile(
        L"rom\\Assets\\Shaders\\tempVertexShader.hlsl",
        "main", "vs_5_0", &pVSBlob);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = mD3dDevicePtr->CreateVertexShader(
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), nullptr,
        &g_DefaultVertexShaderPtr);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {
            "POSITION",0,
            DXGI_FORMAT_R32G32B32_FLOAT,0,0,
            D3D11_INPUT_PER_VERTEX_DATA,0
        },
        {
            "COLOR",0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,
            D3D11_INPUT_PER_VERTEX_DATA,0
        },
        {
            "TEXCOORD",0,
            DXGI_FORMAT_R32G32_FLOAT,0,28,
            D3D11_INPUT_PER_VERTEX_DATA,0
        }
    };
    UINT numInputLayouts = ARRAYSIZE(layout);
    hr = mD3dDevicePtr->CreateInputLayout(
        layout, numInputLayouts,
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        &mVertexLayoutPtr);
    pVSBlob->Release();
    if (FAILED(hr))
    {
        return hr;
    }
    mImmediateContextPtr->IASetInputLayout(mVertexLayoutPtr);

    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(
        L"rom\\Assets\\Shaders\\tempPixelShader.hlsl",
        "main", "ps_5_0", &pPSBlob);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = mD3dDevicePtr->CreatePixelShader(
        pPSBlob->GetBufferPointer(),
        pPSBlob->GetBufferSize(), nullptr,
        &g_DefaultPixelShaderPtr);
    pPSBlob->Release();
    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_BUFFER_DESC lbdc = {};
    lbdc.Usage = D3D11_USAGE_DEFAULT;
    lbdc.ByteWidth = sizeof(ConstantBuffer);
    lbdc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lbdc.CPUAccessFlags = 0;
    hr = mD3dDevicePtr->CreateBuffer(
        &lbdc, nullptr, &mConstBufferPtr);
    if (FAILED(hr))
    {
        return hr;
    }

    lbdc.Usage = D3D11_USAGE_DEFAULT;
    lbdc.ByteWidth = sizeof(ConstantUpdateBuffer);
    lbdc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lbdc.CPUAccessFlags = 0;
    hr = mD3dDevicePtr->CreateBuffer(
        &lbdc, nullptr, &mUpdateConstBufferPtr);
    return hr;
}

void DxHelper::ClearBuffer()
{
    mImmediateContextPtr->ClearRenderTargetView(
        mRenderTargetViewPtr, DirectX::Colors::Black);
    mImmediateContextPtr->ClearDepthStencilView(
        mDepthStencilViewPtr, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void DxHelper::SwapBufferChain()
{
    mSwapChainPtr->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

ID3D11Device* DxHelper::GetDevicePtr()
{
    return mD3dDevicePtr;
}

ID3D11DeviceContext* DxHelper::GetImmediateContextPtr()
{
    return mImmediateContextPtr;
}

void DxHelper::PassWorldMatrixToVS(Matrix4x4f* world)
{
    Float4x4 worldMat = DirectX::XMLoadFloat4x4(world);
    mWorldBuffer.mWorld = worldMat;

    mImmediateContextPtr->UpdateSubresource(mUpdateConstBufferPtr,
        0, nullptr, &mWorldBuffer, 0, 0);
    mImmediateContextPtr->VSSetConstantBuffers(
        1, 1, &mUpdateConstBufferPtr);
}
