#include "TextureHelper.h"
#include "DxHelper.h"
#include "DxProcess.h"
#include "main.h"
#include <iostream>
#include <vector>
#include <DirectXTK\WICTextureLoader.h>

void SplitByRomSymbol(const std::string& s,
    std::vector<std::string>& v, const std::string& c)
{
    v.clear();
    std::string::size_type pos1 = 0, pos2 = s.find(c);
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

ID3D11ShaderResourceView* LoadTexture(std::string fileName)
{
    {
        std::vector<std::string> v;
        SplitByRomSymbol(fileName, v, ":/");
        fileName = v[0] + "\\" + v[1];
        v.clear();
        SplitByRomSymbol(fileName, v, "/");
        if (v.size() > 1)
        {
            fileName = "";
            for (int i = 0; i < v.size(); i++)
            {
                if (i == (v.size() - 1))
                {
                    fileName += v[i];
                }
                else
                {
                    fileName += v[i] + "\\";
                }
            }
        }
    }

    HRESULT hr = S_OK;
    ID3D11ShaderResourceView* texSRV = nullptr;

    std::wstring wName = std::wstring(
        fileName.begin(), fileName.end());

    hr = DirectX::CreateWICTextureFromFile(
        GetDxHelperPtr()->GetDevicePtr(),
        wName.c_str(), nullptr, &texSRV);
    if (FAILED(hr))
    {
        return nullptr;
    }

    return texSRV;
}

void UnloadTexture(ID3D11ShaderResourceView** pSRV)
{
    if (pSRV && *pSRV)
    {
        (*pSRV)->Release();
    }
}

void SetTexture(ID3D11ShaderResourceView** pSRV)
{
    if (!pSRV || !(*pSRV))
    {
        return;
    }
    else
    {
        GetDxHelperPtr()->GetImmediateContextPtr()->
            PSSetShaderResources(0, 1, pSRV);
    }
}
