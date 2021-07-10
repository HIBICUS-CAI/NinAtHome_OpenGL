#pragma once

#include <string>
#include <d3d11_1.h>

ID3D11ShaderResourceView* LoadTexture(std::string fileName);

void UnloadTexture(ID3D11ShaderResourceView** pSRV);

void SetTexture(ID3D11ShaderResourceView** pSRV);
