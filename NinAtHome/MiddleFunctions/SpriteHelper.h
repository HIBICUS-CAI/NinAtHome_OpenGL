#pragma once

#include "DxHelper.h"

void DrawSprite(ID3D11Buffer* const* ppVertexBuffers,
	ID3D11Buffer* ppIndexBuffers,
	float x, float y, float width, float height,
	float tx, float ty, float tw, float th,
	Float4 color);
